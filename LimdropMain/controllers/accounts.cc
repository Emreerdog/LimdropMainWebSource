#include "accounts.h"
#include <limutils/passhandler.h>
#include <limutils/PatternFiller.h>
//add definition of your processing function here


void accounts::createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email){
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

	std::string queryStart = "INSERT INTO accounts(username, L, R, P1, P2, email, accountCreateDate, accountCreateTime) VALUES";
	std::string queryEnd = "('" + uname + "'," + L + "," + R + ",'" + LE + "','" + RE +"','" + email + "','" + createDate + "','" + createTime+ "')";
      	std::string totalQuery = queryStart + queryEnd;	
	clientPtr->execSqlAsyncFuture(totalQuery);

	auto res = HttpResponse::newRedirectionResponse("/accounts/");
	callback(res);
}


void accounts::loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, int num){

		
	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	for(const auto& n : tempParam){
		// TODO 
		// Read the name and password from the database
		// Password should be decrypted using blowfish 
		if(n.second == "3"){
			std::cout << n.second << std::endl;
		}
		
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
		if(LRpair.first == P1 && LRpair.second == P2){
			std::cout << LRpair.first << " " << LRpair.second << std::endl;
			auto resp = HttpResponse::newNotFoundResponse();
			callback(resp);
			return;
		}
	}
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);	
}


void accounts::loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	
	ManualPatternFiller MPF(2, "status", "statusText");
	std::string fileContent = "";
	std::string result = MPF.fillPatterns("login.html", "testStat", "testtext");
	
	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(result);
	callback(resp);

}

