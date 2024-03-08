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
 * NOTE: The s suffix will refer to string literal, but it will depend
 * on the compiler and your code.
*/

int main(int argc, char** argv)
{
    // Info #1: Printing paths (of windows) with literals.
    auto path1 { R"(C:\Users\dan\Documents\)" };
    auto path2 { R"(C:\\Users\\dan\\Downloads\\)"};

    std::cout << "Path 1: " << path1 << std::endl
              << "Path 2: " << path2 << std::endl;
    return 0;
}