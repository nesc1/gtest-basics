#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "mockclass.h"
#include "database2.h"

using namespace std;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::DoDefault;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::Return;

//
// First challenge:
//
// create a test where the code being test is only the init function and nothing else
// and the login function must be called when the init funtion is called
//
// The class under test to use should be now the MyDatabase2
//
