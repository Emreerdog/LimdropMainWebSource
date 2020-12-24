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
		auto totalQuery1 = "SELECT basketitem, address FROM accounts WHERE username='" + username + "'";
		auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
		auto result1 = f1.get();
		
		Json::Value addressJson;
		std::string basket;
		std::string addressString;
		for(auto row : result1){
			basket = row["basketitem"].as<std::string>();
			addressString = row["address"].as<std::string>();
			if(addressString == ""){
				// TODO
				// If the address is empty
				// Redirect to address input page
				auto resp = HttpResponse::newRedirectionResponse("/");
				callback(resp);
				return;
			}
			std::stringstream addressToJson(addressString);
			addressToJson >> addressJson;
		}
		if(basket == ""){
			std::cout << "Basket is empty" << std::endl;
			auto resp = HttpResponse::newNotFoundResponse();
			callback(resp);
			return;
		}
		Basket PB(basket);
		Json::Value tempBasket = PB.getBasket();
		Json::Value resultantBasket;

		unsigned int tempBasketSize = tempBasket["basket_items"].size();
		if(tempBasketSize == 0){
			auto resp = HttpResponse::newRedirectionResponse("/");
			callback(resp);
			return;
		}
		for(int i = 0; i < tempBasketSize; i++){
			resultantBasket[i] = tempBasket["basket_items"][i];
			resultantBasket[i].removeMember("image");
		}


		std::string resultantBasketString = resultantBasket.toStyledString();
		std::cout << resultantBasket << std::endl;

		/*std::string totalQuery2 = "UPDATE accounts SET basketitem=NULL, boughtproducts='" + resultantBasketString + "', currentlyondrop='"+ resultantBasketString +"', boughtProductCount = boughtProductCount + 1 WHERE username='" + username + "'";
		clientPtr->execSqlAsyncFuture(totalQuery2);*/
		Json::Value buyers;
		std::vector<std::string> _buyerJsonString;
		for(int i = 0; i < resultantBasket.size(); i++){
			std::string productID = resultantBasket[i]["id"].asString();
			std::string totalQuery3 = "SELECT buyers, customercount, maximumproductcount FROM products WHERE id=" + productID + "";
			std::string buyerJsonString;
			auto f3 = clientPtr->execSqlAsyncFuture(totalQuery3);
			auto result3 = f3.get();
			unsigned int sizeOfBuyersJson;
			unsigned int customerCount;
			unsigned int maximumproductCount;
			for(auto row : result3){
				customerCount = row["customercount"].as<unsigned int>();
				customerCount++;
				maximumproductCount = row["maximumproductcount"].as<unsigned int>();
				
				if(customerCount >= maximumproductCount ){
					std::cout << "Product is out of stock" << std::endl;
					// Remove the product from the basket
					resultantBasket.removeIndex(i, NULL);
					auto resp = HttpResponse::newNotFoundResponse();
					callback(resp);
					return;	
				}
				buyerJsonString = row["buyers"].as<std::string>();
				if(buyerJsonString == ""){
					// In case the buyer is the first buyer
					sizeOfBuyersJson = 0;
				}
				else{
					std::stringstream streamBuyer(buyerJsonString);
					streamBuyer >> buyers;
					sizeOfBuyersJson = buyers.size();
				}
			}
			buyers[sizeOfBuyersJson]["username"] = username;
			buyerJsonString = buyers.toStyledString();
			_buyerJsonString.push_back(buyerJsonString);
			/*std::string totalQuery4 = "UPDATE products SET buyers='" + buyerJsonString + "', customercount = customercount + 1 WHERE id=" + productID;
			auto f4 = clientPtr->execSqlAsyncFuture(totalQuery4);*/
		}

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

		/*Py_Initialize();
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
		*/


		/*std::string totalQuery4 = "UPDATE products SET buyers='" + buyerJsonString + "', customercount = customercount + 1 WHERE id=" + productID;
		auto f4 = clientPtr->execSqlAsyncFuture(totalQuery4);*/
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

void payment::paymenthistory(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback)
{

}
//add definition of your processing function here
