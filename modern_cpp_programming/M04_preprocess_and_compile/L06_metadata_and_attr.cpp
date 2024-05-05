// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested, oriented C++20.

#include <iostream>

/**
 * C++ is very deficient in the case of intrspection (for language extensions).
 * Then, the compilers have their own way to have extensions, but in C++11
 * the attributes were introduced, and they tell the compiler how to implement
 * certain extensions.
*/

// Info #1: If you want to make sure a return value isn't discarded, you can use
// [[nodiscard]] attribut. Or even, [[nodiscard(text)]] after C++20 when it comes
// to use a message for better understanding.

[[nodiscard]] int get_letter()
{
    return 'd';
}

int main(int argc, char* argv[])
{
    get_letter();
    return 0;
}