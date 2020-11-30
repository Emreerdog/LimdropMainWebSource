#include <iostream>
#include "passhandler.h"
#include "blowfish.h"

void helloguys(){
	std::cout << "Hello guys" << std::endl;
}

PasswordHandler::PasswordHandler(std::string pass, Mode PS_MODE) {
    this->_pass = pass;
    this->_PS_MODE = PS_MODE;
}


std::pair<unsigned long, unsigned long> PasswordHandler::GetLRpair(){
	return LRPair;
}

void PasswordHandler::EncryptPass(){
	if(_PS_MODE == Mode::PS_ENCRYPT){
		if(IsPassValid()){
			
			BLOWFISH_CTX ctx;
			Blowfish_Init(&ctx, (unsigned char*)_pass.c_str(), _pass.size());
			Blowfish_Encrypt(&ctx, &LRPair.first, &LRPair.second);
			
		}
	}
	else{
				
		std::cout << "Password handler is not on encryption mode!" << std::endl;
	}	
}

//WARNING Password needs to be valid
bool PasswordHandler::CheckDecryptValidity(unsigned long L, unsigned long R, unsigned long _L, unsigned long _R){
	if(_PS_MODE == Mode::PS_DECRYPT){
		BLOWFISH_CTX ctx;
		Blowfish_Init(&ctx, (unsigned char*)_pass.c_str(), _pass.size());
		Blowfish_Decrypt(&ctx, &L, &R);
		
		if(L == _L && R == _R){
			return true;
		}
		else {
			return false;
		}

	}
	return false;
}

void PasswordHandler::MakeLRpair(){
	srand(time(0));
	unsigned long L = rand() % 10 + 5;
	unsigned long R = rand() % 10 + 5;
	LRPair = std::make_pair(L, R);
}

bool PasswordHandler::IsPassContainsSpace() {
    std::string tempPass = _pass;
    size_t passLength = tempPass.size();
    for (int i = 0; i < passLength; i++) {
        if (isspace(tempPass[i])) {
            return true;
        }
    }
    return false;
}

bool PasswordHandler::IsPassValid() {
    if (IsPassValidLength() && !(IsPassContainsSpace())) {
        return true;
    }
    return false;
}

bool PasswordHandler::IsPassValidLength() {
    std::string tempPass = _pass;
    size_t passLength = tempPass.size();

    if (passLength < 6) {
        return false;
    }
    else {
        return true;
    }
}
