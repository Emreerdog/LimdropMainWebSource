//this file is generated by program(drogon_ctl) automatically,don't modify it!
#include "header.h"
#include <drogon/utils/OStringStream.h>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <deque>
#include <queue>
using namespace drogon;
std::string header::genText(const DrTemplateData& header_view_data)
{
	drogon::OStringStream header_tmp_stream;
	std::string layoutName{""};
	header_tmp_stream << "<img src=\"https://github.com/an-tao/drogon/wiki/images/drogon-white.jpg\"/>\n";
if(layoutName.empty())
{
std::string ret{std::move(header_tmp_stream.str())};
return ret;
}else
{
auto templ = DrTemplateBase::newTemplate(layoutName);
if(!templ) return "";
HttpViewData data = header_view_data;
auto str = std::move(header_tmp_stream.str());
if(!str.empty() && str[str.length()-1] == '\n') str.resize(str.length()-1);
data[""] = std::move(str);
return templ->genText(data);
}
}
