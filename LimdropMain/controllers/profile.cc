#include "profile.h"
#include <limutils/PatternFiller.h>

void profile::showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey){

	auto sessionPtr = req->session();

	auto clientPtr = drogon::app().getDbClient();
	int _profileKey;
	std::stringstream ss(profileKey);
	ss >> _profileKey;
	if(_profileKey <= 0){
		auto resp = HttpResponse::newNotFoundResponse();
		callback(resp);
		return;
	}

	std::string totalQuery = "SELECT id, username, age, profilePhoto, name, surname FROM accounts WHERE id=" + profileKey;
	auto f = clientPtr->execSqlAsyncFuture(totalQuery);
	auto result = f.get();
	if(result.size() == 0){
		// TODO
		// Show that there is no such profile
		auto resp = HttpResponse::newNotFoundResponse();
		callback(resp);
		return;
	}
	else{
		if(sessionPtr->find("id")){
			// TODO
			// In case if we are already logged in
			// If the queried id is our id
			// We will show our profile with edit buttons
			std::string userID = sessionPtr->get<std::string>("id");
			if(userID == profileKey){
				// It means our profile
				std::cout << "It is your own profile" << std::endl;
			}
		}
		std::string fileContent;
		ManualPatternFiller MPF(5, "username", "age", "profilePhoto", "name", "surname");
		for(auto row : result){
			fileContent = MPF.fillPatterns("profile.html", row["username"].as<std::string>().c_str(), 
					row["age"].as<std::string>().c_str(), row["profilePhoto"].as<std::string>().c_str(),
					row["name"].as<std::string>().c_str(), row["surname"].as<std::string>().c_str());
		}
		auto resp = HttpResponse::newHttpResponse();
		resp->setBody(fileContent);
		callback(resp);

	}
}


void profile::showAddress(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string addressIndex)
{
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		std::string id = sessionPtr->get<std::string>("id");
		auto clientPtr = drogon::app().getDbClient();
		auto f1 = clientPtr->execSqlAsyncFuture("SELECT addresses FROM accounts WHERE username=" + id);
		auto result1 = f1.get();
		for(auto row : result1){	
			std::cout << row["addresses"].as<std::string>() << std::endl;
		}	
		auto resp = HttpResponse::newHttpResponse();
		resp->setBody("Hello");
		callback(resp);
		return;
	}
	auto resp = HttpResponse::newRedirectionResponse("/");
	callback(resp);
}

