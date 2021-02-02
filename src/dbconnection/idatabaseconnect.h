#pragma once
#include <string>
#include <functional>

/// callback for fetch function
using FetchCb = std::function<void(int, const std::string&)>;

/// interface class for a database connection
class IDatabaseConnect
{
public:
    virtual bool login(const std::string& /*user*/, const std::string& /*pass*/) { return true; }
    virtual bool logout(const std::string& /*user*/) { return true; }
    virtual void fetchRecord(const std::string& /*query*/, FetchCb /*cb*/) {}
};