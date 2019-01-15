#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <algorithm>
#include <string>
#include <vector>

//!
//! ArgsParser
//! Convert the argv into tokens for easier parsing. Does not handle complex args.
//! A more sophisticated alternative is boost program options
//! (Not used as requirement is not to depend on more than build-essential)
//!
class ArgsParser {
public:
    ArgsParser(int argc, char** argv)
    {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    const std::string& getOption(const std::string& option) const
    {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) { return *itr; }
        static const std::string empty("");
        return empty;
    }
    bool optionExists(const std::string& option) const
    {
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }

private:
    std::vector<std::string> tokens;
};

#endif // ARGS_PARSER_H