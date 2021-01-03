#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class factory:public drogon::HttpController<factory>
{
  public:
    METHOD_LIST_BEGIN

    METHOD_ADD(factory::changeUserProfile,"/user/profilechange", Post, "profilechangefilter");
    METHOD_ADD(factory::changeUserPassword,"/user/passchange", Post, "passwordchangefilter");
    METHOD_ADD(factory::changeUserPasswordEmail, "/user/passchangemail", Post);
    METHOD_ADD(factory::changeProductParams, "/product/changeparams", Post, "changeparamsfilter");
    METHOD_ADD(factory::addAddress, "/user/addAddress?city={1}&address={2}&phoneNumber={3}&zipcode={4}", Post);
    METHOD_ADD(factory::removeAddress, "/user/removeAddress?addressIndex={1}", Post);

    METHOD_LIST_END
    void changeUserProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);	
    void changeUserPassword(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void changeUserPasswordEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void changeProductParams(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void addAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string city, std::string address, std::string phoneNumber, std::string zipcode);
    void removeAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex);
};
