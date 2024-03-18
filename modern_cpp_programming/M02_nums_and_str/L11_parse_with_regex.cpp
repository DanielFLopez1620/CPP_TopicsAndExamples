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
    auto info
    {
        R"(
timeout=100
server = 127.0.0.0
port=11111
        )"s
    };

    // Info #1: Do not forget on how to create a pattern for a regex:
    auto pattern {R"(^(?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*)$)"s};
    auto rgx = std::regex{R"(^(\w+)\s*=\s*([\w\d.]+)$)"};

    // Info #2: For searching occurrences (well, the first one), you can use:
    
    auto match = std::smatch{};
    if (std::regex_search(info, match, rgx)) 
    {
        std::cout << "Searching for first occurrence: " << std::endl
                << match[1] << " = " << match[2] << std::endl << std::endl;
    }

    // Info #3: You can also use iterators with the matches for the regex
    // and check for the occurences.
    std::cout << "Checking iterations: " << std::endl;
    auto end = std::sregex_iterator{};
    for (auto it = std::sregex_iterator{
        std::begin(info), std::end(info), rgx}; it != end; ++it)
    {
        std::cout << '\'' << (*it)[1] << "'='"
                  << (*it)[2] << '\'' << std::endl;
    }

    // Info #4: You can also iterate in the subexpressiones, by considering
    // tokens:
    std::cout << "Checking iterations with tokens: " << std::endl;
    auto end_tok = std::sregex_token_iterator{};
    for (auto it = std::sregex_token_iterator{
        std::begin(info), std::end(info), rgx }; it != end_tok; ++it)
    {
        std::cout << "\t" << *it << std::endl;
    }


    return 0;
}