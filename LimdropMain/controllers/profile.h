#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class profile:public drogon::HttpController<profile>
{
  public:
    METHOD_LIST_BEGIN
    
    METHOD_ADD(profile::showProfile,"/{1}/", Get, "checktraffic");
    METHOD_ADD(profile::addAddress, "/addAddress?city={1}&address={2}&phoneNumber={3}&zipcode={4}", Get);
    METHOD_ADD(profile::removeAddress, "/removeAddress?addressIndex={1}", Get);
    METHOD_ADD(profile::showAddress, "/address/", Get, "checktraffic");

    METHOD_LIST_END
    
    void showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey);
    void addAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string city, std::string address, std::string phoneNumber, std::string zipcode);
    void removeAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex);
    void showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex);
    // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
};
