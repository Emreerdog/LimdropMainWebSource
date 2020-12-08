#include "accounts.h"
#include <limutils/passhandler.h>
#include <limutils/PatternFiller.h>
//add definition of your processing function here


void accounts::createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email){

	auto sessionPtr = req->session();
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
	std::string createDate = date.toCustomedFormattedString("%d-%m-%Y");
	std::string createTime = date.toCustomedFormattedString("%H:%M:%S");
	std::string preQuery = "SELECT id FROM accounts WHERE username='"+ uname + "'";
	auto f = clientPtr->execSqlAsyncFuture(preQuery);
	if(f.get().size() > 0){
		sessionPtr->insert("display", "block");
		sessionPtr->insert("status", "red");
		sessionPtr->insert("statusText", "Username already exists");
		auto res = HttpResponse::newRedirectionResponse("/accounts/create");
		callback(res);
		return;
	}
	

	std::string queryStart = "INSERT INTO accounts(username, L, R, P1, P2, email, accountCreateDate, accountCreateTime) VALUES";
	std::string queryEnd = "('" + uname + "'," + L + "," + R + ",'" + LE + "','" + RE +"','" + email + "','" + createDate + "','" + createTime+ "')";
      	std::string totalQuery = queryStart + queryEnd;	
	std::cout << totalQuery << std::endl;
	clientPtr->execSqlAsyncFuture(totalQuery);
	
	sessionPtr->insert("display", "block");
	sessionPtr->insert("status", "green");
	sessionPtr->insert("statusText", "Account created sucessfully.<br>Verify your email to login to your account.");
	
	auto res = HttpResponse::newRedirectionResponse("/accounts/");
	callback(res);
}


void accounts::loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass){

	auto sessionPtr = req->session();	
	sessionPtr->erase("display");
	sessionPtr->erase("status");
	sessionPtr->erase("statusText");

	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	for(const auto& n : tempParam){
		// TODO 
		// Read the name and password from the database
		// Password should be decrypted using blowfish 
		
	}
	// TODO 
	// Get L and R value from database
	// Encrypt the password using L and R value
	// Then,
	// Check the validity by comparing new L and R values
	auto clientPtr = drogon::app().getDbClient();
	std::string queryStart = "SELECT L, R, P1, P2 FROM accounts WHERE ";
	std::string queryEnd = "username = '" + uname + "'";
	std::string totalQuery = queryStart + queryEnd;

	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	auto result = f.get();
	if(result.size() == 0){
		// TODO
		// Redirect to login page
		sessionPtr->insert("display", "block");
		sessionPtr->insert("status", "red");
		sessionPtr->insert("statusText", "Username is not valid");
		auto resp = HttpResponse::newRedirectionResponse("/accounts/");
		callback(resp);
		return;
	}
	else{
		unsigned long L = 0;
		unsigned long R = 0;
		unsigned long P1 = 0;
		unsigned long P2 = 0;
		for(auto row : result){
			L = row["L"].as<unsigned long>();
			R = row["R"].as<unsigned long>();
			P1 = row["P1"].as<unsigned long>();
			P2 = row["P2"].as<unsigned long>();
		}
		PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);
		passHandler.MakeLRpair(L, R);
		passHandler.EncryptPass();
		std::pair <unsigned long, unsigned long> LRpair = passHandler.GetLRpair();
		// Decrypt password
		if(LRpair.first == P1 && LRpair.second == P2){
			std::cout << uname << " Logged in" << std::endl;
			auto resp = HttpResponse::newNotFoundResponse();
			callback(resp);
			return;
		}
	}

	sessionPtr->insert("display", "block");
	sessionPtr->insert("status", "red");
	sessionPtr->insert("statusText", "Username is not valid");
	std::cout << "password is incorrect for username: " << uname << std::endl;
	auto resp = HttpResponse::newRedirectionResponse("/accounts/");
	callback(resp);
	return;
}


void accounts::loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	std::string _display = "hidden";
	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	if(sessionPtr->find("display")){
		_display = sessionPtr->get<std::string>("display");
	}


	std::string _status = sessionPtr->get<std::string>("status");
	std::string _statusText = sessionPtr->get<std::string>("statusText");

	ManualPatternFiller MPF(3, "display", "status", "statusText");
	std::string result = MPF.fillPatterns("login.html", _display.c_str(), _status.c_str(), _statusText.c_str());
	sessionPtr->erase("display");
	sessionPtr->erase("status");
	sessionPtr->erase("statusText");

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(result);
	callback(resp);

}

