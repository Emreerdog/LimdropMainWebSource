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
	std::string totalQuery1 = "SELECT id, isbuyable, customercount, price, isverified, details FROM products WHERE id=" + itemId + "";
	std::cout << totalQuery1 << std::endl;
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
		std::stringstream sDescription(row["details"].as<std::string>());
		sDescription >> responseJson;
		responseJson["id"] = itemId;
		responseJson["isbuyable"] = row["isbuyable"].as<std::string>();
		responseJson["customercount"] = row["customercount"].as<std::string>();
		responseJson["price"] = row["price"].as<std::string>();
		responseJson["isverified"] = row["isverified"].as<std::string>();

	}
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
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

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id, details FROM products WHERE isfeatured=TRUE";
	std::cout << totalQuery1 << std::endl;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		std::string totalQuery2 = "SELECT id, details FROM products ORDER BY random() LIMIT 3";
		auto f2 = clientPtr->execSqlAsyncFuture(totalQuery2);
		result1 = f2.get();
	}

	unsigned int i = 0;
	for(auto row : result1){
		Json::Value featuredProducts;
		std::stringstream sDescription(row["details"].as<std::string>());
		sDescription >> featuredProducts;
		responseJson["featured"][i] = featuredProducts;
		responseJson["featured"][i]["id"] = row["id"].as<std::string>();
		i++;
	}
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
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
	std::string totalQuery1 = "SELECT id, details FROM products WHERE type='" + category + "'";
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		
		responseJson["feedback"] = "Bu kategoride ürün bulunmamaktadır";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	unsigned int i = 0;
	for(auto row : result1){
		Json::Value tempDetails;

		std::stringstream detailsToJson(row["details"].as<std::string>());
		detailsToJson >> tempDetails;
		responseJson["productJson"][i] = tempDetails;
		responseJson["productJson"][i]["id"] = row["id"].as<std::string>();
		i++;
	}
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;
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

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT DISTINCT type FROM products";
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	int i = 0;
	for(auto row : result1){
		responseJson["categories"][i] = row["type"].as<std::string>();
		i++;
	}

	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
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