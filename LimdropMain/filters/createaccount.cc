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


    // Redirect to last page if the user already logged in.
    // If there is no last page, then it will be redirected to main page.
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
	 int i = 0;

	 std::unordered_map<std::string, std::string> tempParam = req->parameters();
	 for(const auto& n : tempParam){
		 std::string secondVal = n.second;
		 std::string firstVal = n.first;
	 	if(secondVal.length() < 6 || secondVal.length() > 16){
			std::string redirLoc = "https://192.168.1.23/account/create";
			sessionPtr->insert("status", false);
			sessionPtr->insert("statusText", "*Kullanici adi veya sifre en az 6\n*en fazla 16 karakter olabilir");
			
			auto res = HttpResponse::newRedirectionResponse(redirLoc);
			fcb(res);
			return;
		}
		else{
			
			if(firstVal == "pass"){
				if(!checkPasswordRegex(secondVal)){
					std::string redirLoc = "https://192.168.1.23/account/create";
                        		sessionPtr->insert("status", false);
                        		sessionPtr->insert("statusText", "*Kullanilan karakter gecersiz");
					auto res = HttpResponse::newRedirectionResponse(redirLoc);
					fcb(res);
					return;
				}
			}
			else if(firstVal == "uname"){
				if(!checkUsernameRegex(secondVal)){
					std::string redirLoc = "https://192.168.1.23/account/create";
                        		sessionPtr->insert("status", false);
                        		sessionPtr->insert("statusText", "*Kullanilan karakter gecersiz");
					auto res = HttpResponse::newRedirectionResponse(redirLoc);
					fcb(res);
					return;
				}
			}
		}
		// TODO
		// Check if the username, password and email is valid
		// Then redirect to profile
		i++;
	 }
	 
	 if(i == 2){
	 	fccb();
		return;
	 }

	 std::string redirLoc = "https://192.168.1.23/account/create";
	 sessionPtr->insert("status", false);
	 sessionPtr->insert("statusText", "Kullanici adi veya sifre bos birakilamaz");

	 auto res = HttpResponse::newRedirectionResponse(redirLoc);
	 fcb(res);
	 return;
    }
}
