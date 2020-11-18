#include "testsys.h"
void testsys::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
	for(int i = 0; i < 10000; i++){
		system("python3 test.py");
	}
	auto resp = HttpResponse::newNotFoundResponse();
	callback(resp);
}
