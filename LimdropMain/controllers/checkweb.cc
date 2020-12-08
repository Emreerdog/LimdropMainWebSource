#include "checkweb.h"
void checkweb::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
	wsConnPtr->send("Hello world");
	std::cout << "Hello world" << std::endl;
}
void checkweb::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
	std::cout << req->getPeerAddr().toIp() << std::endl;
	std::cout << "Hello world" << std::endl;
}
void checkweb::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
    //
	std::cout << "Hello world" << std::endl;
}
