#include "basket.h"
#include "limjson.h"
#include <limutils/pyutils.h>


void basket::showBasket(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	Json::Value responseJson;
	if(sessionPtr->find("isLoggedIn")){
		// TODO 
		// Check if item exists
		auto clientPtr = drogon::app().getDbClient();
		std::string id = sessionPtr->get<std::string>("id");
		std::string totalQuery = "SELECT basketitem FROM accounts WHERE id=" + id;
		auto f = clientPtr->execSqlAsyncFuture(totalQuery);
		auto result = f.get();
		
		for(auto row : result){
			if(row["basketitem"].as<std::string>() == ""){
				responseJson["feedback"] = "Sepette hiç ürün yok";
				responseJson["actionStatus"] = "false";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
			// std::cout << row["basketitem"].as<std::string>() << std::endl;	
			Basket PB(row["basketitem"].as<std::string>());
			responseJson = PB.getBasket();

			
		}	
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
}

void basket::addBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		auto clientPtr = drogon::app().getDbClient();
		std::string id = sessionPtr->get<std::string>("id");
		std::string totalQuery1 = "SELECT id, title, type, brand, price, details FROM products WHERE id=" + itemId;
		auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
		auto result1 = f1.get();
		if(result1.size() == 0){
			auto resp = HttpResponse::newRedirectionResponse("/bum");
			callback(resp);
			return;
		}
		std::string proId;
		std::string proTitle;
		std::string proType;
		std::string proBrand;
		std::string proPrice;
		std::string proDetails;
		for(auto row : result1){
			proId = row["id"].as<std::string>();
			proTitle = row["title"].as<std::string>();
			proType = row["type"].as<std::string>();
			proBrand = row["brand"].as<std::string>();
			proPrice = row["price"].as<std::string>();
			proDetails = row["details"].as<std::string>();
		}
		ProductJSON PJ(proDetails);
		std::string proImage = PJ.getImagePaths()[0];
		std::string totalQuery2 = "SELECT basketitem FROM accounts WHERE id=" + id;
		auto f2 = clientPtr->execSqlAsyncFuture(totalQuery2);
		auto result2 = f2.get();
		for(auto row : result2){
			Basket resultPB;
			if(row["basketitem"].as<std::string>() == ""){
				resultPB.addItem(proId, proTitle, proType, proBrand, EITEM_TYPE::PHYSICAL, proPrice, proImage);
			}
			else{
				std::string currentBasket = row["basketitem"].as<std::string>();
				Basket PB(currentBasket);
				PB.addItem(proId, proTitle, proType, proBrand, EITEM_TYPE::PHYSICAL, proPrice, proImage);
				resultPB = PB;		
			}
			std::string tempBasket = resultPB.getBasketAsString();
			std::string totalQuery3 = "UPDATE accounts SET basketitem='" + tempBasket + "' WHERE id=" + id;
			auto f3 = clientPtr->execSqlAsyncFuture(totalQuery3);
		}
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
	return;
}
void basket::removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		auto clientPtr = drogon::app().getDbClient();
		std::string id = sessionPtr->get<std::string>("id");

		std::string totalQuery1 = "SELECT basketitem FROM accounts WHERE id=" + id;
		std::string tempBasket;
		auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
		auto result1 = f1.get();
		for(auto row : result1){
			tempBasket = row["basketitem"].as<std::string>();
			if(tempBasket == ""){
				std::cout << "There are no items in basket" << std::endl;
			}
			else{
				Basket PB(tempBasket);
				PB.removeItem(itemId);
				std::string totalQuery2 = "UPDATE accounts SET basketitem='" + PB.getBasketAsString() + "' WHERE id=" + id;
				auto f2 = clientPtr->execSqlAsyncFuture(totalQuery2);
			}
			auto resp = HttpResponse::newRedirectionResponse("/basket/");
			callback(resp);
			return;
		}
	}
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
}
//add definition of your processing function here
