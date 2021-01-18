#include "uploads.h"
#include "limjson.h"
#include <sstream>
#include <limutils/PatternFiller.h>
#include <algorithm>

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

void uploads::enterprops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	
	Json::Value responseJson;
	

	std::cout << req->getPath() << std::endl;
	std::cout << req->getMatchedPathPattern() << std::endl;
	responseJson["title"] = req->getParameter("title");
	responseJson["featuredheader"] = req->getParameter("htitle");
	responseJson["text"] = req->getParameter("htext");
	responseJson["type"] = req->getParameter("type");
	responseJson["brand"] = req->getParameter("brand");
	responseJson["propertyCount"] = req->getParameter("propertyCount");
	responseJson["layerCount"] = req->getParameter("layerCount");
	responseJson["customerCount"] = req->getParameter("customerCount");
	responseJson["imageCount"] = req->getParameter("imageCount");
	responseJson["outOfDate"] = req->getParameter("outofdate");
	responseJson["outOfDateTime"] = req->getParameter("outofdatetime");

	int _layerCount = 0;
	int _propertyCount = 0;
	std::stringstream ssLayer(responseJson["layerCount"].asString());
	ssLayer >> _layerCount;
	std::stringstream ssProperty(responseJson["propertyCount"].asString());
	ssProperty >> _propertyCount;
	if(_layerCount <= 3){
		responseJson["feedback"] = "Katman sayısı en az 4 olmalıdır";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	for(int i = 0; i < _layerCount; i++){
		float presentValue = 0.0f;

		std::string currentLayer = "L" + std::to_string(i);
		std::string currentLayerValue = req->getParameter(currentLayer);
		std::stringstream ss2(currentLayerValue);
		ss2 >> presentValue;
		responseJson["offVals"][i][currentLayer] = presentValue;
	}

	for(int i = 0; i < _propertyCount; i++){
		std::string pLeft = req->getParameter("PL" + std::to_string(i));
		std::string pRight = req->getParameter("PR" + std::to_string(i));
		responseJson["properties"][pLeft] = pRight;
	}
	auto sessionPtr = req->session();
	sessionPtr->erase("productData");
	sessionPtr->insert("productData", responseJson);

	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}

void uploads::yukle(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	Json::Value productJSON = sessionPtr->get<Json::Value>("productData");
	sessionPtr->erase("productData");

	drogon::MultiPartParser mpp;
	mpp.parse(req);

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
				productJSON["description"] = _fileName;
				It->saveAs(_fileName);
			}
			else if(extension == "jpg" || extension == "png"){
				_fileName = "photos/" + drogon::utils::genRandomString(40) + "." + extension;			
				productJSON["images"][iterPhoto] = _fileName;
				It->saveAs(_fileName);
				iterPhoto++;
			}
			else{
				responseJson["feedback"] = "Fotoğraf uzantıları yalnızca .jpg, .png olabilir. İçerik dosyası uzantısı yalnızca .html olabilir";
				responseJson["actionStatus"] = "false";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}

		}
		else {
			responseJson["feedback"] = "Uzantısı eksik dosya var";
			responseJson["actionStatus"] = "false";
			auto resp = HttpResponse::newHttpJsonResponse(responseJson);
			callback(resp);
			return;
		}
	}

	auto date = trantor::Date::now();
	std::string uuid = drogon::utils::getUuid();
	std::string createDate = date.toCustomedFormattedString("%Y-%m-%d");

	std::string preQuery = "INSERT INTO products(enrolleddate, maximumproductcount, isbuyable, customercount, price, isfeatured, isverified, uuid, details, type) ";
	std::string lastQuery = "VALUES('" + createDate + "', " + productJSON["customerCount"].asString() + ", FALSE, 0, " + productJSON["offVals"][0]["L0"].asString() + ", FALSE, FALSE, '" + uuid + "', '" + productJSON.toStyledString() + "', '" + productJSON["type"].asString() + "')";
	std::string totalQuery = preQuery + lastQuery;

	auto clientPtr = drogon::app().getDbClient();
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery);

	responseJson["feedback"] = "Ürün yüklendi";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}

