#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class product:public drogon::HttpController<product>
{
  public:
    bool checkIfProductExists(std::string itemId);

    METHOD_LIST_BEGIN

    METHOD_ADD(product::details,"/{1}", Get);
    METHOD_ADD(product::makeFeatured,"/makeFeatured/{1}", Post); // Make the product featured
    METHOD_ADD(product::featuredList,"/featured/", Get); // If there is no featured product, 4 random product will be featured
    METHOD_ADD(product::removeFeatured,"/removeFeatured/{1}", Post); // Remove the product from featured
    METHOD_ADD(product::getAllOnCategory, "/onCategory/{1}", Get); // Get all products on specific category
    METHOD_ADD(product::getAllCategories, "/categoryList/", Get);
    METHOD_ADD(product::getAllFinishedDrops, "/finished/", Get);
    METHOD_ADD(product::getOnGoingDrops, "/ongoing/", Get);

    METHOD_LIST_END
    
    void details(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void makeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void featuredList(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void removeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void getAllOnCategory(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string category);
    void getAllCategories(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void getAllFinishedDrops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void getOnGoingDrops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    
};
