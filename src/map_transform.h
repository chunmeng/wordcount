#ifndef MAP_TRANSFORM_H
#define MAP_TRANSFORM_H

#include <algorithm>
#include <cstring>
#include <set>
#include <string>
#include <unordered_map>

// This is a custom comparator for case insensitive greater
// This is taken and modified from https://stackoverflow.com/questions/1801892/making-mapfind-operation-case-insensitive
// According to the comment is much faster than stl version of the implementation. (I've not verified)
// Note that strcasecmp is not portable and does not work for Windows.
struct CiGreater {
    bool operator()(const std::string& lhs, const std::string& rhs) const
    {
        return strcasecmp(lhs.c_str(), rhs.c_str()) > 0;
    }
};

struct CiLess {
    bool operator()(const std::string& lhs, const std::string& rhs) const
    {
        return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
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

    template <typename A, typename B>
    static std::multiset<std::pair<B, A>> FlipMap(const std::unordered_map<A, B>& src)
    {
        std::multiset<std::pair<B, A>> dst;
        std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), MapTransform::FlipPair<A, B>);
        return dst;
    }
};

#endif // MAP_TRANSFORM_H
