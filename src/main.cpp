#include "args_parser.h"
#include "letter_type.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

static const int DefaultNumToDisplay = 20;
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

void printHelp()
{
    cout << "wordfreq usage:\n";
    cout << "-h     Print\n";
    cout << "-f filename\n";
    cout << "-n N \n";
}

int main(int argc, char** argv)
{
    string inputFile = "";

    // Parse arguments
    ArgsParser args(argc, argv);
    if (argc <= 1 || args.optionExists("-h")) {
        printHelp();
        return 0;
    }
    const std::string& filename = args.getOption("-f");
    if (filename.empty()) {
        cout << "Error: input file is mandatory.\n";
        printHelp();
        return 0;
    }
    inputFile = filename;

    unsigned entryToDisplay = DefaultNumToDisplay;
    const std::string& head = args.getOption("-n");
    if (!head.empty()) {
        // Attempt convert to number and sanity check
        try {
            auto n = std::stoi(head);
            if (n <= 0) {
                cout << "Warn: Invalid value for -n " << head << ", default value (" << entryToDisplay
                     << ") will be used.\n";
            } else {
                entryToDisplay = n;
            }
        } catch (std::exception& e) {
            cout << "Warn: Unable to parse -n, default value (" << entryToDisplay << ") will be used.\n";
        }
    }

    ifstream input;
    input.imbue(std::locale(std::locale(), new LetterType()));
    input.open(inputFile.c_str());
    if (!input.good()) {
        cout << "Error: Oops! Input file \"" << inputFile << "\" couldn't be opened." << endl;
        return 0;
    }
    istream_iterator<string> start(input);
    istream_iterator<string> end;
    // read stream and fill into a map[word]: count
    std::map<std::string, int> wordCount = std::for_each(start, end, Counter());
    // transform to map[count]: word, use multimap to allow duplicate key (same count)
    std::multimap<int, string> wordCountOrderedByCount = flip_map(wordCount);
    int n = 0;
    for (std::multimap<int, string>::reverse_iterator it = wordCountOrderedByCount.rbegin();
         it != wordCountOrderedByCount.rend();
         ++it) {
        cout << setw(7) << it->first << " " << it->second << endl;
        if (++n >= entryToDisplay) break;
    }
    return 0;
}
