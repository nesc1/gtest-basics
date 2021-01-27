#pragma once
#include <string>

/// interface class
class IDatabaseConnect
{
public:
    virtual bool login(std::string user, std::string pass) { return true; }
    virtual bool logout(std::string user) { return true; }
    virtual int  fetchRecord() { return -1; }
};