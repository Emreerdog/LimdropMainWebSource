#include "product.h"
#include "limjson.h"
#include "sutils.h"

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
	std::string totalQuery1 = "SELECT id, isbuyable, customercount, price, isverified, details FROM products WHERE id=" + itemId + " AND isverified=TRUE";
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
	bool currentBuyableStatus;
	for(auto row : result1){
		std::stringstream sDescription(row["details"].as<std::string>());
		sDescription >> responseJson;
		responseJson["id"] = itemId;
		responseJson["customercount"] = row["customercount"].as<std::string>();
		responseJson["price"] = row["price"].as<std::string>();
		responseJson["isverified"] = row["isverified"].as<std::string>();
		currentBuyableStatus = row["isbuyable"].as<bool>();
	}
	Json::Value serverTime = sutils::getSVTime();
	const char* currentDate = serverTime["date"].asCString();
	const char* currentTime = serverTime["time"].asCString();
	if(currentBuyableStatus){
		const char* productDate = responseJson["outOfDate"].asCString();
		const char* productTime = responseJson["outOfDateTime"].asCString();
		int comparisonResult = strcmp(currentDate, productDate);
		switch(comparisonResult){
			case 1:{
				// TODO
				// Refund the difference between bought price and current price
				// Add the product to the old products database
				std::string updateBuyableQuery = "UPDATE products SET isbuyable=false WHERE id=" + itemId;
				clientPtr->execSqlAsyncFuture(updateBuyableQuery);
				responseJson["isbuyable"] = "false";
				break;
			}
			
			case -1:{
				responseJson["isbuyable"] = "true";
				break;
			}
			
			case 0:{
				if(strcmp(currentTime, productTime) == 0 || strcmp(currentTime, productTime) == 1){
					// TODO
					// Refund the difference between bought price and current price
					// Add the product to the old products database
					std::string updateBuyableQuery = "UPDATE products SET isbuyable=false WHERE id=" + itemId;
					clientPtr->execSqlAsyncFuture(updateBuyableQuery);
					responseJson["isbuyable"] = "false";
				}
				else{
					responseJson["isbuyable"] = "true";
				}
				break;
			}
		}
	}
	else{
		// Do nothing
	}
	responseJson["serverDate"] = currentDate;
	responseJson["serverTime"] = currentTime;
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
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
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		std::string totalQuery2 = "SELECT id, details FROM products WHERE isverified=TRUE AND isbuyable=TRUE ORDER BY random() LIMIT 3";
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
	std::string totalQuery1 = "SELECT id, details FROM products WHERE type='" + category + "' AND isverified=TRUE AND isbuyable=TRUE";
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
	Json::Value serverTime = sutils::getSVTime();
	const char* currentDate = serverTime["date"].asCString();
	const char* currentTime = serverTime["time"].asCString();
	responseJson["actionStatus"] = "true";
	responseJson["serverDate"] = currentDate;
	responseJson["serverTime"] = currentTime;
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
	std::string totalQuery1 = "SELECT DISTINCT type FROM products WHERE isverified='TRUE' AND isbuyable=TRUE";
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
