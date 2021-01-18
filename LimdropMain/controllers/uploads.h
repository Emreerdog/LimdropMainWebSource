#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class uploads:public drogon::HttpController<uploads>
{
  Json::Value currentJson;
  public:
    METHOD_LIST_BEGIN
    
    METHOD_ADD(uploads::upload_files, "/product/upload-photo", Post);
    METHOD_ADD(uploads::enterprops,"/enterprops", Post);
    METHOD_ADD(uploads::yukle,"/yukle", Post);
//
    METHOD_LIST_END
 
    void upload_files(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void enterprops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void yukle(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);

};
