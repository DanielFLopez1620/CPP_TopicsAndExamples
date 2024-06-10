// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You can parse content that match a regex case you propose, in this case, you
 * can use std::smatch, but you will also discover how to use std::regex_search
 * and std::sregex_iteration.
 * 
 * Review of regex: 
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
 * 
 * In the code below, although we are going to use the regex:
 * 
 *   #([a-f0-9]{2})\n ([a-f0-9]{2}) "([a-f0-9]{2})\n : For hex color code
 *   <\s*A\s+[^>]*href\s*=\s*"([^"]*)" : For catching URLs
 * 
 * Down below, you will use:
 *  - regex_search: Determines if there is a match of a regex (and possibly
 *    some sub-matches).
 *  - regex_iterator: Access the individual matches of a regex.
 *  - regex_token_iterator: Access individual sub-mathces of every match
 *    within the underlying character sequence.
 * 
 * NOTE: For more info on regex check: https://en.cppreference.com/w/cpp/regex
 * 
 * You can run this code with:
 * 
 *      g++ -std=c++17 L11_parse_with_regex.cpp -o parse_regex.out
 *      ./parse_regex.out
 * 
*/

// ---------------------- REQUIRED HEADERS ------------------------------------
#include <regex>  // C++ Library to use regular expressions
#include <string> // To manage strings and char arrays.

// ----------------------- MAIN IMPLEMENTATION --------------------------------
int main(int argc, char** argv)
{
    std::cout << "Lesson 11: Parsing with regex..\n" << std::endl;

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
        // In this case, we only use search to use a flag if the pattern is
        // present.
        std::cout << line << ":= " << std::boolalpha 
                  << std::regex_search(line, rgx) << std::endl;
    }
    std::cout << std::endl << "Now displaying matches:\n" << std::endl;

    std::smatch color_match;
    for (const auto& line : lines)
    {
        // Now we are using the search, with a match, so we can consider
        // new matches.
        if (std::regex_search(line, color_match, rgx))
        {
            std::cout << "matches for '" << line << "'\n";
            std::cout << "Prefix: '" << color_match.prefix() << "'\n";
            for (std::size_t i = 0; i < color_match.size(); ++i) 
                std::cout << i << ": " << color_match[i] << '\n';
            std::cout << "Suffix: '" << color_match.suffix() << "\'\n\n";
        }
    }

    // Info #2: Using sregex iterator with regex for searching matches.
    std::string lines_str = {
        "\tRoses are #ff0000 \n\tViolets are #0000ff \n \
        All of my base are belong to you"
    };
    std::cout << "Searching for colors in poem: " << std::endl 
              << lines_str << std::endl;

    // Create an iteratorthat starts with the array, and search for mathces.
    auto match_begin = std::sregex_iterator(lines_str.begin(), 
        lines_str.end(), rgx);
    auto match_end = std::sregex_iterator();

    // Use the iterator with a loop to display the matches.
    for (std::sregex_iterator i = match_begin; i != match_end; ++i)
    {
        std::smatch patter_match = *i;
        std::string str_match = patter_match.str();
        std::cout <<"Match found: "<< str_match << std::endl;
    }

    // Info #3: Using sregex token iterator with regex for searching mathces.
    std::string html = "\t" R"(<p><a href="http://brave.com">brave</a> )"
        "\n\t" R"(< a HREF ="http://cppreference.com">cppreference</a>\n</p>)";
    
    std::cout << "Searching URLs in HTML Code: " << std::endl << html
              << std::endl << std::endl << "URLs found: " << std::endl;
    
    std::regex url_re(R"!!(<\s*A\s+[^>]*href\s*=\s*"([^"]*)")!!", 
        std::regex::icase);

    std::copy(std::sregex_token_iterator(html.begin(), html.end(), url_re, 1),
              std::sregex_token_iterator(),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
    
} // main