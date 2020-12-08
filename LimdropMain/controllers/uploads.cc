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

	auto sessionPtr = req->session();
	std::vector<drogon::HttpFile> files = mpp.getFiles();
	std::vector<drogon::HttpFile>::iterator It;
	for(It = files.begin(); It != files.end(); It++){
		std::string fileName = drogon::utils::genRandomString(16);
		It->saveAs(fileName);
	}
	std::vector<std::string> passedVars = sessionPtr->get<std::vector<std::string>>("passedVars");
	std::vector<std::string>::iterator strIt;
	for(strIt = passedVars.begin(); strIt != passedVars.end(); strIt++){
		std::cout << *strIt << std::endl;
	}
	sessionPtr->erase("passedVars");
}


void uploads::files_page(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	sessionPtr->erase("passedVars");

	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	ManualPatternFiller MPF(1, "mark");
	std::string tempContent = MPF.fillPatterns("addimage.html", "");
	std::vector<std::string> unchangable;
	std::vector<std::string> fileInputs;
	std::vector<std::string> passedVars;
	unsigned short imageCount = 0;

	for(const auto& n : tempParam){
		if(n.first == "imgCount"){
			imageCount = std::stoi(n.second);
		}
		std::string inputs = "<p>";
		inputs += n.first + ": <br>" + n.second + "<br><p><br>";
		passedVars.push_back(n.second);
		unchangable.push_back(inputs);
	}

	for(int i = 0; i < imageCount; i++){
		std::string formElement = "<input type='file' name='" + drogon::utils::genRandomString(5) + "'><br>";
		fileInputs.push_back(formElement);
	}

	std::reverse(passedVars.begin(), passedVars.end());
	std::reverse(unchangable.begin(), unchangable.end());

	sessionPtr->insert("passedVars", passedVars);
	fileInputs.push_back("<input type='submit' value='Upload files'>");
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
