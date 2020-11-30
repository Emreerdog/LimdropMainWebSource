#include "accounts.h"
#include <limutils/passhandler.h>
//add definition of your processing function here


void accounts::createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email){
	auto clientPtr = drogon::app().getDbClient();
	PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);
	passHandler.MakeLRpair();
	passHandler.EncryptPass();
	std::pair <unsigned long, unsigned long> LRPair = passHandler.GetLRpair();

	std::cout << LRPair.first << "  " << LRPair.second << std::endl;

	auto res = HttpResponse::newNotFoundResponse();
	callback(res);
}


void accounts::loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass){

}
