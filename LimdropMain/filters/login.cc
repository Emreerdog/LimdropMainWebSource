/**
 *
 *  login.cc
 *
 */

#include "login.h"

using namespace drogon;

void login::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    // Already logged in 
    // Redirect to last page
    // If there is no last page, redirect to main page
    auto *sessionPtr = req->session();
    if (sessionPtr->find("isLoggedIn"))
    {
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
    
    else {
	    std::unordered_map<std::string, std::string> tempParam = req->parameters();
	    for(const auto& n : tempParam){
		    // TODO 
		    // Read the name and password from the database
		    // Password should be decrypted using blowfish 
		    fccb();
		    return;
	    }
	    std::string redirLoc = "https://192.168.1.23/"

	    auto res = HttpResponse::newRedirectionResponse(redirLoc);
	    fcb(res);
	    return;
    }
}
