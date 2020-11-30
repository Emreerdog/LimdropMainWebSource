/**
 *
 *  checktraffic.cc
 *
 */

#include "checktraffic.h"
#include <limutils/inputregex.h>

using namespace drogon;

void checktraffic::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb)
{
    	std::string lastVisited = req->getPath();
    	auto sessionPtr = req->session();
	std::string sampleInput = "ananke";
	if(checkUsernameRegex(sampleInput)){
		std::cout << "Input is valid" << std::endl;
	}
  	if(sessionPtr->find("lastVisit")){
		//TODO right the last visited site to database
		//
		// Last data should be erased. Otherwise value of the key won't be change
		sessionPtr->erase("lastVisit");
		sessionPtr->insert("lastVisit", lastVisited);
		fccb();
		return;
	}
    else{
		// Since the data is already empty, we don't have to erase it.
		sessionPtr->insert("lastVisit", lastVisited);
		fccb();
		return;
	}	
}