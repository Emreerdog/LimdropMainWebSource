#include "uploads.h"
#include "limjson.h"
#include <sstream>
#include <limutils/PatternFiller.h>
#include <algorithm>

void uploads::upload_product(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	//This is file parser

	//drogon::MultiPartParser mpp;
	//mpp.parse(req);
	//const std::vector<drogon::HttpFile> f = mpp.getFiles();
	//std::cout << f[0].getFileName() << std::endl;
	Json::Value ourProduct;

	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	for(const auto& n : tempParam){
		 
		ourProduct[n.first] = n.second;
	}
	auto resp = HttpResponse::newHttpJsonResponse(ourProduct);
	callback(resp);

}


void uploads::upload_form(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	sessionPtr->erase("passedVars");

	ManualPatternFiller MPF(1, "mark");
	std::string content = MPF.fillPatterns("addproduct.html", "");

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(content);
	callback(resp);
}


void uploads::upload_files(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	if(!sessionPtr->find("passedvars")){
		auto resp = HttpResponse::newRedirectionResponse("/uploads/");
		callback(resp);
		return;
	}

	drogon::MultiPartParser mpp;
	mpp.parse(req);
	Json::Value productJSON;

	std::vector<drogon::HttpFile> files = mpp.getFiles();
	std::vector<drogon::HttpFile>::iterator It;

	unsigned int iterPhoto = 0;

	for(It = files.begin(); It != files.end(); It++){
		std::string fileName(It->getFileName());
		std::string::size_type idx;
		idx = fileName.rfind('.');

		if(idx != std::string::npos){
			std::string extension = fileName.substr(idx+1);
			std::string _fileName = "";

			if(extension == "html"){
				_fileName = "content/" + drogon::utils::genRandomString(40) + "." + extension;			
				productJSON["product"]["description"] = _fileName;
				It->saveAs(_fileName);
			}
			else if(extension == "jpg" || extension == "png"){
				_fileName = "photos/" + drogon::utils::genRandomString(40) + "." + extension;			
				productJSON["product"]["images"][iterPhoto] = _fileName;
				It->saveAs(_fileName);
				iterPhoto++;
			}
			else{
				auto resp = HttpResponse::newRedirectionResponse("/bum");
				callback(resp);
				return;
			}

		}
		else {
			auto resp = HttpResponse::newRedirectionResponse("/bum");
			callback(resp);
			return;
		}
	}

	std::string title;
	std::string featuredText;
	std::string featuredHeader;
	std::string outOfDate;
	std::string type;
	std::string brand;
	std::string offCount;
	std::string productCount;

	unsigned int i = 0;
	std::vector<float> values;
	std::unordered_map<std::string, std::string> passedVars = sessionPtr->get<std::unordered_map<std::string, std::string>>("passedVars");
	for(const auto& n : passedVars){
		std::string firstVal = n.first;
		std::string secondVal = n.second;

		// We are doing this because somehow values in vector array
		// are mixed inside
		if(firstVal == "title"){ title = secondVal; }
		if(firstVal == "featuredText"){ featuredText = secondVal; }
		if(firstVal == "featuredHeader"){ featuredHeader = secondVal; }
		if(firstVal == "outOfDate"){ outOfDate = secondVal; }	
		if(firstVal == "type"){ type = secondVal; }
		if(firstVal == "brand"){  brand = secondVal; }
		if(firstVal == "productCount"){ productCount = secondVal; }

		size_t found = firstVal.find("offValue");
		if(found != std::string::npos){
			values.push_back(std::stof(secondVal));
		}
	}
	std::string checkIfExists = "SELECT title FROM product WHERE title='" + title + "'";

	std::sort(values.begin(), values.end(), std::greater<float>());
	for(auto a : values){
		float _price = floorf(a * 100) / 100;
		productJSON["product"]["offValues"][i] = _price;
		i++;
	}

	std::stringstream ss;
	float _price = floorf(values[0] * 100) / 100;
	ss << _price;

	auto date = trantor::Date::now();

	auto clientPtr = drogon::app().getDbClient();
	std::string uuid = drogon::utils::getUuid();
	std::string createDate = date.toCustomedFormattedString("%Y-%m-%d");
	std::string preQuery = "INSERT INTO products(title, text, featuredheader,outofdatetime, enrolleddate, maximumproductcount, isbuyable, customercount, type, brand, price, isfeatured, isverified, uuid, details) ";
	std::string lastQuery = "VALUES('" + title + "', '" + featuredText + "', '" + featuredHeader + "', '" + outOfDate + "', '" + createDate + "', '" + productCount + "', FALSE, 0, '" + type + "', '"
		+ brand + "', " + ss.str() + ", FALSE, FALSE, '" + uuid + "', '" + productJSON.toStyledString() + "')";
	std::string totalQuery = preQuery + lastQuery;

	std::cout << totalQuery << std::endl;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery);

	// std::cout << productJSON << std::endl;
	sessionPtr->erase("passedVars");

	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
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
		std::string firstParam = n.first;
		std::string secondParam = n.second;
		if(firstParam == "imgCount"){
			imageCount = std::stoi(secondParam);
		}
		std::string inputs = "<p>";
		inputs += firstParam + ": <br>" + secondParam + "<br><p><br>";
		passedVars.push_back(secondParam);
		unchangable.push_back(inputs);
	}

	for(int i = 0; i < imageCount + 1; i++){
		std::string formElement = "<input type='file' name='" + drogon::utils::genRandomString(5) + "'><br>";
		fileInputs.push_back(formElement);
	}

	std::reverse(passedVars.begin(), passedVars.end());
	std::reverse(unchangable.begin(), unchangable.end());

	sessionPtr->insert("passedVars", tempParam);
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
