#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class accounts:public drogon::HttpController<accounts>
{
  public:
    METHOD_LIST_BEGIN
		METHOD_ADD(accounts::createAccount, "/signup?uname={1}&pass={2}&email={3}", Post, "createaccount");
		METHOD_ADD(accounts::loginAccount, "/login?uname={1}&pass={2}", Post);
		METHOD_ADD(accounts::loginPage, "/", Get);
	
    METHOD_LIST_END
		void createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email);
		void loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass);	
   		void loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
