/**
 *
 *  login.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;


class login : public HttpFilter<login>
{
  public:
    login() {}
    virtual void doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb) override;
};

