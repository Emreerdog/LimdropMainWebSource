#include "signup.h"
#include <trantor/utils/Date.h>
#include <limutils/PatternFiller.h>

void signup::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	ManualPatternFiller MPF(2, "status", "statusText");
	std::string fileContent = "";

	std::cout << "Hello world" << std::endl;

	auto sessionPtr = req->session();
	if(sessionPtr->find("status")){	
			std::string status = sessionPtr->get<std::string>("status");
			std::string statusText = sessionPtr->get<std::string>("statusText");			
			fileContent = MPF.fillPatterns("account.html", status.c_str(), statusText.c_str());
			// Free the status vars
			sessionPtr->erase("status");
			sessionPtr->erase("statusText");
	}
	else{
		fileContent = MPF.fillPatterns("account.html", "", "");
	}

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(fileContent);
	callback(resp);
    //write your application logic here
}
