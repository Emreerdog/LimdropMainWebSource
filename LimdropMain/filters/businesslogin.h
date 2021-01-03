/**
 *
 *  businesslogin.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class businesslogin : public HttpFilter<businesslogin>
{
  public:
    businesslogin() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

