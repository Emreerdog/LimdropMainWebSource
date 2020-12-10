#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class activation:public drogon::HttpController<activation>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(activation::profileActivation,"/profile/{1}",Get);//path is /activation/{arg2}/{arg1}
    METHOD_ADD(activation::productActivation,"/product/{1}",Get);//path is /activation/{arg2}/{arg1}
	//ADD_METHOD_TO(activation::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /absolute/path/{arg1}/{arg2}/list

    METHOD_LIST_END
    void profileActivation(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string activationCode); 
    void productActivation(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string activationCode);
};
