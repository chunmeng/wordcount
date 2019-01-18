#include "map_transform.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cctype>

using namespace testing;

struct TestComparator {
    bool operator()(const std::pair<int, std::string>& lhs, const std::pair<int, std::string>& rhs) const
    {
        // If the count is the same, order the word in descending order (Zz to Aa to 9 - 0), case insensitive
        if (lhs.first == rhs.first) {
            int ret = strcasecmp(lhs.second.c_str(), rhs.second.c_str());
            // If the 2 words are exactly same in case insensitive compare, then sort case sensitive (Z above, z below)
            if (ret == 0) return (lhs.second < rhs.second);

            return (ret > 0);
        }

        return lhs.first > rhs.first;
    }
};

class MapTransformTest : public Test {
};

TEST_F(MapTransformTest, flipPairTest)
{
    std::pair<std::string, int> in = {"Key", 1};
    auto out = MapTransform::FlipPair(in);
    EXPECT_EQ(1, out.first);
    EXPECT_EQ("Key", out.second);
}

TEST_F(MapTransformTest, flipMapTest)
{
    std::unordered_map<std::string, int> in = {{"Key1", 1}, {"Key2", 2}, {"Key3", 3}};
    auto out = MapTransform::FlipMap(in);
    EXPECT_EQ(3, out.size());
    auto n = out.size();
    for (auto& o : out) {
        EXPECT_EQ(n, o.first);
        EXPECT_EQ("Key" + std::to_string(n), o.second);
        n--;
    }
}

TEST_F(MapTransformTest, flipMapDupTest)
{
    std::map<std::string, int> in = {{"Key1", 1}, {"Key2", 1}, {"Key3", 1}};
    // test operation
    auto out = MapTransform::FlipMap(in);
    EXPECT_EQ(3, out.size());
    auto n = out.size();
    for (auto& o : out) {
        EXPECT_EQ(1, o.first);
        EXPECT_EQ("Key" + std::to_string(n), o.second);
        n--;
    }
}

TEST_F(MapTransformTest, flipHashMapDupTest)
{
    std::unordered_map<std::string, int> in = {{"Key1", 1}, {"Key2", 1}, {"Key3", 1}};
    // test operation
    auto out = MapTransform::FlipMap(in);
    EXPECT_EQ(3, out.size());
    auto n = out.size();
    for (auto& o : out) {
        EXPECT_EQ(1, o.first);
        EXPECT_EQ("Key" + std::to_string(n), o.second);
        n--;
    }
}

// This tests the map transform with default comparater
TEST_F(MapTransformTest, flipMapSortOrderCheckDefault)
{
    std::unordered_map<std::string, int> in = {{"the", 1000},
                                               {"theA", 100},
                                               {"theZ", 100},
                                               {"thea", 100},
                                               {"thez", 100},
                                               {"the1", 100},
                                               {"the9", 100},
                                               {"the0", 10}};

    // test operation
    auto out = MapTransform::FlipMap(in);

    std::vector<std::string> expectedSecond = {"the", "thez", "thea", "theZ", "theA", "the9", "the1", "the0"};
    std::vector<int> expectedFirst = {1000, 100, 100, 100, 100, 100, 100, 10};
    auto n = 0;
    for (auto& o : out) {
        EXPECT_EQ(expectedFirst.at(n), o.first);
        EXPECT_EQ(expectedSecond.at(n), o.second);
        n++;
    }
}

// This tests the map transform with custom comparater
TEST_F(MapTransformTest, flipMapSortOrderCheckCustom)
{
    std::unordered_map<std::string, int> in = {{"the", 1000},
                                               {"theA", 100},
                                               {"theZ", 100},
                                               {"thea", 100},
                                               {"thez", 100},
                                               {"the1", 100},
                                               {"the9", 100},
                                               {"the0", 10}};

    // test operation
    auto out = MapTransform::FlipMap(in, TestComparator());

    std::vector<std::string> expectedSecond = {"the", "theZ", "thez", "theA", "thea", "the9", "the1", "the0"};
    std::vector<int> expectedFirst = {1000, 100, 100, 100, 100, 100, 100, 10};
    auto n = 0;
    for (auto& o : out) {
        EXPECT_EQ(expectedFirst.at(n), o.first);
        EXPECT_EQ(expectedSecond.at(n), o.second);
        n++;
    }
}

// This tests the map transform with default comparater
TEST_F(MapTransformTest, flipMapSortOrderCheckDefaultWithCaseConflict)
{
    std::unordered_map<std::string, int> in = {
            {"u", 1}, {"voyaging", 1}, {"voyagers", 1}, {"VOYAGER", 1}, {"voyager", 1}};

    auto out = MapTransform::FlipMap(in);

    std::vector<std::string> expectedSecond = {"voyaging", "voyagers", "voyager", "u", "VOYAGER"};
    std::vector<int> expectedFirst = {1, 1, 1, 1, 1};
    auto n = 0;
    for (auto& o : out) {
        EXPECT_EQ(expectedFirst.at(n), o.first);
        EXPECT_EQ(expectedSecond.at(n), o.second);
        n++;
    }
}

// This tests the map transform with custom comparater
TEST_F(MapTransformTest, flipMapSortOrderCheckCustomWithCaseConflict)
{
    std::unordered_map<std::string, int> in = {
            {"u", 1}, {"voyaging", 1}, {"voyagers", 1}, {"VOYAGER", 1}, {"voyager", 1}};

    auto out = MapTransform::FlipMap(in, TestComparator());

    std::vector<std::string> expectedSecond = {"voyaging", "voyagers", "VOYAGER", "voyager", "u"};
    std::vector<int> expectedFirst = {1, 1, 1, 1, 1};
    auto n = 0;
    for (auto& o : out) {
        EXPECT_EQ(expectedFirst.at(n), o.first);
        EXPECT_EQ(expectedSecond.at(n), o.second);
        n++;
    }
}