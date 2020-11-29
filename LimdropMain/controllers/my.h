#pragma once

#define PY_SSIZE_T_CLEAN

#include <drogon/HttpSimpleController.h>
using namespace drogon;
class my:public drogon::HttpSimpleController<my>
{
  public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    //list path definitions here;
    PATH_ADD("/", Get);
    PATH_LIST_END
};
