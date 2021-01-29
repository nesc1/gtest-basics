#pragma once
#include <string>
#include <functional>

/// interface class for a database connection
class IDatabaseConnect
{
public:
    virtual bool login(const std::string& /*user*/, const std::string& /*pass*/) { return true; }
    virtual bool logout(const std::string& /*user*/) { return true; }
    virtual int  fetchRecord(const std::string& /*sql*/, std::function<int()> /*cbresult*/) { return -1; }
};