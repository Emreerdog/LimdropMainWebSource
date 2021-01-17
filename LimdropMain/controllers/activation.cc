#include "activation.h"


void activation::profileActivation(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string activationCode){
	auto clientPtr = drogon::app().getDbClient();
	Json::Value responseJson;
	std::string Query = "SELECT id FROM accounts WHERE uuid ='"+ activationCode + "'";
	
	auto f = clientPtr->execSqlAsyncFuture(Query);	
	if(f.get().size() == 0){
		responseJson["feedback"] = "Onay kodu profil ile eşleşmiyor";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	else{
		std::string _Query = "UPDATE accounts SET isverified = TRUE WHERE uuid = '" + activationCode + "'";
		auto _f = clientPtr->execSqlAsyncFuture(_Query);
//
		responseJson["feedback"] = "Hesabın onaylandı";
        responseJson["actionStatus"] = "true";
        auto resp = HttpResponse::newHttpJsonResponse(responseJson);
        callback(resp);
        return;
	}
} 

void activation::productActivation(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string activationCode){
	
	auto clientPtr = drogon::app().getDbClient();
	std::string Query = "SELECT id FROM products WHERE uuid = '" + activationCode + "'";
	Json::Value responseJson;

	auto f = clientPtr->execSqlAsyncFuture(Query);
	if(f.get().size() == 0){
		responseJson["feedback"] = "Onay kodu ürün ile eşleşmiyor";
                responseJson["actionStatus"] = "false";
                auto resp = HttpResponse::newHttpJsonResponse(responseJson);
                callback(resp);
                return;
	}
	else{
		std::string _Query = "UPDATE products SET isverified = TRUE WHERE uuid = '" + activationCode + "'";
		auto _f = clientPtr->execSqlAsyncFuture(_Query);
		responseJson["feedback"] = "Ürün onaylandı";
        responseJson["actionStatus"] = "true";
        auto resp = HttpResponse::newHttpJsonResponse(responseJson);
        callback(resp);
        return;
	}
} 

//add definition of your processing function here
