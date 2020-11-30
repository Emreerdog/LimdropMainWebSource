#pragma once
#include <drogon/HttpSimpleController.h>
using namespace drogon;
class signup:public drogon::HttpSimpleController<signup>
{
  public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    //list path definitions here;
    PATH_ADD("/accounts/create", Get, "checktraffic");
    PATH_LIST_END
};
