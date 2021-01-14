#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class administration:public drogon::HttpController<administration>
{
  public:
    METHOD_LIST_BEGIN
//
    METHOD_ADD(administration::login, "/login?loginId={1}", Post);
    METHOD_ADD(administration::panel,"/", Get);
    METHOD_ADD(administration::banUser,"/banUser?username={1}&banReason={2}", Post); // Ban User
    METHOD_ADD(administration::banUserPage,"/banUserPage", Get); // Ban user page
    METHOD_ADD(administration::ipBanUser,"/ipBanUser?username={1}&banReason={2}", Post); // Ip ban user
    METHOD_ADD(administration::ipBanUserPage,"/ipBanUserPage", Get); // Ip ban user page
    METHOD_ADD(administration::sendMessageToUserPage, "/sendMessagePage", Get); // Send message page
    METHOD_ADD(administration::sendMessageToUser, "/sendMessage?username={1}&message={2}", Post); // Send direct message to user
    METHOD_ADD(administration::waitingProductsPage, "/waitingproducts", Get); // Products that are waiting to be accepted
    METHOD_ADD(administration::previewWaitingProduct,"/waitingproducts/{1}", Get); // Preview the product before accepting it
    METHOD_ADD(administration::acceptWaitingProduct,"/waitingproducts/accept?productCode={1}", Post); // Preview the product before accepting it
    METHOD_ADD(administration::rejectWaitingProduct,"/waitingproducts/accept?productCode={1}&reason={2}", Post); // Preview the product before accepting it
    METHOD_ADD(administration::sendEmailToUserPage, "/mailpage", Get);
    METHOD_ADD(administration::sendEmail, "/sendmail?toUser={1}&title={2}&content={3}", Post); // Send mail to user
    METHOD_ADD(administration::sendEmailToAll ,"/sendMailToAll?&title={1}&content={2}", Post); // Send mail to users that have get mail option enabled 

    METHOD_LIST_END
    void login(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string loginId);
    void panel(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void banUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string banReason);
    void banUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void ipBanUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string banReason);
    void ipBanUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void sendMessageToUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void sendMessageToUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string message);
    void waitingProductsPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void previewWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode);
    void acceptWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode);
    void rejectWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode, std::string reason);
    void sendEmailToUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void sendEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string toUser, std::string title, std::string content);
    void sendEmailToAll(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string title, std::string content);
};
