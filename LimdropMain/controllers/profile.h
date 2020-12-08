#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class profile:public drogon::HttpController<profile>
{
  public:
    METHOD_LIST_BEGIN
    //use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(profile::showProfile,"/{1}/", Get, "checktraffic");//path is /profile/{arg2}/{arg1}
    //METHOD_ADD(profile::your_method_name,"/{1}/{2}/list",Get);//path is /profile/{arg1}/{arg2}/list
    //ADD_METHOD_TO(profile::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    void showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey);
    // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
};