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
    auto sessionPtr = req->session();
	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	for(const auto& n : tempParam){
		// TODO 
		// Read the name and password from the database
		// Password should be decrypted using blowfish 
		fccb();
		return;
	}
}
