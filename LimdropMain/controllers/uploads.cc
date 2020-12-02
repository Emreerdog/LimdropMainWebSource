#include "uploads.h"


void uploads::get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string fname){
	drogon::MultiPartParser mpp;
	mpp.parse(req);
	const std::vector<drogon::HttpFile> f = mpp.getFiles();
	f[0].saveAs("bumss.txt");
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);

}
//add definition of your processing function here
