#include "profile.h"
#include <limutils/PatternFiller.h>

void profile::showProfile(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string profileKey){

	std::string fileContent = "";
	auto sessionPtr = req->session();
	if(sessionPtr->find("isLoggedIn")){
		// TODO
		// Set the parameters on navbar
		// Basket etc.
		ManualPatternFiller MPF(2, "_id", "_username");
		fileContent = MPF.fillPatterns("profile.html", "", "");
	}
	else{

		ManualPatternFiller MPF(2, "_id", "_username");
		fileContent = MPF.fillPatterns("profile.html", "", "");
	}

	auto clientPtr = drogon::app().getDbClient();
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
		std::string tempFileContent = fileContent;

		ManualPatternFiller MPF(5, "username", "age", "profilePhoto", "name", "surname");
		for(auto row : result){
			tempFileContent = MPF.fillPatternsOnString(fileContent, row["username"].as<std::string>().c_str(), 
					row["age"].as<std::string>().c_str(), row["profilePhoto"].as<std::string>().c_str(),
					row["name"].as<std::string>().c_str(), row["surname"].as<std::string>().c_str());
		}
		auto resp = HttpResponse::newHttpResponse();
		resp->setBody(tempFileContent);
		callback(resp);

	}
}


//add definition of your processing function here
