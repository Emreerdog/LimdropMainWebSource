/**
 *
 *  createaccount.cc
 *
 */

#include "createaccount.h"
#include <limutils/inputregex.h>

using namespace drogon;

void createaccount::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    
        auto sessionPtr = req->session();
	sessionPtr->erase("status");
	sessionPtr->erase("statusText");

	 std::unordered_map<std::string, std::string> tempParam = req->parameters();
	 	 	for(const auto& n : tempParam){
		 	std::string secondVal = n.second;
		 	std::string firstVal = n.first;
			
			if(firstVal == "uname" || firstVal == "pass"){
										
	 			if(secondVal.length() < 6 || secondVal.length() > 16){
					std::string redirLoc = "https://192.168.1.23/accounts/create";
					std::string status = "false";
					std::string statusText = "Kullanici adi veya sifre en az 6\nen fazla 16 karakter olabilir";
					sessionPtr->insert("status", status);
					sessionPtr->insert("statusText", statusText);
			
					auto res = HttpResponse::newRedirectionResponse(redirLoc);
					fcb(res);
					return;
				}
				if(!checkUsernameRegex(secondVal)){
					std::string redirLoc = "https://192.168.1.23/accounts/create";
                        		
					std::string status = "false";
					std::string statusText = "Hatali giris";
					sessionPtr->insert("status", status);
					sessionPtr->insert("statusText", statusText);
					
					auto res = HttpResponse::newRedirectionResponse(redirLoc);
					fcb(res);
					return;
				}
			}
			else if(firstVal == "email"){
				if(!checkEmailRegex(secondVal)){
					std::string redirLoc = "https://192.168.1.23/accounts/create";
                        		
					std::string status = "false";
					std::string statusText = "hatali mail";
					sessionPtr->insert("status", status);
					sessionPtr->insert("statusText", statusText);	
                        		
					auto res = HttpResponse::newRedirectionResponse(redirLoc);
					fcb(res);
					return;
				}
			}
		// TODO
		// Check if the username, password and email is valid
		// Then redirect to profile
	 } 
	 std::string status = "true";
	 std::string statusText = "Everything is fine";
	 sessionPtr->insert("status", status);
	 sessionPtr->insert("statusText", statusText);	
	
	 fccb(); 
}
