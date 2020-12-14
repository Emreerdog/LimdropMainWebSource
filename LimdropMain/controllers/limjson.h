#include <vector>
#include <tuple>
#include <string>
#include <json/json.h>

namespace Json{
	class Value;
}

enum EITEM_TYPE {
    PHYSICAL,
    VIRTUAL
};

class Basket {
public:
    Basket(Json::Value _basketJson);
    Basket(std::string basketJson);
    Basket();
    void removeItem(std::string id);
    void addItem(std::string id, std::string name, std::string category1, std::string category2, EITEM_TYPE EITYPE, std::string price, std::string image);
    unsigned int getItemCount();
    Json::Value getBasket();
    std::string getBasketAsString();
    std::string getBasketItem(std::string id, std::string whatToGet);
    double getTotalPrice();

private:
    Json::Value _basket;
};

class ProductJSON {
public:
    ProductJSON();
    ProductJSON(std::string product);
    std::vector<std::string> getImagePaths();
    std::vector<std::string> getValues();
    std::vector<std::string> getProperties();
    std::string getContent();
    Json::Value getProductJson();
    unsigned int getImageCount();
    unsigned int getOvCount();
    unsigned int getPropertyCount();

private:
    Json::Value productJson;
};

class AddressJSON {
public:
    AddressJSON(std::string contactName, std::string city, std::string country, std::string address, std::string zipCode);
    AddressJSON(std::string buyer);
    std::string getContactName();
    std::string getCity();
    std::string getCountry();
    std::string getAddress();
    std::string getZipCode();
    Json::Value getAddressJSON();
private:
    Json::Value addressJson;
};
