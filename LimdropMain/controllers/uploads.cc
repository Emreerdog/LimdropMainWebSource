#include "uploads.h"
#include <limutils/PatternFiller.h>

void uploads::upload_product(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	//This is file parser

	//drogon::MultiPartParser mpp;
	//mpp.parse(req);
	//const std::vector<drogon::HttpFile> f = mpp.getFiles();
	//std::cout << f[0].getFileName() << std::endl;
	Json::Value ourProduct;

	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	for(const auto& n : tempParam){
		// TODO 
		// Get the off value count 
		ourProduct[n.first] = n.second;
	}
	auto resp = HttpResponse::newHttpJsonResponse(ourProduct);
	callback(resp);

}


void uploads::upload_form(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	
	ManualPatternFiller MPF(1, "mark");
	std::string content = MPF.fillPatterns("addproduct.html", "");

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(content);
	callback(resp);
}
//add definition of your processing function here
