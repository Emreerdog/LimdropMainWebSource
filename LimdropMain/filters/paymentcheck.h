/**
 *
 *  paymentcheck.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class paymentcheck : public HttpFilter<paymentcheck>
{
  public:
    paymentcheck() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

