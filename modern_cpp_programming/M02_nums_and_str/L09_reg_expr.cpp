// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>

/**
 * Regular expression allow for text management and search of different
 * patterns, for using it in C++, you will need the <regex> header.
 * 
 * If you want to learn about REGEX, you can check:
 *      https://regexr.com/
 * 
*/

#include <regex>
#include <string>

bool is_valid_email_format(std::string const & email);
using namespace std::string_literals;

int main(int argc, char** argv)
{

    // Info #1: Creating a simple regular expression.
    auto pattern {R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s};
    auto rx_simple = std::regex{pattern};
    auto rx_full = std::regex{pattern, std::regex_constants::icase};
    auto obj = "gmail@yourdomain.com";
    auto valid = std::regex_match(obj, rx_full);
    std::cout << "Pattern: " << pattern << std::endl
              << "Evaluation: " << obj << " is " <<  valid << std::endl;
    return 0;
}

bool is_valid_email_format(std::string const & email)
{
    auto eval {R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s};
    auto regex = std::regex{eval, std::regex_constants::icase};
    return std::regex_match(email, regex);
}
