#include "factory.h"

void factory::showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if (req->getHeader("isLogged") == "true"){
		std::string id = req->getHeader("id");
		unsigned int addressCount = 0;
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		auto result1 = f1.get();

		for(auto row : result1){
			std::string addressString = row["addresses"].as<std::string>();
			if(addressString == ""){
				responseJson["feedback"] = "Hiç adresin yok";
				responseJson["actionStatus"] = "false";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
			std::stringstream _addressString(addressString);
			_addressString >> responseJson;
		}
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}


void factory::addAddress(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, std::string city, std::string ilce, std::string address, std::string phoneNumber, std::string zipcode) {

	Json::Value responseJson;
	
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if (req->getHeader("isLogged") == "true") {
		std::string id = req->getHeader("id");
		unsigned int addressCount = 0;
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		auto result1 = f1.get();

		Json::Value addresses;
		for (auto row : result1) {
			std::string addStr = row["addresses"].as<std::string>();
			if (addStr == "") {
				addressCount = 0;
			}
			else {
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
		clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses='" + addresses.toStyledString() + "' WHERE id=" + id);
		responseJson["feedback"] = "Adres başarıyla eklendi!";
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}
void factory::removeAddress(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, std::string addressIndex) {

	auto sessionPtr = req->session();
	Json::Value responseJson;
	if (req->getHeader("fromProxy") != "true") {
		responseJson["feedback"] = "Illegal request has been sent";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	if (req->getHeader("isLogged") == "true") {

		std::string id = req->getHeader("id");
		unsigned int _addressIndex;
		auto clientPtr = drogon::app().getDbClient();
		std::stringstream ss(addressIndex);
		ss >> _addressIndex;
		Json::Value addresses;
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE id=" + id);
		auto result1 = f1.get();
		std::string Address;
		for (auto row : result1) {
			Address = row["addresses"].as<std::string>();
			if (Address == "") {
				// There no addresses to remove
				responseJson["feedback"] = "Hic adres yok";
				responseJson["actionStatus"] = "false";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
			else {
				std::stringstream strToJson(Address);
				strToJson >> addresses;
				int addressCount = addresses["addresses"].size();
				/*if(_addressIndex > addressCount || _addressIndex < addressCount){
					// Given index is out of bounds
					std::cout << "Given index is out of bounds" << std::endl;
					auto resp = HttpResponse::newRedirectionResponse("/profile/address/");
					callback(resp);
					return;
				}*/
				Json::Value asd;

				if (!addresses["addresses"].removeIndex(_addressIndex, &asd)) {
					responseJson["feedback"] = "Address removing failed";
					responseJson["actionStatus"] = "false";
					auto resp = HttpResponse::newHttpJsonResponse(responseJson);
					callback(resp);
					return;
				}
				else {
					if(addresses["addresses"].size() == 0){
						clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses=NULL WHERE id=" + id);
					}
					else{
						Address = addresses.toStyledString();
						clientPtr->execSqlAsyncFuture("UPDATE accounts SET addresses='" + Address + "' WHERE id=" + id);
					}
				}
				responseJson["feedback"] = "Successfully removed address";
				responseJson["actionStatus"] = "true";
				auto resp = HttpResponse::newHttpJsonResponse(responseJson);
				callback(resp);
				return;
			}
		}
	}
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}
