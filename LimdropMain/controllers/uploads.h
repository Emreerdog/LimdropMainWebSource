#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class uploads:public drogon::HttpController<uploads>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(uploads::upload_product,"/product", Post);
    METHOD_ADD(uploads::files_page, "/product/files-page", Post);
    METHOD_ADD(uploads::upload_files, "/product/upload-photo", Post);
    METHOD_ADD(uploads::upload_form,"/",Get);

    METHOD_LIST_END
 
    void upload_product(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void upload_form(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void upload_files(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void files_page(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
};
