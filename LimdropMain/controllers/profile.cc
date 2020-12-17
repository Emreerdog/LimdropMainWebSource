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


//add definition of your processing function here
