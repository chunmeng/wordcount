#include "args_parser.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class ArgsParserTest : public Test {
};

TEST_F(ArgsParserTest, inputTest)
{
    char progPath[] = "/test/program/path";

    char testoption1[] = "-1";
    char testarg1[] = "option1";
    char testoption2[] = "-2";
    char testarg2[] = "option2";
    char testoption3[] = "-3";
    char testarg3[] = "option3";

    const int argc = 7;
    char* argv[argc + 1];
    argv[0] = progPath;
    argv[1] = testoption1;
    argv[2] = testarg1;
    argv[3] = testoption2;
    argv[4] = testarg2;
    argv[5] = testoption3;
    argv[6] = testarg3;
    argv[argc] = nullptr;

    ArgsParser parser(argc, argv);
    EXPECT_TRUE(parser.optionExists("-1"));
    EXPECT_TRUE(parser.optionExists("-2"));
    EXPECT_TRUE(parser.optionExists("-3"));
    EXPECT_FALSE(parser.optionExists("-what"));

    EXPECT_EQ(std::string(testarg1), parser.getOption("-1"));
    EXPECT_EQ(std::string(testarg2), parser.getOption("-2"));
    EXPECT_EQ(std::string(testarg3), parser.getOption("-3"));
    EXPECT_EQ("", parser.getOption("-what"));
}