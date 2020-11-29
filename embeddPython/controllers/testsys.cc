#include "testsys.h"
#include <limutils/passhandler.h>

void testsys::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	helloguys();
	std::cout << "Hello world" << std::endl;
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
}
