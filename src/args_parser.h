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
            tokens_.push_back(std::string(argv[i]));
    }
    const std::string& getOption(const std::string& option) const
    {
        std::vector<std::string>::const_iterator it;
        it = std::find(tokens_.begin(), tokens_.end(), option);
        if (it != tokens_.end() && ++it != tokens_.end()) { return *it; }
        static const std::string empty("");
        return empty;
    }
    bool optionExists(const std::string& option) const
    {
        return std::find(tokens_.begin(), tokens_.end(), option) != tokens_.end();
    }

private:
    std::vector<std::string> tokens_;
};

#endif // ARGS_PARSER_H