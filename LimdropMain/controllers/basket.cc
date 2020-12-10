#include "basket.h"
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
	Json::Value item;
	Json::Value secondItem;
	// TODO
	// Check if item exists
	item["basket_items"][0][0] = itemId;
	item["basket_items"][0][1] = "sdfsdf";
	item["basket_items"][0][2] = "computers";	
	item["basket_items"][0][3] = "laptop";
	item["basket_items"][0][4] = "physical";
	item["basket_items"][0][5] = "50";
	std::string formattedStr = item.toStyledString();
	Py_Initialize();
	POBJECT pyString = LIM_PSTR(formattedStr.c_str());
	POBJECT imports = LIM_PIMPORT("ex2");
	POBJECT funcAttr = LIM_PGET_ATTR(imports, "baban");
	POBJECT funResult = LIM_PFUNC_ONEARG(funcAttr, pyString);
	secondItem = PC_TILL::toString(funResult);
	Py_CLEAR(pyString);
	Py_CLEAR(imports);
	Py_CLEAR(funcAttr);
	Py_CLEAR(funResult);
	Py_FinalizeEx();

	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
	return;
}
void basket::removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){

}
//add definition of your processing function here
