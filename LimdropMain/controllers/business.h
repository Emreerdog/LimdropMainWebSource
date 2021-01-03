#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class business:public drogon::HttpController<business>
{
  public:
    METHOD_LIST_BEGIN
    
    METHOD_ADD(business::loginPage, "/loginPage", Get);
    METHOD_ADD(business::login, "/login/?businessId={1}&pass={2}", Post, "businesslogin");
    METHOD_ADD(business::createPage, "/createPage", Get);
    METHOD_ADD(business::create, "/create/?businessName={1}&pass{2}", Post, "businesscreate");

    METHOD_LIST_END
    void loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void login(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string businessId, std::string pass);
    void createPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string businessName, std::string pass);
};
