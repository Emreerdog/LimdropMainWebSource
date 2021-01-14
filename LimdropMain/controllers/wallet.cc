#include "wallet.h"

void wallet::addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string amount)
{
	auto sessionPtr = req->session();
	Json::Value responseJson;
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Check post arguments if they are valid
		// Ddo all the money operations via embedd python
		// POBJECT and shit...

		int _amount;
		auto clientPtr = drogon::app().getDbClient();
		std::string id = sessionPtr->get<std::string>("id");
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
	auto sessionPtr = req->session();
	Json::Value responseJson;
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Check arguments if they are valid
		Json::Value addedCard;

		std::string id = sessionPtr->get<std::string>("id");
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
