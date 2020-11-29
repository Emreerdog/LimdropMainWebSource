#include <string>
#include <utility>

void helloguys();

enum Mode
{
    PS_ENCRYPT,
    PS_DECRYPT
};

class PasswordHandler {
public:
    PasswordHandler(std::string pass, Mode PS_MODE); 
    void MakeLRpair();
    void EncryptPass();
    std::pair <unsigned long, unsigned long> GetLRpair();
    bool CheckDecryptValidity(unsigned long L, unsigned long R, unsigned long _L, unsigned long _R);
private:
    bool IsPassValid();
    bool IsPassValidLength();
    bool IsPassContainsSpace();
    std::string _pass;
    std::pair <unsigned long, unsigned long> LRPair;
    Mode _PS_MODE;
    unsigned long _L;
    unsigned long _R;
};
