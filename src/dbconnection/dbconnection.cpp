#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "mockclass.h"
#include "database.h"

using namespace std;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::DoDefault;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::Return;

/// test without fixture
TEST(MyDBTest, loginTest)
{
    // prepare
    MockDB     mdb;
    MyDatabase db(mdb);

    // EXPECT_CALL and ON_CALL differs from requirement, expect requires to happen while on_call no
    EXPECT_CALL(mdb, login("Terminator", _))
        .Times(1)
        .WillOnce(Return(true));
    ON_CALL(mdb, login(_, _))
        .WillByDefault(Return(true));

    // act
    int retval = db.init("Terminator", "I will be back!");

    // expect vs assert - expect does not stop the execution if fails assert do
    EXPECT_EQ(retval, 1);
    ASSERT_EQ(retval, 1);
}

//
// tests with fixtures
//

/// the fixture is usuful to prepare the tests with inital data or clean it
class MyTestFixtureForDB : public ::testing::Test
{
public:
    MockDB     mdb;
    MyDatabase db;

    MyTestFixtureForDB()
        : db(mdb)
    {
    }

    void SetUp() override {}
    void TearDown() override {}
};

/// make the same test with fixture
TEST_F(MyTestFixtureForDB, testTheSameWithFixture)
{
    // Arrange
    EXPECT_CALL(mdb, login("Terminator", _))
        .Times(1)
        .WillOnce(Return(true));

    // Act
    int retval = db.init("Terminator", "I will be back!");

    // Assert
    ASSERT_EQ(retval, 1);
}

struct testABC
{
    bool dummyLogin(string a, string b)
    {
        cout << "Dummy login...\n";
        return true;
    }
};

/// using invoke to call another or original method like:
/// DatabaseConnect dbTest;
/// EXPECT_CALL(mdb, login("Terminator", _)).Times(AtLeast(1)).WillOnce(Invoke(&dbTest, &DatabaseConnect::login));
/// or using our own implementation
TEST_F(MyTestFixtureForDB, invokeAnotherImplementation)
{
    // Arrange
    testABC dbTest;
    EXPECT_CALL(mdb, login("Terminator", _))
        .Times(1)
        .WillOnce(Invoke(&dbTest, &testABC::dummyLogin));

    // Act
    int retval = db.init("Terminator", "I will be back!");

    // Assert
    ASSERT_EQ(retval, 1);
}

bool globalDummyFunc()
{
    cout << "Dummy global func...\n";
    return true;
}

/// using global function (note that this function can not have parameters)
TEST_F(MyTestFixtureForDB, invokeGlobalFunction)
{
    // Arrange
    EXPECT_CALL(mdb, login("Terminator", _))
        .Times(1)
        .WillOnce(InvokeWithoutArgs(globalDummyFunc));

    // Act
    int retval = db.init("Terminator", "I will be back!");

    // Assert
    ASSERT_EQ(retval, 1);
}

/// default action using the DoDefault(), this will call the ON_CALL defined previously
TEST_F(MyTestFixtureForDB, invokeWithDefaultAction)
{
    // Arrange
    testABC tdb;
    ON_CALL(mdb, login(_, _))
        .WillByDefault(Invoke(&tdb, &testABC::dummyLogin));
    EXPECT_CALL(mdb, login("Terminator", _))
        .Times(AtLeast(1))
        .WillOnce(DoDefault());

    // Act
    int retval = db.init("Terminator", "I will be back!");

    // Assert
    ASSERT_EQ(retval, 1);
}

struct testABC2
{
    void dummyLogin(string a, string b) { cout << "Dummy login without return...\n"; }
};

/// multiple actions,  the only catch is that only the last action must return the expected type
TEST_F(MyTestFixtureForDB, invokeWithMultiActions)
{
    // Arrange
    testABC2 tdb;
    EXPECT_CALL(mdb, login("Terminator", _))
        .Times(AtLeast(1))
        .WillOnce(DoAll(Invoke(&tdb, &testABC2::dummyLogin),
                        Invoke(&tdb, &testABC2::dummyLogin),
                        Invoke(&tdb, &testABC2::dummyLogin),
                        Return(true)  // only the last one should return the expected type
                        ));

    // Act
    int retval = db.init("Terminator", "I will be back!");

    // Assert
    ASSERT_EQ(retval, 1);
}
