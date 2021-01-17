#include "limjson.h"
#include <drogon/drogon.h>

Basket::Basket(Json::Value _basketJson)
{
    _basket = _basketJson;
}

Basket::Basket(std::string basketJson)
{
    std::stringstream sstr(basketJson);
    sstr >> _basket;
}

Basket::Basket()
{

}

void Basket::removeItem(std::string id)
{
    Json::Value myval;
    unsigned int necessaryIndex = 0;
    bool isFound = false;
    for (Json::ValueConstIterator it = _basket["basket_items"].begin(); it != _basket["basket_items"].end(); ++it)
    {
        const Json::Value& book = *it;
        if (book["id"] == id) {
            necessaryIndex = it.index();
            isFound = true;
            break;
        }
        // rest as before
    }
    if (isFound) {
        _basket["basket_items"].removeIndex(necessaryIndex, &myval);
        return;
    }
    std::cout << "Item with id: " << id << " couldn't found on basket" << std::endl;
}

void Basket::addItem(std::string id, std::string name, std::string category1, std::string category2, EITEM_TYPE EITYPE, std::string price, std::string image)
{
    std::string itemType = "";
    if (EITYPE == EITEM_TYPE::PHYSICAL) {
        itemType = "PHYSICAL";
    }
    else {
        itemType = "VIRTUAL";
    }
    std::vector<std::pair<std::string, std::string>> fields =
    { std::make_pair("id", id), std::make_pair("name", name), std::make_pair("category1", category1),
        std::make_pair("category2", category2), std::make_pair("itemType", itemType), std::make_pair("price", price), std::make_pair("image", image) };
    std::vector<std::pair<std::string, std::string>>::iterator It;

    unsigned int itemCount = getItemCount();

    for (It = fields.begin(); It != fields.end(); It++) {
        if (itemCount == 0) {

            _basket["basket_items"][0][It->first] = It->second;
        }
        else {
            _basket["basket_items"][itemCount][It->first] = It->second;
        }
    }
    fields.empty();
}

unsigned int Basket::getItemCount()
{
    return _basket["basket_items"].size();
}

Json::Value Basket::getBasket()
{
    return _basket;
}

std::string Basket::getBasketAsString()
{
    return _basket.toStyledString();
}

std::string Basket::getBasketItem(std::string id, std::string whatToGet)
{
    std::string result = "Item couldn't found on basket";
    unsigned int necessaryIndex = 0;
    bool isFound = false;
    for (Json::ValueConstIterator it = _basket["basket_items"].begin(); it != _basket["basket_items"].end(); ++it)
    {
        const Json::Value& book = *it;
        if (book["id"] == id) {
            result = book[whatToGet].asString();
            necessaryIndex = it.index();
            isFound = true;
            break;
        }
        // rest as before
    }
    return result;
}

double Basket::getTotalPrice() {
    double totalPrice = 0.0;
    for (Json::ValueConstIterator it = _basket["basket_items"].begin(); it != _basket["basket_items"].end(); ++it)
    {
        const Json::Value& book = *it;
        totalPrice += std::stod(book["price"].asString());
        // rest as before
    }
    return totalPrice;
}

ProductJSON::ProductJSON()
{
}

std::vector<std::string> ProductJSON::getImagePaths()
{
    std::vector<std::string> imagePaths;
    unsigned int imgCount = getImageCount();
    for (int i = 0; i < imgCount; i++) {
        imagePaths.push_back(productJson["product"]["images"][i].asString());
    }
    return imagePaths;
}

ProductJSON::ProductJSON(std::string product)
{
    std::stringstream sstr(product);
    sstr >> productJson;
}

std::vector<std::string> ProductJSON::getValues()
{
    std::vector<std::string> offValues;
    unsigned int offCount = getOvCount();
    for (int i = 0; i < offCount; i++) {
        offValues.push_back(productJson["product"]["offValues"][i].asString());
    }
    return offValues;
}

unsigned int ProductJSON::getOvCount()
{
    return productJson["product"]["offValues"].size();
}

unsigned int ProductJSON::getImageCount()
{
    return productJson["product"]["images"].size();
}

unsigned int ProductJSON::getPropertyCount()
{
    return productJson["product"]["properties"].size();
}

Json::Value ProductJSON::getProductJson()
{
    return productJson;
}

std::vector<std::string> ProductJSON::getProperties()
{
    std::vector<std::string> propValues;
    unsigned int propCount = getPropertyCount();
    for (int i = 0; i < propCount; i++) {
        propValues.push_back(productJson["product"]["properties"][i].asString());
    }
    return propValues;
}

AddressJSON::AddressJSON(std::string buyer) {
    std::stringstream sstr(buyer);
    sstr >> addressJson;
}

AddressJSON::AddressJSON(std::string contactName, std::string city, std::string country, std::string address, std::string zipCode) {
    addressJson["contactName"] = contactName;
    addressJson["city"] = city;
    addressJson["country"] = country;
    addressJson["address"] = address;
    addressJson["zipCode"] = zipCode;
}

std::string AddressJSON::getAddress() {
    return addressJson["address"].asString();
}

std::string AddressJSON::getCity() {
    return addressJson["City"].asString();
}

std::string AddressJSON::getContactName() {
    return addressJson["contactName"].asString();
}

std::string AddressJSON::getCountry() {
    return addressJson["Country"].asString();
}

std::string AddressJSON::getZipCode() {
    return addressJson["zipCode"].asString();
}

Json::Value AddressJSON::getAddressJSON() {
    return addressJson;
}
