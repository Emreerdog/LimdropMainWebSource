#include <drogon/drogon.h>

int
main(int argc, char *argv[])
{
    const char* uploadPath = "../../../../rootDrop/";

    drogon::app().addListener("192.168.2.21", 443, true, "/etc/ssl/certs/drogon-selfsigned.crt", "/etc/ssl/private/drogon-selfsigned.key");
    drogon::app().setDocumentRoot(uploadPath);
    drogon::app().setUploadPath(uploadPath);
    //drogon::app().addListener("192.168.2.38", 80);
    drogon::app().createDbClient("postgresql", "192.168.2.21", 5432, "limdrop", "anil", "mt98mxb9r2");
    drogon::app().enableSession();
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("404");
    drogon::app().setCustom404Page(resp);

    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();

    return 0;
}
