#include "trjson.h"
#include <limutils/PatternFiller.h>

void trjson::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	auto sessionPtr = req->session();
	std::string x = "var";
	sessionPtr->insert("isloggedin", x);
	ManualPatternFiller MPF(1, "mark");
	std::string result = MPF.fillPatterns("index.html", "Ozan, Anıl, Mustafa");

    	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(result);
    	callback(resp);
}
