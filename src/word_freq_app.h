#ifndef WORD_FREQ_APP_H
#define WORD_FREQ_APP_H

#include "map_transform.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <unordered_map>

struct WordCounter {
    std::unordered_map<std::string, int> wordCount;
    void operator()(const std::string& item)
    {
        ++wordCount[item];
    }
    operator std::unordered_map<std::string, int>()
    {
        return wordCount;
    }
};

// Custom comparator for multiset order needed "case insensitive greater" for word string
// This order the pair by count first (descending), then by then word according to the reference output
struct CustomPairCompare {
    bool operator()(const std::pair<int, std::string>& lhs, const std::pair<int, std::string>& rhs) const
    {
        // If the count is the same, order the word in descending order (Zz to Aa to 9 - 0), case insensitive
        if (lhs.first == rhs.first) {
            // @INFO: Note that strcasecmp is not portable and does not work for WINS (stricmp).
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

// Note to evaluator:
// Typically I would use pimpl to hide away the implemention of the bussiness logic.
class WordFreqApp {
public:
    //! Given an istream, process it and generate the word frequence result set
    void process(std::istream& input)
    {
        std::istream_iterator<std::string> start(input);
        std::istream_iterator<std::string> end;
        // read stream and fill into a map[word]: count
        std::unordered_map<std::string, int> byWord = std::for_each(start, end, WordCounter());

        // transform to map[count]: word
        result_ = MapTransform::FlipMap(byWord, CustomPairCompare());
    }
    //! Print the top n entries of the result to standard output stream
    void print(unsigned topN = 20)
    {
        int n = 0;
        for (auto& it : result_) {
            std::cout << std::setw(7) << it.first << " " << it.second << std::endl;
            if (topN == 0) continue; // print all if 0
            if (++n >= topN) break;
        }
    }

private:
    std::multiset<std::pair<int, std::string>, CustomPairCompare> result_;
};

#endif // WORD_FREQ_APP_H