#ifndef LETTER_TYPE_H
#define LETTER_TYPE_H

#include <iostream>
#include <locale>
#include <vector>

//!
//! LetterType. Locale modifier to filter out non-letter/number chars
//!
struct LetterType : std::ctype<char> {
    LetterType()
        : std::ctype<char>(GetTable())
    {
    }

    static std::ctype_base::mask const* GetTable()
    {
        // Default all ascii as whitespace
        static std::vector<std::ctype_base::mask> rc(std::ctype<char>::table_size, std::ctype_base::space);

        // Mark these ascii as alphanum
        // '0' - '9' (48 - 57)
        // 'A' - 'Z' (65 - 90)
        // 'a' - 'z' (97 - 122)
        std::fill(&rc['0'], &rc['9' + 1], std::ctype_base::digit);
        std::fill(&rc['A'], &rc['Z' + 1], std::ctype_base::alpha | std::ctype_base::upper);
        std::fill(&rc['a'], &rc['z' + 1], std::ctype_base::alpha | std::ctype_base::lower);
        return &rc[0];
    }
};

#endif // LETTER_TYPE_H
