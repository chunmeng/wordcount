#include "letter_type.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace testing;

class LetterTest : public Test {
};

TEST_F(LetterTest, spaceStream)
{
    std::string in = "Word1 Word2 Word3";
    std::istringstream iss(in);
    iss.imbue(std::locale(std::locale(), new LetterType()));
    std::string out;
    std::vector<std::string> tokens;
    while (iss >> out) {
        tokens.push_back(out);
    }

    EXPECT_EQ(3, tokens.size());
    EXPECT_EQ("Word1", tokens.at(0));
    EXPECT_EQ("Word2", tokens.at(1));
    EXPECT_EQ("Word3", tokens.at(2));
}

TEST_F(LetterTest, enclosedStream)
{
    std::string in = "[Word1] {Word2} <Word3> \"Word4\" \'Word5\'";

    std::istringstream iss(in);
    iss.imbue(std::locale(std::locale(), new LetterType()));
    std::string out;
    std::vector<std::string> tokens;
    while (iss >> out) {
        tokens.push_back(out);
    }

    EXPECT_EQ(5, tokens.size());
    for (unsigned i = 0; i < tokens.size(); i++) {
        EXPECT_EQ("Word" + std::to_string(i + 1), tokens.at(i));
    }
}

TEST_F(LetterTest, punctStream)
{
    std::string in = "Word1! Word2? Word3!~ Word4. Word5, Word6; He's";
    std::istringstream iss(in);
    iss.imbue(std::locale(std::locale(), new LetterType()));

    std::string out;
    std::vector<std::string> tokens;
    while (iss >> out) {
        tokens.push_back(out);
    }

    EXPECT_EQ(8, tokens.size());
    EXPECT_EQ("Word1", tokens.at(0));
    EXPECT_EQ("Word2", tokens.at(1));
    EXPECT_EQ("Word3", tokens.at(2));
    EXPECT_EQ("Word4", tokens.at(3));
    EXPECT_EQ("Word5", tokens.at(4));
    EXPECT_EQ("Word6", tokens.at(5));
    EXPECT_EQ("He", tokens.at(6));
    EXPECT_EQ("s", tokens.at(7));
}

TEST_F(LetterTest, numberStream)
{
    std::string in = "1~ 2! 3 4@ 5# 6$ 7% 8^ 9& 10* 11( 12) 13- 14+ 15` 16_ 17= 18| 19\\ 20/";

    std::istringstream iss(in);
    iss.imbue(std::locale(std::locale(), new LetterType()));
    std::string out;
    std::vector<std::string> tokens;
    while (iss >> out) {
        tokens.push_back(out);
    }

    EXPECT_EQ(20, tokens.size());
    for (unsigned i = 0; i < tokens.size(); i++) {
        EXPECT_EQ(std::to_string(i + 1), tokens.at(i));
    }
}