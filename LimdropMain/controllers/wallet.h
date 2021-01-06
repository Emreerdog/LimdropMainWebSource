#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class wallet:public drogon::HttpController<wallet>
{
  public:
    METHOD_LIST_BEGIN

    METHOD_ADD(wallet::show,"/", Get);//path is /wallet/{arg2}/{arg1}
    METHOD_ADD(wallet::addmoney,"/addmoney?amount={1}", Post);//path is /wallet/{arg1}/{arg2}/list	
    METHOD_ADD(wallet::addcard,"/addcard?cardholderName={1}&cardNumber={2}&expireMonth={3}&expireYear={4}&cvc={5}", Post);//path is /wallet/{arg1}/{arg2}/list

    METHOD_LIST_END
    void show(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string amount);
    void addcard(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string cardholderName, std::string cardNumber, std::string expireMonth, std::string expireYear, std::string cvc);
};
