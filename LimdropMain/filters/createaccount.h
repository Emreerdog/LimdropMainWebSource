/**
 *
 *  createaccount.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class createaccount : public HttpFilter<createaccount>
{
  public:
    createaccount() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

