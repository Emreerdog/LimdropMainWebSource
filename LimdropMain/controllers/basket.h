#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class basket:public drogon::HttpController<basket>
{
  public:
    METHOD_LIST_BEGIN

    //use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(basket::showBasket,"/", Get, "checktraffic");//path is /basket/{arg2}/{arg1}
    METHOD_ADD(basket::addBasketItem,"/additem?itemId={1}", Post);//path is /basket/{arg1}/{arg2}/list
    METHOD_ADD(basket::removeBasketItem,"/removeitem?itemId={1}", Post);//path is /basket/{arg1}/{arg2}/list
    
    METHOD_LIST_END

    void showBasket(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void addBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void removeBasketItem(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);

};
