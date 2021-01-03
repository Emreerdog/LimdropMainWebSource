/**
 *
 *  changeparamsfilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class changeparamsfilter : public HttpFilter<changeparamsfilter>
{
  public:
    changeparamsfilter() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

