/**
 *
 *  profilechangefilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class profilechangefilter : public HttpFilter<profilechangefilter>
{
  public:
    profilechangefilter() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

