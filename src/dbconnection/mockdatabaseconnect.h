#pragma once
#include <gmock/gmock.h>
#include <string>

#include "idatabaseconnect.h"

/// mock class (of interface class)
/// we can also mocking wihout deriving from class doing only:
/// class DatabaseConnect { }  << this will obligate to not include the real code
class MockDatabaseConnect : public IDatabaseConnect
{
public:
    MOCK_METHOD2(fetchRecord, int(const std::string&, std::function<int()>));
    MOCK_METHOD1(logout, bool(const std::string&));
    MOCK_METHOD2(login, bool(const std::string&, const std::string&));
};