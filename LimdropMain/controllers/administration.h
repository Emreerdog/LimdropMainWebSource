#pragma once
#include <drogon/HttpController.h>
using namespace drogon;
class administration:public drogon::HttpController<administration>
{
  public:
    METHOD_LIST_BEGIN

    METHOD_ADD(administration::login, "/login?loginId={1}", Post, "adminloginfilter");
    METHOD_ADD(administration::panel,"/", Get);
    METHOD_ADD(administration::banUser,"/banUser?banReason={1}", Post);
    METHOD_ADD(administration::banUserPage,"/banUserPage?username={1}", Post);
    METHOD_ADD(administration::ipBanUser,"/ipBanUser?banReason={1}", Post);
    METHOD_ADD(administration::ipBanUserPage,"/ipBanUserPage?username={1}", Post);
    METHOD_ADD(administration::suspendForTime,"/suspenduser?suspendReason={1}", Post);
    METHOD_ADD(administration::sendMessageToUserPage, "/sendMessage?username={1}", Get);

    METHOD_LIST_END
    // void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,int p1,std::string p2);
};
