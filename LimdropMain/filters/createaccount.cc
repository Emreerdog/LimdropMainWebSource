/**
 *
 *  createaccount.cc
 *
 */

#include "createaccount.h"

using namespace drogon;

void createaccount::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    
    auto *sessionPtr = req->session();
   
    if (sessionPtr->find("isLoggedIn")){	    
	if(sessionPtr->find("lastVisit")){
		std::string redirLoc = "https://192.168.1.23" + sessionPtr->get<std::string>("lastVisit");
		
		auto res = HttpResponse::newRedirectionResponse(redirLoc);
		fcb(res);
		return;
	}
	std::string redirLoc = "https://192.168.1.23/";

	auto res = HttpResponse::newRedirectionResponse(redirLoc);
	fcb(res);
        return;
    }
    else{
    	
	 std::unordered_map<std::string, std::string> tempParam = req->parameters();
	 for(const auto& n : tempParam){
	 	// TODO
		// Write username, password and email to database
		// Encrypt password with blowfish
		//
		// TODO
		// Check if the username, password and email is valid
		// Then redirect to profile
	 }
	 std::string redirLoc = "https://192.168.1.23/account/create"
	 sessionPtr->insert("status", false);
	 sessionPtr->insert("statusText", "Bos alan birakmamalisin");

	 auto res = HttpResponse::newRedirectionResponse(redirLoc);
	 fcb(res);
	 return;
    }
}
