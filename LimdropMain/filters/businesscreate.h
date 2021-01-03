/**
 *
 *  businesscreate.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class businesscreate : public HttpFilter<businesscreate>
{
  public:
    businesscreate() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

