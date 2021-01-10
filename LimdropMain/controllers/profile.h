#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class profile:public drogon::HttpController<profile>
{
  public:
    METHOD_LIST_BEGIN
    
    METHOD_ADD(profile::showProfile,"/{1}/", Get, "checktraffic");
    METHOD_ADD(profile::showAddress, "/address", Post);

    METHOD_LIST_END
    
    void showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey);
    void showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
