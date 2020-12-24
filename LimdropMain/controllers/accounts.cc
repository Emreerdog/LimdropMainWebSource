#include "accounts.h"
#include <limutils/passhandler.h>
#include <limutils/PatternFiller.h>
#include "limjson.h"
//add definition of your processing function here


void accounts::createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email){

	auto sessionPtr = req->session();
	
	drogon::Cookie loginDisplay;
	drogon::Cookie loginCssStat;
	drogon::Cookie loginStatus;
	loginDisplay.setKey("_isdisplayed");
	loginCssStat.setKey("_color");
	loginStatus.setKey("_feedback_msg");
	
	PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);

	srand(time(0));
	
	passHandler.MakeLRpair(rand() % 10 + 5, rand() % 10 + 5);
	std::pair <unsigned long, unsigned long> LRPair = passHandler.GetLRpair();

	// Convert not encrypted lr pair to string
	std::string L = std::to_string(LRPair.first);
	std::string R = std::to_string(LRPair.second);

	passHandler.EncryptPass();
	LRPair = passHandler.GetLRpair();

	// Convert encrypted lr pair to string
	std::string LE = std::to_string(LRPair.first);
	std::string RE = std::to_string(LRPair.second);
	
	auto date = trantor::Date::now();

	auto clientPtr = drogon::app().getDbClient();
	std::string createDate = date.toCustomedFormattedString("%Y-%m-%d");
	std::string createTime = date.toCustomedFormattedString("%H:%M:%S");
	std::string preQuery = "SELECT id FROM accounts WHERE username='"+ uname + "' OR email='" + email + "'";
	auto f = clientPtr->execSqlAsyncFuture(preQuery);
	if(f.get().size() > 0){
		const char* _display = "block";
		const char* _status = "red";
		const char* _statusText = "Username or email already exists";
		
		loginDisplay.setValue(_display);
		loginCssStat.setValue(_status);
		loginStatus.setValue(_statusText);
		auto res = HttpResponse::newRedirectionResponse("/accounts/create");
		res->addCookie(loginDisplay);
		res->addCookie(loginCssStat);
		res->addCookie(loginStatus);
		callback(res);
		return;
	}
	

	std::string uuid = drogon::utils::getUuid();
	std::string queryStart = "INSERT INTO accounts(username, L, R, P1, P2, email, accountCreateDate, accountCreateTime, uuid, isverified) VALUES";
	std::string queryEnd = "('" + uname + "'," + L + "," + R + ",'" + LE + "','" + RE +"','" + email + "','" + createDate + "','" + createTime+ "', '" + uuid + "', FALSE)";
      	std::string totalQuery = queryStart + queryEnd;	
	clientPtr->execSqlAsyncFuture(totalQuery);

	const char* _display = "block";
	const char* _status = "green";
	std::string _statusText = uuid;

	loginDisplay.setValue(_display);
	loginCssStat.setValue(_status);
	loginStatus.setValue(_statusText);
	auto res = HttpResponse::newRedirectionResponse("/accounts/create");
	res->addCookie(loginDisplay);
	res->addCookie(loginCssStat);
	res->addCookie(loginStatus);
	callback(res);
}


void accounts::loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass){

	auto sessionPtr = req->session();	
	// TODO 
	// Read the name and password from the database
	// Password should be decrypted using blowfish 
	//
	// TODO 
	// Get L and R value from database
	// Encrypt the password using L and R value
	// Then,
	// Check the validity by comparing new L and R values
	auto clientPtr = drogon::app().getDbClient();
	drogon::Cookie loginDisplay;
	drogon::Cookie loginCssStat;
	drogon::Cookie loginStatus;
	loginDisplay.setKey("_isdisplayed");
	loginCssStat.setKey("_color");
	loginStatus.setKey("_feedback_msg");

	std::string queryStart = "SELECT L, R, P1, P2, id FROM accounts WHERE ";
	std::string queryEnd = "username = '" + uname + "' AND isverified = TRUE";
	std::string totalQuery = queryStart + queryEnd;

	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	auto result = f.get();
	if(result.size() == 0){
		const char* _displaymessage = "block";
		const char*  _status = "red";
		const char*  _statusText = "Unable to login";
		loginDisplay.setValue(_displaymessage);
		loginCssStat.setValue(_status);
		loginStatus.setValue(_statusText);
		auto resp = HttpResponse::newRedirectionResponse("/accounts/");
		resp->addCookie(loginDisplay);
		resp->addCookie(loginCssStat);
		resp->addCookie(loginStatus);
		callback(resp);
		return;
	}
	else{
		unsigned long L = 0;
		unsigned long R = 0;
		unsigned long P1 = 0;
		unsigned long P2 = 0;
		std::string user_id;
		for(auto row : result){
			L = row["L"].as<unsigned long>();
			R = row["R"].as<unsigned long>();
			P1 = row["P1"].as<unsigned long>();
			P2 = row["P2"].as<unsigned long>();
			user_id = row["id"].as<std::string>();
		}
		PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);
		passHandler.MakeLRpair(L, R);
		passHandler.EncryptPass();
		std::pair <unsigned long, unsigned long> LRpair = passHandler.GetLRpair();
		// Decrypt password
		if(LRpair.first == P1 && LRpair.second == P2){
			sessionPtr->erase("isLoggedIn");
			sessionPtr->erase("username");
			sessionPtr->erase("balance");
			sessionPtr->erase("id");

			bool isLoggedIn = true;
			float balance = 0;
			sessionPtr->insert("isLoggedIn", isLoggedIn);
			sessionPtr->insert("username", uname);
			sessionPtr->insert("balance", balance);
			sessionPtr->insert("id", user_id);
			auto resp = HttpResponse::newNotFoundResponse();
			callback(resp);
			return;
		}
	}
        const char* _displaymessage = "block";
	const char* _status = "red";
	const char* _statusText = "Password is incorrect";
	loginDisplay.setValue(_displaymessage);
	loginCssStat.setValue(_status);
	loginStatus.setValue(_statusText);
	auto resp = HttpResponse::newRedirectionResponse("/accounts/");
	resp->addCookie(loginDisplay);
	resp->addCookie(loginCssStat);
	resp->addCookie(loginStatus);
	callback(resp);
	return;
}


void accounts::loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();

	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	const char* _display = req->getCookie("_isdisplayed").c_str();
	const char* _status = req->getCookie("_color").c_str();
	const char* _statusText = req->getCookie("_feedback_msg").c_str();

	ManualPatternFiller MPF(3, "display", "status", "statusText");
	std::string result = MPF.fillPatterns("login.html", _display, _status, _statusText);

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(result);
	resp->addCookie("_isdisplayed", "");
	resp->addCookie("_color", "");
	resp->addCookie("_feedback_msg", "");	
	callback(resp);
}

