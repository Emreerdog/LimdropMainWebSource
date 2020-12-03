#include <drogon/drogon.h>

int
main(int argc, char *argv[])
{

    drogon::app().addListener("192.168.2.38", 443, true, "/etc/ssl/certs/drogon-selfsigned.crt", "/etc/ssl/private/drogon-selfsigned.key");
    drogon::app().setDocumentRoot("../../../rootDrop/");
    //drogon::app().addListener("192.168.1.23", 80);
    drogon::app().createDbClient("postgresql", "192.168.2.38", 5432, "limdrop", "anil", "mt98mxb9r2");
    drogon::app().enableSession();
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();

    return 0;
}
