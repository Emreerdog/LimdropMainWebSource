#include "payment.h"
#include "limjson.h"
#include <vector>
#include <sstream>
#include <tuple>
#include <limutils/pyutils.h>



void payment::payit(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		std::string username = sessionPtr->get<std::string>("username");
		auto clientPtr = drogon::app().getDbClient();
		auto totalQuery1 = "SELECT basketitem FROM accounts WHERE username='" + username + "'";
		auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
		auto result1 = f1.get();

		std::string basket;
		for(auto row : result1){
			basket = row["basketitem"].as<std::string>();
		}
		Basket PB(basket);
		Json::Value tempBasket = PB.getBasket();
		Json::Value resultantBasket;
		//float price = 1.0;
		//std::stringstream ss;
		//ss << price;

		for(int i = 0; i < tempBasket["basket_items"].size(); i++){
			//std::string _price = ss.str();
			resultantBasket[i] = tempBasket["basket_items"][i];
			resultantBasket[i].removeMember("image");
			//resultantBasket[i]["price"] = _price;
			//tempBasket["basket_items"].removeIndex(i, NULL);
		}

		std::cout << resultantBasket << std::endl;
		//std::string totalQuery2 = "UPDATE accounts SET basketitem='" + tempBasket.toStyledString() + "' WHERE username='" + username + "'";
		std::string resultantBasketString = resultantBasket.toStyledString();

		std::vector<std::pair<std::string, std::string>> payment_card = {
    		std::make_pair("cardHolderName", "John Doe"),
    		std::make_pair("cardNumber", "5528790000000008"),
    		std::make_pair("expireMonth", "12"),
    		std::make_pair("expireYear", "2030"),
    		std::make_pair("cvc", "123"),
    		std::make_pair("registerCard", "0")
    		};
		
		std::vector<std::pair<std::string, std::string>> buyer = {
    		std::make_pair("id", "BY789"),
    		std::make_pair("name", "John"),
    		std::make_pair("surname", "Doe"),
    		std::make_pair("gsmNumber", "+905350000000"),
    		std::make_pair("email", "email@email.com"),
    		std::make_pair("identityNumber", "74300864791"),
    		std::make_pair("lastLoginDate", "2015-10-05 12:43:35"),
    		std::make_pair("registrationDate", "2013-04-21 15:12:09"),
    		std::make_pair("registrationAddress", "Nidakule Göztepe, Merdivenköy Mah. Bora Sok. No:1"),
    		std::make_pair("ip", "85.34.78.112"),
    		std::make_pair("city", "Istanbul"),
    		std::make_pair("country", "Turkey"),
    		std::make_pair("zipCode", "34732")
    		};


		std::vector<std::pair<std::string, std::string>> address = {
    		std::make_pair("contactName", "Jane Doe"),
    		std::make_pair("city", "Istanbul"),
    		std::make_pair("country", "Turkey"),
    		std::make_pair("address", "Nidakule Göztepe, Merdivenköy Mah. Bora Sok. No:1"),
    		std::make_pair("zipCode", "34732")
    		};

    		std::vector<std::pair<std::string, std::string>>::iterator paymentIT;
    		std::vector<std::pair<std::string, std::string>>::iterator buyerIT;
    		std::vector<std::pair<std::string, std::string>>::iterator addressIT;

    		Json::Value Jpayment_card;
    		Json::Value Jbuyer;
    		Json::Value Jaddress;

    		for (paymentIT = payment_card.begin(); paymentIT != payment_card.end(); paymentIT++) {
        		Jpayment_card[paymentIT->first] = paymentIT->second;
    		}

    		for (buyerIT = buyer.begin(); buyerIT != buyer.end(); buyerIT++) {
        		Jbuyer[buyerIT->first] = buyerIT->second;
    		}

    		for (addressIT = address.begin(); addressIT != address.end(); addressIT++) {
        		Jaddress[addressIT->first] = addressIT->second;
    		}

		std::string _payment_card = Jpayment_card.toStyledString();
		std::string _buyer = Jbuyer.toStyledString();
		std::string _address = Jaddress.toStyledString();

		std::cout << _payment_card << std::endl;
		std::cout << _buyer << std::endl;
		std::cout << _address << std::endl;


		Py_Initialize();
		POBJECT p_payment_card = LIM_PSTR(_payment_card.c_str());
		POBJECT p_buyer = LIM_PSTR(_buyer.c_str());
		POBJECT p_address = LIM_PSTR(_address.c_str()); 
		POBJECT p_basket = LIM_PSTR(resultantBasketString.c_str());
		POBJECT functionArgs = LIM_PMAKE_TUPLE(4);
		LIM_PADD_TUPLE(functionArgs, 0, p_payment_card);
		LIM_PADD_TUPLE(functionArgs, 1, p_buyer);
		LIM_PADD_TUPLE(functionArgs, 2, p_address);
		LIM_PADD_TUPLE(functionArgs, 3, p_basket);

		POBJECT imports = LIM_PIMPORT("limpayment");
		POBJECT func = LIM_PGET_ATTR(imports, "limpayment");
		POBJECT returnValue = LIM_PFUNC_ARGS(func, functionArgs);

		Py_CLEAR(imports);
		Py_CLEAR(func);
		Py_CLEAR(returnValue);
		Py_CLEAR(functionArgs);
		Py_FinalizeEx();

		//auto f2 = clientPtr->execSqlAsyncFuture(totalQuery2);
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
}


void payment::paymentpage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
	
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}
//add definition of your processing function here
