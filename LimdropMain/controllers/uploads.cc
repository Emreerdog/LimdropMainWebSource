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


void uploads::upload_files(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	drogon::MultiPartParser mpp;
	mpp.parse(req);
	const std::vector<drogon::HttpFile> f = mpp.getFiles();
	std::cout << f[1].getFileName() << std::endl;
	std::cout << f[2].getFileName() << std::endl;
	std::cout << f[3].getFileName() << std::endl;
	std::cout << f[4].getFileName() << std::endl;

	

}


void uploads::files_page(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	ManualPatternFiller MPF(1, "mark");
	std::string tempContent = MPF.fillPatterns("addimage.html", "");
	std::vector<std::string> unchangable;
	std::vector<std::string> fileInputs;
	unsigned short imageCount = 0;

	for(const auto& n : tempParam){
		if(n.first == "imgCount"){
			imageCount = std::stoi(n.second);
		}
		std::string inputs = "<p>";
		inputs += n.first + ": <br>" + n.second + "<br><p><br>";
		unchangable.push_back(inputs);
	}
	for(int i = 0; i < imageCount; i++){
		std::string formElement = "<input type='file' name='" + drogon::utils::genRandomString(8) + "'>";
		fileInputs.push_back(formElement);
	}

	std::reverse(unchangable.begin(), unchangable.end());
	fileInputs.push_back("<input type='submit' value='Upload image'>");
	unchangable.insert(unchangable.end(), fileInputs.begin(), fileInputs.end());

	SequentialPatternFiller SPF;
	std::string content = SPF.fillOnString(tempContent, "#$ozan", unchangable, "form", true, true, "/uploads/product/upload-photo", "", "post", true);
	fileInputs.clear();
	unchangable.clear();
	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(content);
	callback(resp);

}
//add definition of your processing function here
