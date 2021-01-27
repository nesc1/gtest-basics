#pragma once
#include <iostream>
#include "IDatabaseConnect.h"

/// class under test
class MyDatabase
{
    IDatabaseConnect& db;

public:
    MyDatabase(IDatabaseConnect& _db)
        : db(_db)
    {
    }

    int init(std::string user, std::string pwd)
    {
        int ret = 0;
        if(!db.login(user, pwd))
        {
            std::cout << "DB failure\n";
            ret = -1;
        }
        else
        {
            std::cout << "DB SUCCESS\n";
            ret = 1;
        }
        return ret;
    }
};
