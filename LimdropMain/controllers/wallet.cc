#include "wallet.h"


void wallet::show(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// +Query the database and print the currency the account has
		// +Show added cards
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}

void wallet::addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string amount)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Check post arguments if they are valid
		// Do all the money operations via embedd python
		// POBJECT and shit...

		int _amount;
		auto clientPtr = drogon::app().getDbClient();
		std::string username = sessionPtr->get<std::string>("username");
		std::stringstream amountStr(amount);
		amountStr >> _amount;
		if(_amount == 0){
			// Entered argument is probably invalid
			// Return to wallet page
		}
		std::string totalQuery1 = "UPDATE accounts SET balance = balance + " + amount + " WHERE username='" + username + "'";
		clientPtr->execSqlAsyncFuture(totalQuery1);
	}
	// TODO
	// +Report the attempt to add money to wallet without logging in
	// +Report the attempt of outside post request
	auto resp = HttpResponse::newRedirectionResponse("/");	
	callback(resp);
}


void wallet::addcard(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string holderName, std::string cardNumber, std::string expireMonth, std::string expireYear, std::string cvc)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Check arguments if they are valid
		Json::Value addedCard;

		std::string username = sessionPtr->get<std::string>("username");
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT cardlist FROM accounts WHERE username='" + username + "'");
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

		addedCard[cardCount]["cardHolderName"] = holderName;
		addedCard[cardCount]["cardNumber"] = cardNumber;
		addedCard[cardCount]["expireMonth"] = expireMonth;
		addedCard[cardCount]["expireYear"] = expireYear;
		addedCard[cardCount]["cvc"] = cvc;
		
		std::string _addedCard = addedCard.toStyledString();
		clientPtr->execSqlAsyncFuture("UPDATE accounts SET cardlist='" + _addedCard + "' WHERE username='" + username + "'");
		
		std::cout << "Card successfuly added to your saved cards" << std::endl; 
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}
//add definition of your processing function here
