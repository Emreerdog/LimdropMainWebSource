#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class sutils:public drogon::HttpController<sutils>
{
  public:
    static Json::Value getSVTime();

    METHOD_LIST_BEGIN
    METHOD_ADD(sutils::getServerTime,"/currentDate",Get);//path is /sutils/{arg2}/{arg1}

    METHOD_LIST_END
    
    void getServerTime(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
