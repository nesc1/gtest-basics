#pragma once
#include <iostream>
#include "idatabaseconnect.h"

/// class under test
/// it simulates a client that performs a connection to a database
/// the interface with the database is offered by the interface IDatabaseConnect
class MyDbClient
{
private:
    IDatabaseConnect& m_db;

public:
    explicit MyDbClient(IDatabaseConnect& _db)
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
