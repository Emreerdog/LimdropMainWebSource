#include "signup.h"
#include <limutils/PatternFiller.h>

void signup::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	ManualPatternFiller MPF(2, "status", "statusText");
	std::string fileContent = "";

	auto sessionPtr = req->session();
	if(sessionPtr->find("status")){
			std::string status = sessionPtr->get<std::string>("status");
			std::string statusText = sessionPtr->get<std::string>("statusText");
			
			// Free the status vars
			sessionPtr->erase("status");
			sessionPtr->erase("statusText");

			fileContent = MPF.fillPatterns("account.html", status, statusText);
	}
	else{
		fileContent = MPF.fillPatterns("account.html", "", "");
	}

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(fileContent);
	callback(resp);
    //write your application logic here
}