#pragma once
#include <iostream>
#include "IDatabaseConnect.h"

/// class under test
class MyDatabase
{
    IDatabaseConnect& m_db;

public:
    explicit MyDatabase(IDatabaseConnect& _db)
        : m_db(_db)
    {
    }

    int init(const std::string& user, const std::string& pwd)
    {
        int ret = 0;
        if(!m_db.login(user, pwd))
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
