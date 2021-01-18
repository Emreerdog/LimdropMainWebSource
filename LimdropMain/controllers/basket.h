#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class basket:public drogon::HttpController<basket>
{
  public:
    METHOD_LIST_BEGIN

    
    METHOD_ADD(basket::showBasket,"/", Get);
    METHOD_ADD(basket::addBasketItem,"/additem/{1}", Post);
    METHOD_ADD(basket::removeBasketItem,"/removeitem/{1}", Post);
    
    METHOD_LIST_END

    void showBasket(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void addBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);

};
