#ifndef MAP_TRANSFORM_H
#define MAP_TRANSFORM_H

#include <algorithm>
#include <cstring>
#include <set>
#include <string>
#include <unordered_map>

// Custom comparator for multiset order needed "case insensitive greater" for word string
// This order the pair by count first (descending), then by then word according to the reference output
struct CustomPairComp {
    bool operator()(const std::pair<int, std::string>& lhs, const std::pair<int, std::string>& rhs) const
    {
        // If the count is the same, order the word in descending order (Zz to Aa to 9 - 0), case insensitive
        if (lhs.first == rhs.first) {
            // @INFO: Note that strcasecmp is not portable and does not work for WINS.
            // I used it here because the assignment does not required WINS support, and according to the comment on SO
            // https://stackoverflow.com/questions/1801892/making-mapfind-operation-case-insensitive, it is much faster
            // than stl version of the implementation. (not personally profiled)
            int ret = strcasecmp(lhs.second.c_str(), rhs.second.c_str());
            // If the 2 words are exactly same in case insensitive compare, then sort case sensitive (Z above, z below)
            if (ret == 0) return (lhs.second < rhs.second);

            return (ret > 0);
        }

        return lhs.first > rhs.first;
    }
};

//! MapTransform
//! Utility class to transform a map[A]:B to map[B]:A. Output multimap to allow duplicate value as key
class MapTransform {
public:
    template <typename A, typename B>
    static std::pair<B, A> FlipPair(const std::pair<A, B>& p)
    {
        return std::pair<B, A>(p.second, p.first);
    }

    template <typename A, typename B, template <typename...> class Map>
    static std::multiset<std::pair<B, A>, CustomPairComp> FlipMap(const Map<A, B>& src)
    {
        std::multiset<std::pair<B, A>, CustomPairComp> dst;
        std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), MapTransform::FlipPair<A, B>);
        return dst;
    }
};

#endif // MAP_TRANSFORM_H
