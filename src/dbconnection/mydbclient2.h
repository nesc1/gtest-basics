#pragma once
#include <iostream>
#include <memory>
#include "idatabaseconnect.h"

/// class under test for first challenge
class MyDbClient2
{
private:
    std::shared_ptr<IDatabaseConnect> m_db;

public:
    void setDatabase(std::shared_ptr<IDatabaseConnect> db)
    {
        m_db = std::move(db);
    }

    int init(const std::string& user, const std::string& pwd)
    {
        int ret = 0;
        if(m_db)
        {
            if(!m_db->login(user, pwd))
            {
                std::cout << "DB failure\n";
                ret = -1;
            }
            else
            {
                std::cout << "DB SUCCESS\n";
                ret = 1;
            }
        }
        return ret;
    }
};
