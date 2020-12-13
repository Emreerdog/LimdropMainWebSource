#include "trjson.h"
#include <limutils/PatternFiller.h>

void trjson::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	ManualPatternFiller MPF(1, "mark");
	std::string result = MPF.fillPatterns("addbasketitem.html", "Ozan, Anıl, Mustafa");

    	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(result);
    	callback(resp);
}
