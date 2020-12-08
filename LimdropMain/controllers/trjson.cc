#include "trjson.h"
#include <limutils/PatternFiller.h>
#include <Python.h>

void trjson::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    
    auto resp = HttpResponse::newNotFoundResponse();
    callback(resp);
}
