#include "trjson.h"
void trjson::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	Json::Value root;
	std::string a = "val1";
	std::string b = "val2";
	root["vals"][a];
	root["vals"][b];


    auto resp = HttpResponse::newHttpJsonResponse(root);
    callback(resp);
}
