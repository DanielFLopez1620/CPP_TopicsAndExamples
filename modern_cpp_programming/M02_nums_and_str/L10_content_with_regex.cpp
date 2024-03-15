// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Regex can be more than a search pattern, it can be used as a text
 * replacement tool. This is supported after C++11, and you need the 
 * implementations learned in the previous lesson.
 * 
 * You have checked what to do with a std::regex, so now check bellow how to
 * use std::regex_replace in single cases or cases where you have more than one
 * match. The purpose is oriented to describing a certain combintations of
 * digits, reorganizing a name provided or even changing the date format.
 * 
 * You can run this code with:
 * 
 *      g++ -std=c++17 L10_content_with_regex.cpp -o rep_reg.out
 *      ./rep_reg.out
*/

#include <regex>
#include <string>

using namespace std::string_literals;

int main(int argc, char** argv)
{
    // Info #1: Replacing an exact math.
    // The regex used:
    // \b : Word boundary anchor, and for matching a whole word.
    // [1 | 2 | 3] is oriented to match this three digits in some order.
    std::string draft = "123 11 321 2222 123 23111";
    std::string pattern1 = R"(\b[1|2|3]{3}\b)";
    std::regex regex1(pattern1);
    std::string change1 = "***";
    std::string applied1 = std::regex_replace(draft, regex1, change1);

    std::cout << "Original: " << draft << std::endl
              << "Pattern: "  << pattern1 << std::endl
              << "Change to: " << change1 << std::endl
              << "Result: " << applied1 << std::endl << std::endl;

    // Info #2: Considering num of mathces, and organizing them
    // The regex used:
    // \w+ : This is a capturing group that mathces one or more words.
    // \w : Menas any word character
    // + : Means one or more ocurrences
    // , : To indicate the separation of two groups.
    // \s* : Matches zero or more whitespaces
    std::string full_name = "Doe, John";
    std::string pattern2 = R"((\w+),\s*(\w+))";
    std::regex regex2(pattern2);
    std::string change2 = "$2 $1";
    std::string applied2 = std::regex_replace(full_name, regex2, change2);

    std::cout << "Original: " << full_name << std::endl
              << "Pattern: "  << pattern2 << std::endl
              << "Change to: " << change2 << std::endl
              << "Result: " << applied2 << std::endl << std::endl;

    // Info #3: Using dates formats with regex.
    // The regex here is oriented to:
    // \d{1,2} : Capturing group that matches one or two digits.
    // \d : Represents any digit
    // \{1,2} : Represents one or two ocurrences.
    // (\.|-|/) : For select a dot (.), a hyphen(-) or a slash (/).
    // \d{4} : Capturing group of four digits.
    std::string date = "Today is 15.03.2023";
    std::string pattern3 = R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))";
    std::regex regex3(pattern3);
    std::string change3 = R"($5$4$3$2$1)";
    std::string applied3 = std::regex_replace(date, regex3, change3);

    std::cout << "Original: " << date << std::endl
              << "Pattern: "  << pattern3 << std::endl
              << "Change to: " << change3 << std::endl
              << "Result: " << applied3 << std::endl;

    return 0;
}