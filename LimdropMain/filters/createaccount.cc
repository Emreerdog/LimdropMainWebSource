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

	 std::unordered_map<std::string, std::string> tempParam = req->parameters();
	 	 	for(const auto& n : tempParam){
		 	std::string secondVal = n.second;
		 	std::string firstVal = n.first;
			
			if(firstVal == "uname" || firstVal == "pass"){
										
	 			if(secondVal.length() < 6 || secondVal.length() > 16){
					const char* redirLoc = "/createaccount.html";
					const char* display = "block";
					const char* status = "red";
					const char* statusText = "Sifre en az 6<br>En fazla 16 karakter olabilir";
					sessionPtr->insert("display", display);
					sessionPtr->insert("status", status);
					sessionPtr->insert("statusText", statusText);
			
					auto res = HttpResponse::newRedirectionResponse(redirLoc);
					fcb(res);
					return;
				}
			}
			else if(firstVal == "email"){
				if(!checkEmailRegex(secondVal)){
					const char* redirLoc = "/createaccount.html";
					const char* display = "block";
					const char* status = "red";
					const char* statusText = "hatali mail";
					sessionPtr->insert("display", display);
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
	 fccb(); 
}
