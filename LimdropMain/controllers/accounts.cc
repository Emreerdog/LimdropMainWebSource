#include "accounts.h"
#include <limutils/passhandler.h>
#include <limutils/PatternFiller.h>
//add definition of your processing function here


void accounts::createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email){
	PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);
	passHandler.MakeLRpair();
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
	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	std::cout << totalQuery << std::endl;

	auto res = HttpResponse::newNotFoundResponse();
	callback(res);
}


void accounts::loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass){

}


void accounts::loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("https://192.168.1.23/");
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
