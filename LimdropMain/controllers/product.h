#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class product:public drogon::HttpController<product>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(product::details,"/?itemId={1}",Get);//path is /product/{arg2}/{arg1}
//
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    void details(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
};
