#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class wallet:public drogon::HttpController<wallet>
{
  public:
    METHOD_LIST_BEGIN

    METHOD_ADD(wallet::show,"/", Get);//path is /wallet/{arg2}/{arg1}
    METHOD_ADD(wallet::addmoney,"/addmoney", Post);//path is /wallet/{arg1}/{arg2}/list

    METHOD_LIST_END
    void show(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
