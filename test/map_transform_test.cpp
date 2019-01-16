#include "map_transform.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

class MapTransformTest : public Test {
};

TEST_F(MapTransformTest, flipPairTest)
{
    std::pair<std::string, int> in = {"Key", 1};
    auto out = MapTransform::FlipPair(in);
    EXPECT_EQ(1, out.first);
    EXPECT_EQ("Key", out.second);
}

// TEST_F(MapTransformTest, flipMapTest)
// {
//     std::map<std::string, int> in = {{"Key1", 1}, {"Key2", 2}, {"Key3", 3}};
//     auto out = MapTransform::FlipMap(in);
//     EXPECT_EQ(3, out.size());
//     auto n = 1;
//     for (auto& o : out) {
//         EXPECT_EQ(n, o.first);
//         EXPECT_EQ("Key" + std::to_string(n), o.second);
//         n++;
//     }
// }

// TEST_F(MapTransformTest, flipMapDupTest)
// {
//     std::map<std::string, int> in = {{"Key1", 1}, {"Key2", 1}, {"Key3", 1}};
//     // test operation
//     auto out = MapTransform::FlipMap(in);
//     EXPECT_EQ(3, out.size());
//     auto n = 1;
//     for (auto& o : out) {
//         EXPECT_EQ(1, o.first);
//         EXPECT_EQ("Key" + std::to_string(n), o.second);
//         n++;
//     }
// }

// TEST_F(MapTransformTest, flipDefaultMapDupOrderCheckTest)
// {
//     // Default map insertion order
//     std::map<std::string, int> in = {{"the", 1000},
//                                      {"theA", 100},
//                                      {"theZ", 100},
//                                      {"thea", 100},
//                                      {"thez", 100},
//                                      {"the1", 100},
//                                      {"the9", 100},
//                                      {"the0", 10}};
//     {
//         std::vector<std::string> expectedFirst = {"the", "the0", "the1", "the9", "theA", "theZ", "thea", "thez"};
//         std::vector<int> expectedSecond = {1000, 10, 100, 100, 100, 100, 100, 100};
//         auto n = 0;
//         // Test note: Just checking default map sort order
//         for (auto& i : in) {
//             EXPECT_EQ(expectedFirst.at(n), i.first);
//             EXPECT_EQ(expectedSecond.at(n), i.second);
//             n++;
//         }
//     }

//     // test operation
//     auto out = MapTransform::FlipMap(in);

//     std::vector<std::string> expectedSecond = {"the", "thez", "thea", "theZ", "theA", "the9", "the1", "the0"};
//     std::vector<int> expectedFirst = {1000, 100, 100, 100, 100, 100, 100, 10};
//     auto n = 0;
//     // Test note: map are ordered ascending, so test reserve iterator
//     for (auto it = out.rbegin(); it != out.rend(); ++it) {
//         EXPECT_EQ(expectedFirst.at(n), it->first);
//         EXPECT_EQ(expectedSecond.at(n), it->second);
//         n++;
//     }
// }

// TEST_F(MapTransformTest, dupCustomOrderCheckWordsTest)
// {
//     // Map with custom case sensity greater order (i.e. z ... a)
//     std::map<std::string, int, std::greater<std::string>> in = {{"u", 1}, {"voyaging", 1},
//                                      {"voyagers", 1},
//                                      {"VOYAGER", 1},
//                                      {"voyaged", 1}};
//     {
//         std::vector<std::string> expectedFirst = {"voyaging", "voyagers", "VOYAGER", "voyaged", "u"};
//         std::vector<int> expectedSecond = {1, 1, 1, 1, 1};
//         auto n = 0;
//         // Test note: Just checking the map sort order
//         for (auto& i : in) {
//             EXPECT_EQ(expectedFirst.at(n), i.first);
//             EXPECT_EQ(expectedSecond.at(n), i.second);
//             n++;
//         }
//     }

//     auto out = MapTransform::FlipMap(in);

//     std::vector<std::string> expectedSecond = {"voyaging", "voyagers", "VOYAGER", "voyaged", "u"};
//     std::vector<int> expectedFirst = {1, 1, 1, 1, 1};
//     auto n = 0;
//     // Test note: map are ordered ascending, so test reserve iterator
//     for (auto it = out.rbegin(); it != out.rend(); ++it) {
//         EXPECT_EQ(expectedFirst.at(n), it->first);
//         EXPECT_EQ(expectedSecond.at(n), it->second);
//         n++;
//     }
// }

// TEST_F(MapTransformTest, dupCustomOrderCheckCIWordsTest)
// {
//     // This is obviously not what's wanted - just testing the behavior
//     // Map with custom case insensity greater order (i.e. z ... a)
//     std::map<std::string, int, CiGreater> in = {{"VOYAG", 1}, {"VOYAg", 1},
//                                      {"VOYag", 1},
//                                      {"VOyag", 1},
//                                      {"Voyag", 1},
//                                      {"voyag", 1}};
//     {
//         std::vector<std::string> expectedFirst = {"VOYAG"};
//         std::vector<int> expectedSecond = {1};
//         auto n = 0;
//         // Test note: Just checking the map sort order
//         for (auto& i : in) {
//             EXPECT_EQ(expectedFirst.at(n), i.first);
//             EXPECT_EQ(expectedSecond.at(n), i.second);
//             n++;
//         }
//     }

//     auto out = MapTransform::FlipMap(in);

//     std::vector<std::string> expectedSecond = {"VOYAG"};
//     std::vector<int> expectedFirst = {1};
//     auto n = 0;
//     // Test note: map are ordered ascending, so test reserve iterator
//     for (auto it = out.rbegin(); it != out.rend(); ++it) {
//         EXPECT_EQ(expectedFirst.at(n), it->first);
//         EXPECT_EQ(expectedSecond.at(n), it->second);
//         n++;
//     }
// }