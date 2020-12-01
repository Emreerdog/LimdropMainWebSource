#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class accounts:public drogon::HttpController<accounts>
{
  public:
    METHOD_LIST_BEGIN
		METHOD_ADD(accounts::createAccount, "/signup?uname={1}&pass={2}&email={3}", Post, "createaccount");
		METHOD_ADD(accounts::loginAccount, "/login?uname={1}&pass{2}", Post, "login");
		METHOD_ADD(accounts::loginPage, "/", Get);
    //use METHOD_ADD to add your custom processing function here;
    //METHOD_ADD(accounts::get,"/{2}/{1}",Get);//path is /accounts/{arg2}/{arg1}
    //METHOD_ADD(accounts::your_method_name,"/{1}/{2}/list",Get);//path is /accounts/{arg1}/{arg2}/list
    //ADD_METHOD_TO(accounts::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /absolute/path/{arg1}/{arg2}/list
	
    METHOD_LIST_END
		void createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass, std::string email);
		void loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string uname, std::string pass);
    
	
    void loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,int p1,std::string p2);
    // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
};
