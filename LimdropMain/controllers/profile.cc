#include "profile.h"
#include <limutils/PatternFiller.h>

void profile::showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey){

	Json::Value responseJson;
	/*if(req->getHeader("fromProxy") != "true"){
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}*/
	auto clientPtr = drogon::app().getDbClient();
	int _profileKey;
	std::stringstream ss(profileKey);
	ss >> _profileKey;
	if(_profileKey <= 0){
		responseJson["feedback"] = "Profil numaras� negatif olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}


	std::string totalQuery = "SELECT id, name, surname FROM accounts WHERE id=" + profileKey;
	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	auto result = f.get();
	if(result.size() == 0){
		// TODO
		// Show that there is no such profile
		responseJson["feedback"] = "B�yle bir profil mevcut de�il";
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	else{
		for(auto row : result){
			responseJson["id"] = row["id"].as<std::string>();
			responseJson["name"] = row["name"].as<std::string>();
			responseJson["surname"] = row["surname"].as<std::string>();
		}
		if (req->getHeader("isLogged") == "true") {
			// TODO
			// In case if we are alreaddy logged in
			// If the queried id is our id
			// We will show our profile with edit buttons
			std::string userID = req->getHeader("id");
			if (userID == responseJson["id"].asString()) {
				// It means our profile
				responseJson["profileOwn"] = "true";
			}
			responseJson["profileOwn"] = "false";
		}
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
	}
}


void profile::showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{
	Json::Value responseJson;

	if(req->getHeader("fromProxy") != "true"){
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if(req->getHeader("isLogged") == "true"){
		std::string id = req->getHeader("id");
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		std::string addressString;
		auto result1 = f1.get();
		for(auto row : result1){	
			addressString = row["addresses"].as<std::string>();
			std::stringstream ss(addressString);
			ss >> responseJson;
		}	
		responseJson["actionStatus"] = "true";
		std::cout << responseJson << std::endl;
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	responseJson["feedback"] = "Hesaba giri� yap�lmam��";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}

void profile::currentInfo(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	
	Json::Value responseJson;

	if(req->getHeader("fromProxy") != "true"){
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if(req->getHeader("isLogged") == "true"){
		responseJson["isloggedin"] = "true";
		responseJson["id"] = req->getHeader("id");
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	responseJson["isloggedin"] = "false";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;
}

void profile::logout(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();
	Json::Value responseJson;
	if(sessionPtr->find("isLoggedIn")){
		sessionPtr->clear();
		responseJson["feedback"] = "Cikis basarili";
		responseJson["actionStatus"] = true;
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
	}
	responseJson["feedback"] = "Hesaba giris yapilmamis";
	responseJson["actionStatus"] = false;
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);

}
