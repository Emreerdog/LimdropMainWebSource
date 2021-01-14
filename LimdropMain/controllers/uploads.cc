#include "uploads.h"
#include "limjson.h"
#include <sstream>
#include <limutils/PatternFiller.h>
#include <algorithm>

void uploads::upload_product(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	// Tis is experimental
	Json::Value ourProduct;
//
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

	ManualPatternFiller MPF(1, "_isdisplayed");
	std::string content = MPF.fillPatterns("addproduct.html", "yes");

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(content);
	callback(resp);
}


void uploads::upload_files(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	if(!sessionPtr->find("passedVars")){
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
		std::cout << "First Val: " << firstVal << " type=" << typeid(firstVal).name()  << " correspons to=" << secondVal << std::endl;
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
			float _offVals;
			std::stringstream OVstream(secondVal);
			OVstream >> _offVals;
			if(_offVals <= 0){
				auto resp = HttpResponse::newRedirectionResponse("/uploads/");
				callback(resp);
				return;
			}
			values.push_back(_offVals);
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

	auto resp = HttpResponse::newRedirectionResponse("/uploads/");
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
		if(secondParam == ""){
			// Input fields cannot be empty
			std::cout << "Input fields cannot be left empty" << std::endl;
			auto resp = HttpResponse::newRedirectionResponse("/uploads/");
			callback(resp);
			return;
		}

		size_t found = firstParam.find("offValue");
		if (found != std::string::npos) {
			float _offVals;
			std::stringstream OVstream(secondParam);
			OVstream >> _offVals;
			if (_offVals <= 0) {
				std::cout << "Negative values are not okay" << std::endl;
				auto resp = HttpResponse::newRedirectionResponse("/uploads/");
				callback(resp);
				return;
			}
		}

		if(firstParam == "imgCount"){
			int _imageCount = 0;
			std::stringstream imageCountStream(secondParam);
			imageCountStream >> _imageCount;
			if(_imageCount < 2 || _imageCount > 20){
				std::cout << "Image count is out of bounds" << std::endl;
				auto resp = HttpResponse::newRedirectionResponse("/uploads/");
				callback(resp);
				return;
			}
			imageCount = _imageCount;	
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
