#include "accounts.h"
#include <limutils/passhandler.h>
#include <limutils/PatternFiller.h>
#include "limjson.h"
//add definition of your processing function here


void accounts::createAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string email, std::string name, std::string surname, std::string pass, std::string passCheck){

	Json::Value responseJson;	
	if(pass != passCheck){
		// Password doesn't match
		responseJson["feedback"] = "Parola uyumlu değil";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	auto sessionPtr = req->session();
	
	PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);

	srand(time(0));
	
	passHandler.MakeLRpair(rand() % 10 + 5, rand() % 10 + 5);
	std::pair <unsigned long, unsigned long> LRPair = passHandler.GetLRpair();

	// Convert not encrypted lr pair to string
	std::string L = std::to_string(LRPair.first);
	std::string R = std::to_string(LRPair.second);

	passHandler.EncryptPass();
	LRPair = passHandler.GetLRpair();

	// Convert encrypted lr pair to string
	std::string LE = std::to_string(LRPair.first);
	std::string RE = std::to_string(LRPair.second);
	
	auto date = trantor::Date::now();

	auto clientPtr = drogon::app().getDbClient();
	std::string createDate = date.toCustomedFormattedString("%Y-%m-%d");
	std::string createTime = date.toCustomedFormattedString("%H:%M:%S");
	std::string preQuery = "SELECT id FROM accounts WHERE email='" + email + "'";
	auto f = clientPtr->execSqlAsyncFuture(preQuery);
	if(f.get().size() > 0){
		responseJson["feedback"] = "Böyle bir kullanıcı zaten mevcut";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string uuid = drogon::utils::getUuid();
	std::string queryStart = "INSERT INTO accounts(L, R, P1, P2, email, name, surname, accountCreateDate, accountCreateTime, uuid, isverified) VALUES";
	std::string queryEnd = "(" + L + "," + R + ",'" + LE + "','" + RE +"','" + email + "','" + name + "', '" + surname +"', '" + createDate + "','" + createTime+ "', '" + uuid + "', FALSE)";
      	std::string totalQuery = queryStart + queryEnd;	
	clientPtr->execSqlAsyncFuture(totalQuery);
		
	responseJson["feedback"] = email;
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}


void accounts::loginAccount(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, std::string email, std::string pass){

	auto sessionPtr = req->session();
	Json::Value responseJson;	
	// TODO 
	// Read the name and password from the database
	// Password should be decrypted using blowfish 
	//
	// TODO 
	// Get L and R value from database
	// Encrypt the password using L and R value
	// Then,
	// Check the validity by comparing new L and R values
	auto clientPtr = drogon::app().getDbClient();

	std::string queryStart = "SELECT L, R, P1, P2, id, name, surname FROM accounts WHERE ";
	std::string queryEnd = "email='" + email + "' AND isverified = TRUE";
	std::string totalQuery = queryStart + queryEnd;

	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	auto result = f.get();
	if(result.size() == 0){
		// ERROR
		// UNABLE TO LOGIN
		responseJson["feedback"] = "Hatalı Giriş";
	        responseJson["actionStatus"] = "false";	
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	else{
		unsigned long L = 0;
		unsigned long R = 0;
		unsigned long P1 = 0;
		unsigned long P2 = 0;
		std::string user_id;
		std::string name;
		std::string surname;
		for(auto row : result){
			L = row["L"].as<unsigned long>();
			R = row["R"].as<unsigned long>();
			P1 = row["P1"].as<unsigned long>();
			P2 = row["P2"].as<unsigned long>();
			user_id = row["id"].as<std::string>();
			name = row["name"].as<std::string>();
		        surname = row["surname"].as<std::string>();	
		}
		PasswordHandler passHandler(pass, Mode::PS_ENCRYPT);
		passHandler.MakeLRpair(L, R);
		passHandler.EncryptPass();
		std::pair <unsigned long, unsigned long> LRpair = passHandler.GetLRpair();
		// Decrypt password
		if(LRpair.first == P1 && LRpair.second == P2){
			sessionPtr->erase("isLoggedIn");
			sessionPtr->erase("balance");
			sessionPtr->erase("id");
			sessionPtr->erase("name");	
			sessionPtr->erase("surname");

			bool isLoggedIn = true;
			float balance = 0;
			sessionPtr->insert("isLoggedIn", isLoggedIn);
			sessionPtr->insert("email", email);
			sessionPtr->insert("balance", balance);
			sessionPtr->insert("id", user_id);
			sessionPtr->insert("name", name);
			sessionPtr->insert("surname", surname);

			responseJson["feedback"] = "Giriş Onaylandı";
	        	responseJson["actionStatus"] = "true";	
			auto resp = HttpResponse::newHttpJsonResponse(responseJson);
			callback(resp);
			return;
		}
	}
	responseJson["feedback"] = "Parola Hatalı";
	responseJson["actionStatus"] = "false";	
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}

void accounts::loginPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	auto sessionPtr = req->session();

	if(sessionPtr->find("isLoggedIn")){
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody("Hi");
	callback(resp);
}

