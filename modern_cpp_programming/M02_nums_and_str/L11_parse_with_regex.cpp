// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You can parse content that match a regex case you propose, in this case, you
 * can use std::smatch, but you will also discover how to use std::regex_search
 * and std::sregex_iteration.
 * 
 * The regex we are going to use here is:
 * 
 *      ^(?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*)$
 * 
 * It is composed of:
 *  - ^ : Start of line
 *  - (?!#) : For making sure it is not possible to match # char.
 *  - (\w)+ : Capturing group of word with at least one char.
 *  - \s* : Any number of whitespace (can be also cero).
 *  - = : Equals sign.
 *  - ([\w\d]+[\w\d._,\-:]*) : Capturing group for a word (can contain symbols)
 *  - $ : End of line.
*/

#include <regex>
#include <string>



int main(int argc, char** argv)
{
    using namespace std::string_literals;

    // Example text that will be used for identify with regex.
    std::string lines[] = {"Roses are #ff0000",
                    "violets are #0000ff",
                    "all of my base are belong to you"};

    // Info #1: Do not forget on how to create a pattern for a regex:
    auto pattern {R"( #([a-f0-9]{2})\n ([a-f0-9]{2}) "([a-f0-9]{2})\n )"s};

    std::regex rgx = std::regex{ "#([a-f0-9]{2})"
                                  "([a-f0-9]{2})"
                                  "([a-f0-9]{2})" };

    // Info #2: Usage of regex_search for matching patterns, opr validating if
    // pattern is present.
    std::cout << "Searching for color pattern: " << std::endl
              << pattern << std::endl << std::endl
              << "Lines containts the pattern? " << std::endl;
    for (const auto& line : lines)
    {
        std::cout << line << ":= " << std::boolalpha 
                  << std::regex_search(line, rgx) << std::endl;
    }
    std::cout << std::endl << "Now displaying matches:\n" << std::endl;

    std::smatch color_match;
    for (const auto& line : lines)
    {
        if (std::regex_search(line, color_match, rgx))
        {
            std::cout << "matches for '" << line << "'\n";
            std::cout << "Prefix: '" << color_match.prefix() << "'\n";
            for (std::size_t i = 0; i < color_match.size(); ++i) 
                std::cout << i << ": " << color_match[i] << '\n';
            std::cout << "Suffix: '" << color_match.suffix() << "\'\n\n";
        }
    }

    // Info #2: Using iterator with regex for searching occasions.
    std::string lines_str = {"Roses are #ff0000 \n violets are #0000ff \n all of my base are belong to you"};

    auto match_begin = std::sregex_iterator(lines_str.begin(), lines_str.end(), rgx);
    auto match_end = std::sregex_iterator();

    for (std::sregex_iterator i = match_begin; i != match_end; ++i)
    {
        std::smatch patter_match = *i;
        std::string str_match = patter_match.str();
        std::cout << str_match << std::endl;
    }

    


    return 0;
}