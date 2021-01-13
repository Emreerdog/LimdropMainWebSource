#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class profile:public drogon::HttpController<profile>
{
  public:
    METHOD_LIST_BEGIN
    
    METHOD_ADD(profile::showProfile,"/{1}/", Get);
    METHOD_ADD(profile::showAddress, "/address", Get);
    METHOD_ADD(profile::currentInfo, "/currentInfo", Get); 
    METHOD_ADD(profile::logout, "/logout", Post);

    METHOD_LIST_END
    
    void showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey);
    void showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void currentInfo(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void logout(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
