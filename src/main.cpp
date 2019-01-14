#include "letter_type.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

struct Counter {
    std::map<std::string, int> wordCount;
    void operator()(const std::string& item)
    {
        ++wordCount[item];
    }
    operator std::map<std::string, int>()
    {
        return wordCount;
    }
};

template <typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B>& p)
{
    return std::pair<B, A>(p.second, p.first);
}

template <typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B>& src)
{
    std::multimap<B, A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), flip_pair<A, B>);
    return dst;
}

int main(int argc, char** argv)
{
    int topCount = 20;
    string inputFile = "moby.txt";

    ifstream input;
    input.imbue(std::locale(std::locale(), new LetterType()));
    input.open(inputFile.c_str());
    if (!input.good()) {
        cout << "Oops! Input file " << inputFile << " couldn't be opened." << endl;
        return 0;
    }
    istream_iterator<string> start(input);
    istream_iterator<string> end;
    std::map<std::string, int> wordCount = std::for_each(start, end, Counter());
    std::multimap<int, string> wordCountOrderedByCount = flip_map(wordCount);
    int n = 0;
    for (std::multimap<int, string>::reverse_iterator it = wordCountOrderedByCount.rbegin();
         it != wordCountOrderedByCount.rend();
         ++it) {
        cout << setw(7) << it->first << " " << it->second << endl;
        if (++n >= topCount) break;
    }
    return 0;
}
