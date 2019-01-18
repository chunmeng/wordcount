#include "args_parser.h"
#include "letter_type.h"
#include "word_freq_app.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

static const int DefaultNumToDisplay = 20;

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
    input.open(filename.c_str());
    if (!input.good()) {
        cout << "Error: Oops! Input file \"" << filename << "\" couldn't be opened." << endl;
        return 0;
    }
    input.imbue(std::locale(std::locale(), new LetterType()));
    WordFreqApp app;
    app.process(input);
    app.print(entryToDisplay);
    return 0;
}
