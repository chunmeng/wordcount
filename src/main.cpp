#include "args_parser.h"
#include "letter_type.h"
#include "map_transform.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

static const int DefaultNumToDisplay = 20;
struct Counter {
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

static void PrintHelp()
{
    cout << "wordfreq usage:\n";
    cout << "\t -f filename   Mandatory. Provide the input file to be analyzed.\n";
    cout << "\t -n N          Optional. Provide number of top entries to display.\n";
    cout << "\t               Default 20. 0 to display all entries.\n";
    cout << "\t -h            Print this help.\n";
}

int main(int argc, char** argv)
{
    string inputFile = "";

    // Parse arguments
    ArgsParser args(argc, argv);
    if (argc <= 1 || args.optionExists("-h")) {
        PrintHelp();
        return 0;
    }
    const std::string& filename = args.getOption("-f");
    if (filename.empty()) {
        cout << "Error: input file is mandatory.\n";
        PrintHelp();
        return 0;
    }
    inputFile = filename;

    unsigned entryToDisplay = DefaultNumToDisplay;
    const std::string& head = args.getOption("-n");
    if (!head.empty()) {
        // Attempt convert to number and sanity check
        try {
            auto n = std::stoi(head);
            if (n < 0) {
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
    input.open(inputFile.c_str());
    if (!input.good()) {
        cout << "Error: Oops! Input file \"" << inputFile << "\" couldn't be opened." << endl;
        return 0;
    }
    input.imbue(std::locale(std::locale(), new LetterType()));
    // @TODO: Move to a WordFreqApp(stream, entry) class
    istream_iterator<string> start(input);
    istream_iterator<string> end;
    // read stream and fill into a map[word]: count
    std::unordered_map<std::string, int> byWordMap = std::for_each(start, end, Counter());
    // for (auto& m : byWordMap) {
    //     cout << setw(7) << m.second << " " << m.first << endl;
    // }

    // transform to map[count]: word
    std::multiset<std::pair<int, string>> byCountMap = MapTransform::FlipMap(byWordMap);
    int n = 0;
    for (auto it = byCountMap.rbegin(); it != byCountMap.rend(); ++it) {
        cout << setw(7) << it->first << " " << it->second << endl;
        if (entryToDisplay == 0) continue;
        if (++n >= entryToDisplay) break;
    }
    return 0;
}
