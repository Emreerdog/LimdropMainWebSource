#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class payment:public drogon::HttpController<payment>
{
  public:
    METHOD_LIST_BEGIN
    
    METHOD_ADD(payment::payit, "/pay", Get);
    METHOD_ADD(payment::paymentpage, "/page", Get);

    METHOD_LIST_END
    void payit(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);    
    void paymentpage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
