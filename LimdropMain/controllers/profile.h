#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class profile:public drogon::HttpController<profile>
{
  public:
    METHOD_LIST_BEGIN
    //use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(profile::showProfile,"/{1}/", Get, "checktraffic");//path is /profile/{arg2}/{arg1}
    METHOD_ADD(profile::addAddress, "/addAddress?city={1}&address={2}&phoneNumber={3}&zipcode={4}", Get);
    METHOD_ADD(profile::removeAddress, "/removeAddress", Get);
    METHOD_ADD(profile::showAddress, "/address/", Get, "checktraffic");
	//METHOD_ADD(profile::your_method_name,"/{1}/{2}/list",Get);//path is /profile/{arg1}/{arg2}/list
    //ADD_METHOD_TO(profile::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    void showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey);
    void addAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string city, std::string address, std::string phoneNumber, std::string zipcode);
    void removeAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex);
    void showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex);
    // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
};
