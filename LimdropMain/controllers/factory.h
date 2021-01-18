#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class factory:public drogon::HttpController<factory>
{
  public:
    METHOD_LIST_BEGIN

    METHOD_ADD(factory::showAddress, "/address", Get);
    METHOD_ADD(factory::addAddress, "/addAddress/{1}/{2}/{3}/{4}/{5}", Post); // 
    METHOD_ADD(factory::removeAddress, "/removeAddress/{1}", Post);

    METHOD_LIST_END
    
    void showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void addAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string city, std::string ilce, std::string address, std::string phoneNumber, std::string zipcode);
    void removeAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex);

};
