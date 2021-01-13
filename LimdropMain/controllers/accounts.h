#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class accounts:public drogon::HttpController<accounts>
{
  public:
    METHOD_LIST_BEGIN
		METHOD_ADD(accounts::createAccount, "/signup?email={1}&name={2}&surname={3}&pass={4}&passCheck={5}", Post);
		METHOD_ADD(accounts::loginAccount, "/login?email={1}&pass={2}", Post);
	
    METHOD_LIST_END
		void createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string email, std::string name, std::string surname, std::string pass, std::string passCheck);
		void loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string email, std::string pass);	
   		void loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
