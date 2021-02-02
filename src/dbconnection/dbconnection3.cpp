#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "mockdatabaseconnect.h"
#include "mydbclient2.h"

using namespace std;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::DoDefault;
using ::testing::Invoke;
using ::testing::InvokeArgument;
using ::testing::InvokeWithoutArgs;
using ::testing::Return;
using ::testing::WithArg;

//
// Fourth challenge:
//
// create one or more tests to validate the MyDbClient2::execute with a valid return and test
// IDatabaseConnect::fetchRecord with a valid and an invalid return use case
//
// The class under test to use should be the MyDbClient2
//
