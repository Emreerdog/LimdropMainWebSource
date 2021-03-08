#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class administration:public drogon::HttpController<administration>
{
  public:

    METHOD_LIST_BEGIN
//
    METHOD_ADD(administration::login, "/login?loginId={1}", Get);
    METHOD_ADD(administration::makeFeatured, "/makeFeatured/{1}", Post);
    METHOD_ADD(administration::removeFeatured,"/removeFeatured/{1}", Post); // Remove the product from featured
    METHOD_ADD(administration::ipBanUser,"/ipBanUser?username={1}&banReason={2}", Post); // Ip ban user
    METHOD_ADD(administration::unverifiedProducts, "/unverifiedlist/", Get);
    METHOD_ADD(administration::distinctUnverified, "/uproduct/{1}", Get);
    METHOD_ADD(administration::sendMessageToUser, "/sendMessage?username={1}&message={2}", Post); // Send direct message to user
    METHOD_ADD(administration::acceptWaitingProduct,"/waitingproducts/accept?productCode={1}", Post); // Preview the product before accepting it
    METHOD_ADD(administration::rejectWaitingProduct,"/waitingproducts/reject?productCode={1}", Post); // Preview the product before accepting it

    METHOD_ADD(administration::sendEmail, "/sendmail?toUser={1}&title={2}&content={3}", Post); // Send mail to user
    METHOD_ADD(administration::sendEmailToAll ,"/sendMailToAll?&title={1}&content={2}", Post); // Send mail to users that have get mail option enabled 

    METHOD_LIST_END
    void login(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string loginId);
    void makeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void removeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void ipBanUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string banReason);
    void unverifiedProducts(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void distinctUnverified(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId);
    void sendMessageToUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string message);
    void acceptWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode);
    void rejectWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode);
    void sendEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string toUser, std::string title, std::string content);
    void sendEmailToAll(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string title, std::string content);
};
