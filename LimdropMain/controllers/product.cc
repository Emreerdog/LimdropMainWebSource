#include "product.h"
#include "limjson.h"

bool product::checkIfProductExists(std::string itemId){
	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id FROM products WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		return false;
	}
	return true;
}

void product::details(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId)
{
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string _itemId = itemId;
	// Check if it is number
	for(int i = 0; i < _itemId.length(); i++){
		if(!(_itemId[i] >= '0' && _itemId[i] <= '9')){
			responseJson["feedback"] = "Girilen parametre say� de�il";
			responseJson["actionStatus"] = "false";
			auto resp = HttpResponse::newHttpJsonResponse(responseJson);
			callback(resp);
			return;
		}
	}
	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id, title, isfeatured, outofdatetime, maximumproductcount, isbuyable, customercount, type, brand, price, details FROM products WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		responseJson["id"] = itemId;
		responseJson["feedback"] = "B�yle bir �r�n bulunmamaktad�r";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string detailsJSON;
	for(auto row : result1){
		responseJson["id"] = itemId;
		responseJson["title"] = row["title"].as<std::string>();
		responseJson["isfeatured"] = row["isfeatured"].as<std::string>();
		responseJson["outofdatetime"] = row["outofdatetime"].as<std::string>();
		responseJson["maximumproductcount"] = row["maximumproductcount"].as<std::string>();
		responseJson["isbuyable"] = row["isbuyable"].as<std::string>();
		responseJson["customercount"] = row["customercount"].as<std::string>();
		responseJson["type"] = row["type"].as<std::string>();
		responseJson["brand"] = row["brand"].as<std::string>();
		responseJson["price"] = row["price"].as<std::string>();
		detailsJSON = row["details"].as<std::string>();

	}
	ProductJSON PJ(detailsJSON);
	std::vector<std::string> imagePaths = PJ.getImagePaths();
	std::vector<std::string> values = PJ.getValues();
	unsigned int imageCount = PJ.getImageCount();
	unsigned int valueCount = PJ.getOvCount();

	unsigned int j = 0;
	std::vector<std::string>::iterator It1;

	// Off value iterator
	// Result will be sequential
	for(It1 = values.begin(); It1 != values.end(); It1++){
		std::stringstream ss;
		std::stringstream ss1(*It1);
		ss << j;
		std::string valueOutput = "OffValue" + ss.str();
		
		float beforeFloor;
		ss1 >> beforeFloor;
		float floored = floorf(beforeFloor * 100) / 100;
		//std::cout << valueOutput << floored << std::endl;
		responseJson[j][valueOutput] = floored;
		j++;
	}
	j = 0;
//	// Image path iterator
	// Result will be sequential
	std::vector<std::string>::iterator It2;
	for(It2 = imagePaths.begin(); It2 != imagePaths.end(); It2++){
		std::stringstream ss;
		ss << j;
		std::string pathOutput = "ImagePath" + ss.str();
		//std::cout << pathOutput << std::endl;
		responseJson[j][pathOutput] = *It2;
		j++;
	}
	imagePaths.clear();
	values.clear();

	responseJson["feedback"] = "Ürün görüntülendi";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;
}

void product::makeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::stringstream ss(itemId);
	int checkIfNum = 0;
	ss >> checkIfNum;
	if(checkIfNum == 0){
		responseJson["feedback"] = "Ürün numarası 0 olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if(!checkIfProductExists(itemId)){
		responseJson["feedback"] = "Böyle bir ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "UPDATE products SET isfeatured = TRUE WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	responseJson["id"] = itemId;
	responseJson["feedback"] = "Ürün öne çıkanlara eklendi";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;

}
void product::featuredList(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}
void product::removeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::stringstream ss(itemId);
	int checkIfNum = 0;
	ss >> checkIfNum;
	if(checkIfNum == 0){
		responseJson["feedback"] = "Ürün numarası 0 olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if(!checkIfProductExists(itemId)){
		responseJson["feedback"] = "Böyle bir ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "UPDATE products SET isfeatured = FALSE WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	responseJson["id"] = itemId;
	responseJson["feedback"] = "Ürün öne çıkanlardan kaldırıldı";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;
}
void product::getAllOnCategory(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string category){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id, title, isfeatured, outofdatetime, maximumproductcount, isbuyable, customercount, type, brand, price, details FROM products WHERE type='" + category + "'";
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		
		responseJson["feedback"] = "Bu kategoride ürün bulunmamaktadır";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}
void product::getAllCategories(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}
void product::getAllFinishedDrops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}
void product::getOnGoingDrops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}