#include "basket.h"
#include "limjson.h"
#include <limutils/pyutils.h>


void basket::showBasket(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	if(req->getHeader("isLogged") == "true"){
		// TODO 
		// Check if item exists
		auto clientPtr = drogon::app().getDbClient();
		std::string id = req->getHeader("id");
		std::string totalQuery = "SELECT id, basketitem FROM accounts WHERE id=" + id;
		auto f = clientPtr->execSqlAsyncFuture(totalQuery);
		auto result = f.get();
		
		for(auto row : result){
			std::string returnedResult = row["basketitem"].as<std::string>();
			if(returnedResult == ""){
				responseJson["feedback"] = "Sepette hiç ürün yok";
				responseJson["actionStatus"] = "false";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
			// std::cout << row["basketitem"].as<std::string>() << std::endl;	
			std::stringstream basketString(returnedResult);
			basketString >> responseJson;

		}
		unsigned int basketSize = responseJson["myBasket"].size();
		bool itemRemoved = false;
		for(basketSize; basketSize > 0; basketSize--){
			// Check if items in the basket are still buyable
			// If not remove them from the basket
			std::string tempProductId = responseJson["myBasket"][basketSize - 1]["id"].asString();
			std::string itemCheckQuery = "SELECT id FROM products WHERE id=" + tempProductId + " AND isbuyable=true";
			auto tempResult = clientPtr->execSqlAsyncFuture(itemCheckQuery);
			if(tempResult.get().size() == 0){
				itemRemoved = true;
				Json::Value *removedPart = new Json::Value;
				responseJson["myBasket"].removeIndex(basketSize - 1, removedPart);
				delete removedPart;
			}
		}
		if(itemRemoved){
			clientPtr->execSqlAsyncFuture("UPDATE accounts SET basketitem='" + responseJson.toStyledString() + "' WHERE id=" + id);
		}
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}

void basket::addBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	if(req->getHeader("isLogged") == "true"){
		auto clientPtr = drogon::app().getDbClient();
		std::string id = req->getHeader("id");
		std::string totalQuery1 = "SELECT id, details FROM products WHERE id=" + itemId + " AND isbuyable=true;";
		auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
		auto result1 = f1.get();
		if(result1.size() == 0){
			responseJson["feedback"] = "Böyle bir ürün bulunmamaktadır";
			responseJson["actionStatus"] = "false";
			auto resp = HttpResponse::newHttpJsonResponse(responseJson);
			callback(resp);
			return;
		}
		std::string proId;
		Json::Value temporaryProduct;
		Json::Value tempBasket;
		for(auto row : result1){
			proId = row["id"].as<std::string>();
			std::stringstream productString(row["details"].as<std::string>());
			productString >> temporaryProduct;
		}
		
		std::string totalQuery2 = "SELECT basketitem FROM accounts WHERE id=" + id;
		auto f2 = clientPtr->execSqlAsyncFuture(totalQuery2);
		auto result2 = f2.get();
		for(auto row : result2){
			
			std::string resultantBasket = row["basketitem"].as<std::string>();
			unsigned int sizeOfBasket = 0;
			if(resultantBasket == ""){

			}
			else{
				std::stringstream tempBasketString(resultantBasket);
				tempBasketString >> tempBasket;
				sizeOfBasket = tempBasket["myBasket"].size();
			}

			tempBasket["myBasket"][sizeOfBasket]["id"] = proId;
			for(auto &n : temporaryProduct["properties"].getMemberNames()){
				tempBasket["myBasket"][sizeOfBasket]["properties"][n.data()] = temporaryProduct["properties"][n.data()];
			}
			tempBasket["myBasket"][sizeOfBasket]["basketImage"] = temporaryProduct["images"][0];
			tempBasket["myBasket"][sizeOfBasket]["title"] = temporaryProduct["title"];
			tempBasket["myBasket"][sizeOfBasket]["price"] = temporaryProduct["offVals"][0]["L0"];
			
			std::string totalQuery3 = "UPDATE accounts SET basketitem='" + tempBasket.toStyledString() + "' WHERE id=" + id;
			auto f3 = clientPtr->execSqlAsyncFuture(totalQuery3);
		}
		responseJson["feedback"] = "Urun eklendi";
		responseJson["productId"] = proId; 
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}
void basket::removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if(req->getHeader("isLogged") == "true"){
		auto clientPtr = drogon::app().getDbClient();
		std::string id = req->getHeader("id");

		std::string totalQuery1 = "SELECT basketitem FROM accounts WHERE id=" + id;
		std::string tempBasketSTR;
		auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
		auto result1 = f1.get();
		for(auto row : result1){
			tempBasketSTR = row["basketitem"].as<std::string>();
			if(tempBasketSTR == ""){
				responseJson["feedback"] = "Sepet zaten boş";
				responseJson["actionStatus"] = "false";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
			else{
				Json::Value _tempBasket;
				std::stringstream tempBasketSTRToJson(tempBasketSTR);
				tempBasketSTRToJson >> _tempBasket;
				unsigned int BasketSize = _tempBasket["myBasket"].size();
				unsigned int BasketIterator = 0;
				bool isItemFound = false;
				std::cout << BasketSize << std::endl;
				for(BasketIterator; BasketIterator < BasketSize; BasketIterator++){
					if(_tempBasket["myBasket"][BasketIterator]["id"] == itemId){
					 	isItemFound = true;
					 	break;
					}
				}
				if(!isItemFound){
					responseJson["feedback"] = "Sepette böyle bir ürün yok";
					responseJson["actionStatus"] = "false";
					auto resp = HttpResponse::newHttpJsonResponse(responseJson);
					callback(resp);
					return;
				}
				Json::Value *removeVersion = new Json::Value;

				_tempBasket["myBasket"].removeIndex(BasketIterator, removeVersion);
				delete removeVersion;

				std::string totalQuery2;
				if(_tempBasket["myBasket"].size() == 0){
					totalQuery2 = "UPDATE accounts SET basketitem=NULL WHERE id=" + id;
				}
				else{
					totalQuery2 = "UPDATE accounts SET basketitem='" + _tempBasket.toStyledString() + "' WHERE id=" + id;
				}	
				auto f2 = clientPtr->execSqlAsyncFuture(totalQuery2);
				responseJson["feedback"] = "Ürün başarıyla kaldırıldı";
				responseJson["actionStatus"] = "true";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
		}
	}
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}
//add definition of your processing function here
