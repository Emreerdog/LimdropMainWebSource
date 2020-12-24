#include "signup.h"
#include <trantor/utils/Date.h>
#include <limutils/PatternFiller.h>

void signup::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	const char* status = req->getCookie("_color").c_str();
	const char* statusText = req->getCookie("_feedback_msg").c_str();
	ManualPatternFiller MPF(2, "status", "statusText");
	std::string fileContent = "";

	auto sessionPtr = req->session();
	if(sessionPtr->find("isloggedin")){
		std::cout << "Nice look" << std::endl;
	}
	fileContent = MPF.fillPatterns("account.html", status, statusText);

	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(fileContent);
	resp->addCookie("_isdisplayed", "");
	resp->addCookie("_color", "");
	resp->addCookie("_feedback_msg", "");	
	callback(resp);
    //write your application logic here
}
