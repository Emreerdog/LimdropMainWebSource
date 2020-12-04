#include "basket.h"


void basket::showBasket(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	

}
void basket::addBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){

}
void basket::removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){

}
//add definition of your processing function here
