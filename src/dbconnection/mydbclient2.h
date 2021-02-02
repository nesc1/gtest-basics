#pragma once
#include <iostream>
#include <memory>
#include "idatabaseconnect.h"

/// class under test for first challenge
class MyDbClient2
{
private:
    std::shared_ptr<IDatabaseConnect> m_db;
    bool                              m_initialized{ false };

public:
    void setDatabase(std::shared_ptr<IDatabaseConnect> db)
    {
        m_initialized = false;
        m_db          = std::move(db);
    }

    int init(const std::string& user, const std::string& pwd)
    {
        m_initialized = false;
        int ret       = 0;
        if(m_db)
        {
            if(!m_db->login(user, pwd))
            {
                std::cout << "DB failure\n";
                ret = -1;
            }
            else
            {
                m_initialized = true;
                std::cout << "DB SUCCESS\n";
                ret = 1;
            }
        }
        return ret;
    }

    int execute(const std::string& query, std::function<void(const std::string&)> cb)
    {
        int ret = 0;
        if(m_db && m_initialized)
        {
            ret = 1;
            m_db->fetchRecord(query, [query, cb](int result, const std::string& output) {
                //if result is 0 then the result has a valid value, otherwise result is invalid
                if(result == 0)
                {
                    std::cout << "fetch executed with SUCCESS (query: " << query << ")\n";
                    cb(output);
                }
                else
                {
                    std::cout << "fetch FAILED (query: " << query << ")\n";
                    std::string errmsg{ "fetch failed, err: " };
                    errmsg += std::to_string(result);
                    cb(errmsg);
                }
            });
        }
        return ret;
    }
};
