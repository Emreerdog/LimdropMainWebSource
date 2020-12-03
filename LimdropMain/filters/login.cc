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
	std::cout << "----------" << std::endl;
    auto sessionPtr = req->session();
	std::unordered_map<std::string, std::string> tempParam = req->parameters();
	for(const auto& n : tempParam){
		// TODO 
		// Read the name and password from the database
		// Password should be decrypted using blowfish 
		std::cout << n.first << std::endl;
		
	}
	fccb();
	return;
}
