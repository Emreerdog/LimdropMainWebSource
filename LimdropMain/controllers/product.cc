#include "product.h"
#include "limjson.h"


void product::details(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback, std::string itemId)
{
	std::string _itemId = itemId;
	// Check if it is number
	for(int i = 0; i < _itemId.length(); i++){
		if(!(_itemId[i] >= '0' && _itemId[i] <= '9')){
			auto resp = HttpResponse::newNotFoundResponse();
			callback(resp);
			return;
		}
	}
	auto clientPtr = drogon::app().getDbClient();
	std::string totalQuery1 = "SELECT id, title, outofdatetime, maximumproductcount, isbuyable, customercount, type, brand, price, details FROM products WHERE id=" + itemId;
	auto f1 = clientPtr->execSqlAsyncFuture(totalQuery1);
	auto result1 = f1.get();
	if(result1.size() == 0){
		auto resp = HttpResponse::newRedirectionResponse("/bum");
		callback(resp);
		return;
	}
	std::string title;
	std::string outOfDateTime;
	std::string maximumProductCount;
	std::string isBuyable;
	std::string customerCount;
	std::string type;
	std::string brand;
	std::string price;
	std::string detailsJSON;
	for(auto row : result1){
		title = row["title"].as<std::string>();
		outOfDateTime = row["outofdatetime"].as<std::string>();
		maximumProductCount = row["maximumproductcount"].as<std::string>();
		isBuyable = row["isbuyable"].as<std::string>();
		customerCount = row["customercount"].as<std::string>();
		type = row["type"].as<std::string>();
		brand = row["brand"].as<std::string>();
		price = row["price"].as<std::string>();
		detailsJSON = row["details"].as<std::string>();

	}
	ProductJSON PJ(detailsJSON);
	std::vector<std::string> imagePaths = PJ.getImagePaths();
	std::vector<std::string> values = PJ.getValues();
	unsigned int imageCount = PJ.getImageCount();
	unsigned int valueCount = PJ.getOvCount();

	std::cout << "Title is: " << title << std::endl;
	std::cout << "Out of date time is: " << outOfDateTime << std::endl;
	std::cout << "Maximum product count is: " << maximumProductCount << std::endl;
	std::cout << "Buyable status is: " << isBuyable << std::endl;
	std::cout << "Customer count is: " << customerCount << std::endl;
	std::cout << "Type is: " << type << std::endl;
	std::cout << "Brand is: " << brand << std::endl;
	std::cout << "Price is: " << price << std::endl;

	unsigned int j = 1;
	std::vector<std::string>::iterator It1;

	// Off value iterator
	for(It1 = values.begin(); It1 != values.end(); It1++){
		std::stringstream ss;
		ss << j;
		std::string valueOutput = "OffValue " + ss.str() + " is: ";
		float beforeFloor = std::stof(*It1);
		float floored = floorf(beforeFloor * 100) / 100;
		std::cout << valueOutput << floored << std::endl;
		j++;
	}
	j = 1;
	// Image path iterator
	std::vector<std::string>::iterator It2;
	for(It2 = imagePaths.begin(); It2 != imagePaths.end(); It2++){
		std::stringstream ss;
		ss << j;
		std::string pathOutput = "Image path " + ss.str() + " is: " + *It2;
		std::cout << pathOutput << std::endl;
		j++;
	}
	imagePaths.clear();
	values.clear();
}
