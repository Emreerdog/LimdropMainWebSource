#include "factory.h"

void factory::changeUserProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}	
void factory::changeUserPassword(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void factory::changeUserPasswordEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void factory::changeProductParams(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void factory::addAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string city, std::string address, std::string phoneNumber, std::string zipcode){	
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		std::string username = sessionPtr->get<std::string>("username");	
		unsigned int addressCount = 0;
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE username='" + username + "'");
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
		addresses["addresses"][addressCount]["city"] = city;
    		addresses["addresses"][addressCount]["address"] = address;
    		addresses["addresses"][addressCount]["phonenumber"] = phoneNumber;
    		addresses["addresses"][addressCount]["zipcode"] = zipcode;
		clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses='" + addresses.toStyledString()  + "' WHERE username='" + username + "'");
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}
void factory::removeAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex){

	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){

		std::string username = sessionPtr->get<std::string>("username");
		unsigned int _addressIndex;
		auto clientPtr = drogon::app().getDbClient();
		std::stringstream ss(addressIndex);
		ss >> _addressIndex;
		Json::Value addresses;
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE username='" + username + "'");
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
					std::cout << "Address removing failed successfully" << std::endl;
				}
				else{
					std::cout << "Successfully removed address" << std::endl;
					Address = addresses.toStyledString();
					clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses='" + Address + "' WHERE username='" + username + "'");
				}
				auto resp = HttpResponse::newRedirectionResponse("/profile/address/");
				callback(resp);
				return;
			}
		}
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}



































//add definition of your processing function here
