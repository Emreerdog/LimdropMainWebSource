#include "trjson.h"
#include <limutils/PatternFiller.h>
void trjson::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{

    ManualPatternFiller MPF(2, "bum", "bam");
    std::string content = MPF.fillPatterns("sendfile.html", "", "");

    auto resp = HttpResponse::newHttpResponse();

    resp->setBody(content);
    callback(resp);
}
