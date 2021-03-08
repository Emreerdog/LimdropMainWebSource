#include "sutils.h"


Json::Value sutils::getSVTime(){
    Json::Value responseJson;
    auto date = trantor::Date::now();
    std::string getDate = date.toCustomedFormattedString("%Y-%m-%d");
    std::string getTime = date.toCustomedFormattedString("%H:%M"); 
    responseJson["date"] = getDate;
    responseJson["time"] = getTime;
	responseJson["actionStatus"] = "true";
	
	return responseJson;
}

void sutils::getServerTime(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	
	auto resp = HttpResponse::newHttpJsonResponse(sutils::getSVTime());
	callback(resp);
	return;
}
