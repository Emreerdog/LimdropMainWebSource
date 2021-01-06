#include "activation.h"


void activation::profileActivation(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string activationCode){


	auto clientPtr = drogon::app().getDbClient();
	std::string Query = "SELECT id FROM accounts WHERE uuid ='"+ activationCode + "'";
	
	auto f = clientPtr->execSqlAsyncFuture(Query);	
	if(f.get().size() == 0){
		auto resp = HttpResponse::newRedirectionResponse("/bum");
		callback(resp);
		return;
	}
	else{
		std::string _Query = "UPDATE accounts SET isverified = TRUE WHERE uuid = '" + activationCode + "'";
		auto _f = clientPtr->execSqlAsyncFuture(_Query);

		auto resp = HttpResponse::newNotFoundResponse();
		callback(resp);
		return;
	}
	
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
} 

void activation::productActivation(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string activationCode){
	
	auto clientPtr = drogon::app().getDbClient();
	std::string Query = "SELECT id FROM products WHERE uuid = '" + activationCode + "'";

	auto f = clientPtr->execSqlAsyncFuture(Query);
	if(f.get().size() == 0){
		auto resp = HttpResponse::newRedirectionResponse("/bum");
		callback(resp);
		return;	
	}
	else{
		std::string _Query = "UPDATE products SET isverified = TRUE WHERE uuid = '" + activationCode + "'";
		auto _f = clientPtr->execSqlAsyncFuture(_Query);
		std::cout << "Product is verified" << std::endl;

		auto resp = HttpResponse::newNotFoundResponse();
		callback(resp);
		return;
	}
} 

//add definition of your processing function here
