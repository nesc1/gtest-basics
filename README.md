# Test Project

GTest and GMock simple tutorial and workplace to experiment with gtest and its functionalities.

## Challenges

### First Challenge

Using the `dbconnection` project  do:

- a test where the code being test is only the init function and nothing else and the login function must be called when the init funtion is called

`Note1:` class under test is now the `MyDbClient2` and the mock class is still the same one (`MockDatabaseConnect`)

`Note2:` start your implementation on `dbconnection2.cpp`

### Second challenge

On the project `calculator` complete the calculator functionality with multiplication and division operations.

`Note:` you can change the types that hold the input and output if desired. The main idea is to have several inputs and one or more tests testing these inputs and executing all four operations:

- addition,
- subtraction,
- multiplication and
- division

## Build steps

### Debug Build

```bash
mkdir -p conan
cd conan
conan install .. -s build_type=Debug --build=outdated --update
cd ..
mkdir -p build
cd build
mkdir -p debug
cd debug
cmake ../.. -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_INSTALL_PREFIX=../../install
cmake --build . --config Debug --target all
cmake --build . --config Debug --target install
```

## Overview

Learn how the google gtest and gmock works

## Common cases

- compare if function is called with values expected one time and remove when hit

```cpp
    EXPECT_CALL(mockclass, function(arg1expected, arg2expected))
        .Times(1)
        .RetiresOnSaturation();
```

- return function value as default when called

```cpp
    EXPECT_CALL(mockclass, funcName())
        .WillRepeatedly(Return(valueToReturn));
```

- return a value and change reference argument value (note that the following example is expecting that only one call is made and at the same time the value 5 is returned and bool reference parameter is changed to false)

```cpp
    EXPECT_CALL(mockclass, funcName(arg1expected, _))
        .WillOnce( DoAll( SetArgReferee<1>(false), Return(5) ) );
```

- call callback passed as argument by doing it in a lambda function

```cpp
    EXPECT_CALL(mockclass, funcName(arg1expected, _))
        .WillOnce( WithArg<1>( Invoke([](cbtype cb){
            //do some code
            ...
            //call the callback in the end
            cb(...);
        }) ) );
```

- call callback passed as argument by passing 'argpassedtocallback' to it

```cpp
    EXPECT_CALL(mockclass, funcName(arg1expected, _))
        .WillOnce(InvokeArgument<1>(argpassedtocallback));
```

- repeated test with different values

```cpp
// test input
struct TestInputOutput
{
    std::string          desc;
    std::vector<int>     numbers{};
    int                  result{ 0 };
    int                  diff{ 0 };
    friend std::ostream& operator<<(std::ostream&, const TestInputOutput&);
};
std::ostream& operator<<(std::ostream& os, const TestInputOutput& info)
{
    os << info.desc;
    return os;
}

// main test class where initializations can be done
class MainTest : public ::testing::TestWithParam<TestInputOutput>
{
public:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @test make the sum
 * @brief picks in the input and do the calculation and check if is equal to the result
 */
TEST_P(MainTest, makeSumCalculation)
{
    const auto& input  = GetParam().numbers;
    const auto& output = GetParam().result;

    ASSERT_EQ(std::accumulate(input.begin(), input.end(), 0), output);
}

/**
 * @test make the difference
 * @brief picks in the input and do the calculation and check if is equal to the result
 */
TEST_P(MainTest, makeMinusCalculation)
{
    const auto& input  = GetParam().numbers;
    const auto& output = GetParam().diff;

    ASSERT_EQ(std::accumulate(std::next(std::begin(input)), std::end(input), *std::begin(input), std::minus<int>()), output);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(ExampleListOfTests,
                         MainTest,
                         ::testing::Values(
    (
        // Case 1: normal sum
        TestInputOutput
        {
            "normal sum",
            {1,2,3},
            6, -4
        },
        // Case 2: big sum
        TestInputOutput
        {
            "big sum",
            {1000,23},
            1023, 977
        }
    )
));
```
