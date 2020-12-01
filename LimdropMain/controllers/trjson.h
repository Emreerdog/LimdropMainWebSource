#pragma once
#include <drogon/HttpSimpleController.h>
using namespace drogon;
class trjson:public drogon::HttpSimpleController<trjson>
{
  public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    //list path definitions here;
    PATH_ADD("/bum", Get);
    PATH_LIST_END
};
