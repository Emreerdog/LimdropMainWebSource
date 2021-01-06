#include "administration.h"
//add definition of your processing function here
void administration::login(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string loginId){
	auto clientPtr = drogon::app().getDbClient();
	std::string query1 = "SELECT adminId FROM admins WHERE adminId='" + loginId + "'";
	auto f1 = clientPtr->execSqlAsyncFuture(query1);
	auto result1 = f1.get();
	
	if(result1.size() == 0){
		// In this case login id is wrong
		// Redirect to main page
		// Get the ip of the attempt
		// Report the attempt to the administrator via email or sms
		auto resp = HttpResponse::newRedirectionResponse("/");
		callback(resp);
		return;
	}
	auto sessionPtr = req->session();
	sessionPtr->erase("loggedAsAdmin");
	sessionPtr->insert("loggedAsAdmin", "true");

	auto resp = HttpResponse::newRedirectionResponse("/administration/");
	callback(resp);
}
void administration::panel(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void administration::banUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string banReason){

}
void administration::banUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void administration::ipBanUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string banReason){

}
void administration::ipBanUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void administration::sendMessageToUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void administration::sendMessageToUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string message){

}
void administration::waitingProductsPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void administration::previewWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode){

}
void administration::acceptWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode){

}
void administration::rejectWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string productCode, std::string reason){

}
void administration::sendEmailToUserPage(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){

}
void administration::sendEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string toUser, std::string title, std::string content){

}
void administration::sendEmailToAll(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string title, std::string content){

}
