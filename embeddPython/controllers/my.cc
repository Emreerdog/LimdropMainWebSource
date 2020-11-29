#include "my.h"
#include <Python.h>
void my::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    auto resp = HttpResponse::newNotFoundResponse();
    callback(resp);
}
