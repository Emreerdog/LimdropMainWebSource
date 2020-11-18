#pragma once
#include <drogon/HttpSimpleController.h>
using namespace drogon;
class testsys:public drogon::HttpSimpleController<testsys>
{
  public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    
	    PATH_ADD("/testsystem", Get);
    
    PATH_LIST_END
};
