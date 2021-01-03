/**
 *
 *  passwordchangefilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class passwordchangefilter : public HttpFilter<passwordchangefilter>
{
  public:
    passwordchangefilter() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

