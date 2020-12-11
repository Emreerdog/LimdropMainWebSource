#include "basket.h"
#include "limjson.h"
#include <limutils/pyutils.h>


void basket::showBasket(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	// TODO
	// Check if item exists

}

void basket::addBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
	
	}
	else{
		auto resp = HttpResponse::newNotFoundResponse();
		callback(resp);
		return;
	}
}
void basket::removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){

}
//add definition of your processing function here
