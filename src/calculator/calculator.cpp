#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <numeric>

#include <boost/algorithm/string/classification.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

using namespace std;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoDefault;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::Return;

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
// clang-format on
