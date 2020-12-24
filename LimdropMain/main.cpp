#include <drogon/drogon.h>

int
main(int argc, char *argv[])
{
    const char* uploadPath = "../../../../rootDrop/";

    //drogon::app().addListener("192.168.1.27", 443, true, "/etc/ssl/certs/drogon-selfsigned.crt", "/etc/ssl/private/drogon-selfsigned.key"); 
    drogon::app().setDocumentRoot(uploadPath);
    drogon::app().setUploadPath(uploadPath);
    drogon::app().addListener("192.168.2.21", 80);
    drogon::app().createDbClient("postgresql", "192.168.2.21", 5432, "limdrop", "anil", "mt98mxb9r2");
    drogon::app().enableSession();
    drogon::Cookie cookie1("test", "1");
    drogon::Cookie cookie2;
    cookie2.setKey("test2");
    cookie2.setValue("14");
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("404");
    resp->addCookie(cookie1);
    resp->addCookie(cookie2);
    drogon::app().setCustom404Page(resp);

    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();

    return 0;
}
