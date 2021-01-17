#include "wallet.h"

void wallet::addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string amount)
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
		// TODO
		// Check post arguments if they are valid
		// Ddo all the money operations via embedd python
		// POBJECT and shit...

		int _amount;
		auto clientPtr = drogon::app().getDbClient();
		std::string id = req->getHeader("id");
		std::stringstream amountStr(amount);
		amountStr >> _amount;
		if(_amount == 0){
			// Entered argument is probably invalid
			// Return to wallet page
		}
		std::string totalQuery1 = "UPDATE accounts SET balance = balance + " + amount + " WHERE id=" + id;
		clientPtr->execSqlAsyncFuture(totalQuery1);
		responseJson["feedback"] = "Bakiye yüklendi";
		responseJson["Miktar"] = amount;
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	// TODO
	// +Report the attempt to add money to wallet without logging in
	// +Report the attempt of outside post request
	responseJson["feedback"] = "Hesaba giriş yapılmamış";
	responseJson["actionStatus"] = "false";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}


void wallet::addcard(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string cardholderName, std::string cardNumber, std::string expireMonth, std::string expireYear, std::string cvc)
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
		// TODO
		// Check arguments if they are valid
		Json::Value addedCard;

		std::string id = req->getHeader("id");
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT cardlist FROM accounts WHERE id=" + id);
		auto result1 = f1.get();
		int resultSize = result1.size();
		int cardCount = 0; // Default card count is null
		if(resultSize > 0){
			// In case its the first card
			for(auto row : result1){
				std::stringstream ss(row["cardlist"].as<std::string>());
				ss >> addedCard;
				cardCount = addedCard.size();
			}
		}

		addedCard[cardCount]["cardHolderName"] = cardholderName;
		addedCard[cardCount]["cardNumber"] = cardNumber;
		addedCard[cardCount]["expireMonth"] = expireMonth;
		addedCard[cardCount]["expireYear"] = expireYear;
		addedCard[cardCount]["cvc"] = cvc;
		
		std::string _addedCard = addedCard.toStyledString();
		clientPtr->execSqlAsyncFuture("UPDATE accounts SET cardlist='" + _addedCard + "' WHERE id=" + id);
		responseJson["feedback"] = "Yeni kart başarıyla eklendi.";
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
//add definition of your processing function here

void wallet::showBalance(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
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
		std::string balance = "";
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT balance FROM accounts WHERE id=" + id);
		auto result1 = f1.get();
		for (auto row : result1) {
			balance = row["balance"].as<std::string>();
		}
		responseJson["feedback"] = "Balance is successfully seend";
		responseJson["balance"] = balance;
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