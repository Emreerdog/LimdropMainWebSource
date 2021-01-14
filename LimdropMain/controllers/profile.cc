#include "profile.h"
#include <limutils/PatternFiller.h>

void profile::showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey){

	auto sessionPtr = req->session();
	Json::Value responseJson;
	std::string checkString = "Hello guyz";
	auto clientPtr = drogon::app().getDbClient();
	int _profileKey;
	std::stringstream ss(profileKey);
	ss >> _profileKey;
	if(_profileKey <= 0){
		responseJson["feedback"] = "Profil numaras¿ negatif olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	sessionPtr->insert("myVar", checkString);
	std::string key1 = "isLogged";
	std::cout << req->getHeader(key1) << std::endl;
	std::cout << sessionPtr->get<std::string>("myVar") << std::endl;
	std::string totalQuery = "SELECT id, name, surname FROM accounts WHERE id=" + profileKey;
	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	auto result = f.get();
	if(result.size() == 0){
		// TODO
		// Show that there is no such profile
		responseJson["feedback"] = "Böyle bir profil mevcut de¿il";
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
		if (sessionPtr->find("id")) {
			// TODO
			// In case if we are alreaddy logged in
			// If the queried id is our id
			// We will show our profile with edit buttons
			std::string userID = sessionPtr->get<std::string>("id");
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
	auto sessionPtr = req->session();
	Json::Value resultantJson;
	if(sessionPtr->find("isLoggedIn")){
		std::string id = sessionPtr->get<std::string>("id");
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		std::string addressString;
		auto result1 = f1.get();
		for(auto row : result1){	
			addressString = row["addresses"].as<std::string>();
			std::stringstream ss(addressString);
			ss >> resultantJson;
		}	
		resultantJson["actionStatus"] = "true";
		std::cout << resultantJson << std::endl;
		auto resp = HttpResponse::newHttpJsonResponse(resultantJson);
		callback(resp);
		return;
	}
	resultantJson["feedback"] = "Hesaba giriþ yapýlmamýþ";
	resultantJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(resultantJson);
	callback(resp);
}

void profile::currentInfo(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	
	auto sessionPtr = req->session();
	Json::Value responseJson;

	if(sessionPtr->find("isLoggedIn")){
		responseJson["isloggedin"] = "true";
		responseJson["id"] = sessionPtr->get<std::string>("id");
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	responseJson["isloggedin"] = "false";
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
