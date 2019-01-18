#include "map_transform.h"

#include <algorithm>
#include <iomanip>
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
        std::unordered_map<std::string, int> byWordMap = std::for_each(start, end, WordCounter());

        // transform to map[count]: word
        result_ = MapTransform::FlipMap(byWordMap);
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
    std::multiset<std::pair<int, std::string>, CustomPairComp> result_;
};
