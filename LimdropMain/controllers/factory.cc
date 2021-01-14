#include "factory.h"

void factory::changeUserProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}	
void factory::changeUserPassword(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void factory::changeUserPasswordEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void factory::changeProductParams(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void factory::addAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string city, std::string ilce,std::string address, std::string phoneNumber, std::string zipcode){	
	auto sessionPtr = req->session();
	Json::Value resultantJSON;
	std::cout << "Request send" << std::endl;
	if(sessionPtr->find("isLoggedIn")){
		std::string id = sessionPtr->get<std::string>("id");	
		unsigned int addressCount = 0;
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		auto result1 = f1.get();
		
		Json::Value addresses;
		for(auto row : result1){
			std::string addStr = row["addresses"].as<std::string>(); 
			if(addStr == ""){
				addressCount = 0;
			}
			else{	
				std::stringstream ss(addStr);
				ss >> addresses;
				addressCount = addresses["addresses"].size();
			}
		}	
		addresses["addresses"][addressCount]["Sehir"] = city;
		addresses["addresses"][addressCount]["Ilce"] = ilce;
    		addresses["addresses"][addressCount]["acikAdres"] = address;
    		addresses["addresses"][addressCount]["telefonNumara"] = phoneNumber;
    		addresses["addresses"][addressCount]["postaKodu"] = zipcode;
		clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses='" + addresses.toStyledString()  + "' WHERE id='" + id);
		resultantJSON["feedback"] = "Adres başarıyla eklendi!";
		resultantJSON["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(resultantJSON);
		callback(resp);
		return;
	}
	resultantJSON["feedback"] = "User not logged in";
	resultantJSON["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(resultantJSON);
	callback(resp);
}
void factory::removeAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex){

	auto sessionPtr = req->session();
	Json::Value resultantJSON;
//
	if(sessionPtr->find("isLoggedIn")){

		std::string id = sessionPtr->get<std::string>("id");
		unsigned int _addressIndex;
		auto clientPtr = drogon::app().getDbClient();
		std::stringstream ss(addressIndex);
		ss >> _addressIndex;
		Json::Value addresses;
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		auto result1 = f1.get();
		std::string Address;
		for(auto row : result1){
			Address = row["addresses"].as<std::string>();
			if(Address == ""){
				// There no addresses to remove
				std::cout << "There are no addresses to remove" << std::endl;
				auto resp = HttpResponse::newRedirectionResponse("/profile/address/");
				callback(resp);
				return;
			}
			else{
				std::stringstream strToJson(Address);
				strToJson >> addresses;
				int addressCount =  addresses["addresses"].size();
				/*if(_addressIndex > addressCount || _addressIndex < addressCount){
					// Given index is out of bounds
					std::cout << "Given index is out of bounds" << std::endl;
					auto resp = HttpResponse::newRedirectionResponse("/profile/address/");
					callback(resp);
					return;
				}*/
				Json::Value asd;
				std::cout << addresses << std::endl;
				std::cout << addresses["addresses"].size() << std::endl;
				std::cout << _addressIndex << std::endl;
				
				if(addresses["addresses"].removeIndex(_addressIndex, &asd)){
					resultantJSON["feedback"] = "Address removing failed";
					resultantJSON["actionStatus"] = "false";
					auto resp = HttpResponse::newHttpJsonResponse(resultantJSON);
					callback(resp);
					return;
				}
				else{
					std::cout << "Successfully removed address" << std::endl;
					Address = addresses.toStyledString();
					clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses='" + Address + "' WHERE id=" + id);
				}
				resultantJSON["feedback"] = "Successfully removed address";
				resultantJSON["actionStatus"] = "true";
				auto resp = HttpResponse::newHttpJsonResponse(resultantJSON);
				callback(resp);
				return;
			}
		}
	}
	resultantJSON["feedback"] = "User not logged in";
	resultantJSON["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(resultantJSON);
	callback(resp);
}



































//add definition of your processing function here
