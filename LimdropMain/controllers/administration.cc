#include "administration.h"
//add definition of your processing function here
void administration::login(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string loginId){
	Json::Value responseJson;
	auto clientPtr = drogon::app().getDbClient();
	std::string query1 = "SELECT adminId FROM admins WHERE adminId='" + loginId + "'";
	auto f1 = clientPtr->execSqlAsyncFuture(query1);
	auto result1 = f1.get();
	
	if(result1.size() == 0){
		// In this case login id is wrong
		// Redirect to main page
		// Get the ip of the attempt
		// Report the attempt to the administrator via email or sms
		responseJson["feedback"] = "Admin girişi başarısız";
		responseJson["attemptedIP"] = req->getPeerAddr().toIp();
		responseJson["actionStatus"] = "true";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}//
	auto sessionPtr = req->session();
	sessionPtr->erase("loggedAsAdmin");
	sessionPtr->insert("loggedAsAdmin", "true");

	responseJson["feedback"] = "Admin girişi yapıldı";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;
}
void administration::makeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::stringstream ss(itemId);
	int checkIfNum = 0;
	ss >> checkIfNum;
	if(checkIfNum == 0){
		responseJson["feedback"] = "Ürün numarası 0 olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery0 = "SELECT id FROM products WHERE id=" + itemId;
	auto f0 = clientPtr->execSqlAsyncFuture(totalQuery0);
	auto result1 = f0.get();
	if(result1.size() == 0){
		responseJson["feedback"] = "Böyle bir ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string totalQuery1 = "UPDATE products SET isfeatured = TRUE WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	responseJson["id"] = itemId;
	responseJson["feedback"] = "Ürün öne çıkanlara eklendi";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;

}

void administration::removeFeatured(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::stringstream ss(itemId);
	int checkIfNum = 0;
	ss >> checkIfNum;
	if(checkIfNum == 0){
		responseJson["feedback"] = "Ürün numarası 0 olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery0 = "SELECT id FROM products WHERE id=" + itemId;
	auto f0 = clientPtr->execSqlAsyncFuture(totalQuery0);
	auto result0 = f0.get();
	if(result0.size() == 0){
		responseJson["feedback"] = "Böyle bir ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string totalQuery1 = "UPDATE products SET isfeatured = FALSE WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	responseJson["id"] = itemId;
	responseJson["feedback"] = "Ürün öne çıkanlara eklendi";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;
}


void administration::ipBanUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string banReason){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}

void administration::unverifiedProducts(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id, details FROM products WHERE isverified=FALSE";
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		responseJson["feedback"] = "Onaylanmamış ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	unsigned int i = 0;

	for(auto row : result1){
		Json::Value featuredProducts;
		std::stringstream sDescription(row["details"].as<std::string>());
		sDescription >> featuredProducts;
		responseJson["uprod"][i] = featuredProducts;
		responseJson["uprod"][i]["id"] = row["id"].as<std::string>();
		i++;
	}
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}

void administration::distinctUnverified(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string _itemId = itemId;
	// Check if it is number
	for(int i = 0; i < _itemId.length(); i++){
		if(!(_itemId[i] >= '0' && _itemId[i] <= '9')){
			responseJson["feedback"] = "Girilen parametre say� de�il";
			responseJson["actionStatus"] = "false";
			auto resp = HttpResponse::newHttpJsonResponse(responseJson);
			callback(resp);
			return;
		}
	}
	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id, isbuyable, customercount, price, isverified, details FROM products WHERE id=" + itemId + " AND isverified=FALSE";
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		responseJson["id"] = itemId;
		responseJson["feedback"] = "B�yle bir �r�n bulunmamaktad�r";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string detailsJSON;
	for(auto row : result1){
		std::stringstream sDescription(row["details"].as<std::string>());
		sDescription >> responseJson;
		responseJson["id"] = itemId;
		responseJson["isbuyable"] = row["isbuyable"].as<std::string>();
		responseJson["customercount"] = row["customercount"].as<std::string>();
		responseJson["price"] = row["price"].as<std::string>();
		responseJson["isverified"] = row["isverified"].as<std::string>();

	}
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
}


void administration::sendMessageToUser(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string username, std::string message){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}

void administration::acceptWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::stringstream ss(itemId);
	int checkIfNum = 0;
	ss >> checkIfNum;
	if(checkIfNum == 0){
		responseJson["feedback"] = "Ürün numarası 0 olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery0 = "SELECT id FROM products WHERE id=" + itemId;
	auto f0 = clientPtr->execSqlAsyncFuture(totalQuery0);
	auto result0 = f0.get();
	if(result0.size() == 0){
		responseJson["feedback"] = "Böyle bir ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string totalQuery1 = "UPDATE products SET isverified = TRUE, isbuyable = TRUE WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	responseJson["id"] = itemId;
	responseJson["feedback"] = "Ürün onaylandı";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;

}

void administration::rejectWaitingProduct(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::stringstream ss(itemId);
	int checkIfNum = 0;
	ss >> checkIfNum;
	if(checkIfNum == 0){
		responseJson["feedback"] = "Ürün numarası 0 olamaz";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery0 = "SELECT id FROM products WHERE id=" + itemId;
	auto f0 = clientPtr->execSqlAsyncFuture(totalQuery0);
	auto result0 = f0.get();
	if(result0.size() == 0){
		responseJson["feedback"] = "Böyle bir ürün yok";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}

	std::string totalQuery1 = "DELETE FROM products WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	responseJson["id"] = itemId;
	responseJson["feedback"] = "Ürün kaldırıldı";
	responseJson["actionStatus"] = "true";
	auto resp = HttpResponse::newHttpJsonResponse(responseJson);
	callback(resp);
	return;

}

void administration::sendEmail(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string toUser, std::string title, std::string content){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}
void administration::sendEmailToAll(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string title, std::string content){
	Json::Value responseJson;
	auto sessionPtr = req->session();
	if (!sessionPtr->find("loggedAsAdmin")) {
		responseJson["feedback"] = "Admin loggin failed";
		responseJson["actionStatus"] = "false";
		auto resp = HttpResponse::newHttpJsonResponse(responseJson);
		callback(resp);
		return;
	}
}
