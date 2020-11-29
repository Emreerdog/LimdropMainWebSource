/**
 *
 *  checktraffic.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class checktraffic : public HttpFilter<checktraffic>
{
  public:
    checktraffic() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

