#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class uploads:public drogon::HttpController<uploads>
{
  Json::Value currentJson;
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(uploads::upload_product,"/product", Post);
    METHOD_ADD(uploads::files_page, "/product/files-page", Post);
    METHOD_ADD(uploads::upload_files, "/product/upload-photo", Post);
    METHOD_ADD(uploads::upload_form,"/", Get);
    METHOD_ADD(uploads::enterprops,"/enterprops", Post);
    METHOD_ADD(uploads::enterImages,"/enterImages", Post);
    METHOD_ADD(uploads::yukle,"/yukle", Post);
    METHOD_ADD(uploads::propCheck, "/propcheck", Post);
//
    METHOD_LIST_END
 
    void upload_product(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void upload_form(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void upload_files(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void files_page(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void enterprops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void enterImages(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void yukle(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void fillprops(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);

};
