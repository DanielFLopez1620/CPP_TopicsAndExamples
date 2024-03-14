// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>

/**
 * Regex can be more than a search pattern, it can be used as a text
 * replacement tool. This is supported after C++11, and you need the 
 * implementations learned in the previous lesson.
 * 
 * 
*/

#include <regex>
#include <string>

using namespace std::string_literals;

int main(int argc, char** argv)
{
    // Info #1: Replacing an exact math.
    std::string draft = "123 11 321 2222 123";
    std::string pattern1 = R"(\b[1|2|3]{3}\b)";
    std::regex regex1(pattern1);
    std::string change1 = "***";
    std::string applied1 = std::regex_replace(draft, regex1, change1);

    std::cout << "Original: " << draft << std::endl
              << "Pattern: "  << pattern1 << std::endl
              << "Change to: " << change1 << std::endl
              << "Result: " << applied1 << std::endl << std::endl;

    // Info #2: Considering num of mathces.
    std::string full_name = "Doe, Joh";
    std::string pattern2 = R"((\w+),\s*(\w+))";
    std::regex regex2(pattern2);
    std::string change2 = "$2 $1";
    std::string applied2 = std::regex_replace(full_name, regex2, change2);

    std::cout << "Original: " << draft << std::endl
              << "Pattern: "  << pattern1 << std::endl
              << "Change to: " << change1 << std::endl
              << "Result: " << applied1 << std::endl;

    return 0;
}