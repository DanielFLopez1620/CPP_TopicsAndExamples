// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>

/**
 * If you have used strings, you should now that there are non-printable chars
 * and delimiters, they usually start with a backslash '\' or are included by
 * pairs with '' and "".
 * 
 * But if you need to print this characters, you can use raw literals.
 * This literals can have the form of: 
 * 
 * - R"( literal)s" -> The most basic one that can be used with files, patterns
 *   and commands for other programs or usages. 
 * 
 * - R"delimiter ( literal )delimiter" -> Where the delimter can't be a
 *   parentheses, backslash or space, and the literal cannot have a closing
 *   sequence.
 * 
 * You can execute this code with:
 * 
 *      g++ -std=c++14 L07_raw_lit_and_esc_char.cpp -o esc_char.out
 *      ./esc_char.out
 * 
 * NOTE: The s suffix will refer to string literal, but it will depend
 * on the compiler and your code.
*/

int main(int argc, char** argv)
{
    // Info #1: Printing paths (of windows) with literals.
    auto path1 { R"(C:\Users\dan\Documents\)" };
    auto path2 { R"(C:\\Users\\dan\\Downloads\\)"};

    std::cout << "Using paths:" << std::endl << "Path 1: " << path1 
              << std::endl<< "Path 2: " << path2 << std::endl << std::endl;

    // Info #2: Usage of delimiters.
    auto text{ R"!!(Containing quotations "( and parenthesis )".)!!" };
    std::cout << "Using quotations: " << text << std::endl << std::endl;

    // Info #3: Other raw string literals: That are related with the different
    // types of string we have mananged during this module.
    auto msg1 { LR"(const wchart_t*)" };
    auto msg2 { u8R"(const char _t*)" };
    auto msg3 { uR"(const char16_t*)" };
    auto msg4 { UR"(const char32_t*)" };
    auto msg5 { LR"(wstring)" };
    auto msg6 { u8R"(string)" };
    auto msg7 { UR"(u16string)" };
    
    std::cout << "MS1: " << msg1 << std::endl
              << "MS2: " << msg2 << std::endl
              << "MS3: " << msg3 << std::endl
              << "MS4: " << msg4 << std::endl
              << "MS5: " << msg5 << std::endl
              << "MS6: " << msg6 << std::endl
              << "MS7: " << msg7 << std::endl;
              
    return 0;
}