#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoDefault;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::Return;

/// get correct path if is a relative path then it adds the base on it
inline boost::filesystem::path getCorrectPath(const boost::filesystem::path& relative_path,
                                              const boost::filesystem::path& base,
                                              boost::system::error_code&     ec)
{
    boost::filesystem::path res = boost::filesystem::canonical(relative_path, base, ec);
    if(ec)
    {
        if(relative_path.is_relative())
        {
            res = base;
            res.make_preferred();
            res /= relative_path;
        }
        else
        {
            res = relative_path;
        }
    }
    res.make_preferred();
    return boost::filesystem::absolute(res);
}
inline boost::filesystem::path getCorrectPath(const boost::filesystem::path& relative_path,
                                              const boost::filesystem::path& base = boost::filesystem::current_path())
{
    boost::system::error_code ec;
    return getCorrectPath(relative_path, base, ec);
}

/**
 * @test check absolute path returns
 * @brief test build of absolute paths
 */
TEST(FileSystem, absolute)
{
    // not exist
    ASSERT_EQ(getCorrectPath(R"(..\..\gtest)", R"(C:\git\tests\gtest\other\other)"),
              boost::filesystem::path(R"(C:\git\tests\gtest\other\other\..\..\gtest)"));
    ASSERT_EQ(getCorrectPath(R"(..\..\gtest)", R"(C:\)"), boost::filesystem::path(R"(C:\..\..\gtest)"));

    boost::filesystem::path full_path(boost::filesystem::current_path());
    // valid paths
    std::string dirname = full_path.filename().string();
    ASSERT_EQ(getCorrectPath(full_path, R"(c:\)"), full_path);
    ASSERT_EQ(getCorrectPath(R"(.\)" + dirname, full_path.parent_path()), full_path);
    ASSERT_EQ(getCorrectPath(R"(..\)" + dirname, full_path), full_path);
    ASSERT_EQ(getCorrectPath(R"(..\..)", full_path), full_path.parent_path().parent_path());
}
