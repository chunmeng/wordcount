#ifndef MAP_TRANSFORM_H
#define MAP_TRANSFORM_H

#include <algorithm>
#include <cstring>
#include <set>
#include <string>
#include <unordered_map>

//! MapTransform
//! Utility class to transform a map[A]:B to set[B]:A.
//! Output multiset to allow duplicate value as key and sorting by both key and value
class MapTransform {
public:
    template <typename A, typename B>
    static std::pair<B, A> FlipPair(const std::pair<A, B>& p)
    {
        return std::pair<B, A>(p.second, p.first);
    }

    //! tranform the map to a set with given camparator. Default order is greater first (descending)
    template <template <typename...> class Map, typename A, typename B, typename Comparator = std::greater<std::pair<B,A>>>
    static std::multiset<std::pair<B, A>, Comparator> FlipMap(const Map<A, B>& src, Comparator c = Comparator())
    {
        std::multiset<std::pair<B, A>, Comparator> dst;
        std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), MapTransform::FlipPair<A, B>);
        return dst;
    }
};

#endif // MAP_TRANSFORM_H
