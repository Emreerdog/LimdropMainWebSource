#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class wallet:public drogon::HttpController<wallet>
{
  public:
    METHOD_LIST_BEGIN

    METHOD_ADD(wallet::addmoney,"/addmoney/{1}", Post);//path is /wallet/{arg1}/{arg2}/list	
    METHOD_ADD(wallet::addcard,"/addcard/{1}/{2}/{3}/{4}/{5}", Post);//path is /wallet/{arg1}/{arg2}/list
    METHOD_ADD(wallet::showBalance, "/balance");

    METHOD_LIST_END
    void addmoney(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string amount);
    void addcard(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string cardholderName, std::string cardNumber, std::string expireMonth, std::string expireYear, std::string cvc);
    void showBalance(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
