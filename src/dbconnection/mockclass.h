#pragma once
#include <gmock/gmock.h>
#include <string>

#include "IDatabaseConnect.h"

//! mock class (of interface class)
//! we can also mocking wihout deriving from class doing only:
//! class DatabaseConnect { }  << this will obligate to not include the real code
class MockDB : public IDatabaseConnect
{
public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(logout, bool(std::string));
    MOCK_METHOD2(login, bool(std::string, std::string));
};