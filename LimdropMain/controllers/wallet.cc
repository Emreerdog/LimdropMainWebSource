#include "wallet.h"


void wallet::show(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Query the database and print the currency the account has
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}

void wallet::addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Check post arguments if they are valid
		// Do all the money operations via embedd python
	}
	// TODO
	// Report the attempt to add money to wallet without logging in
	// Report the attempt of outside post request
	auto resp = HttpResponse::newRedirectionResponse("/");	
	callback(resp);
}
//add definition of your processing function here
