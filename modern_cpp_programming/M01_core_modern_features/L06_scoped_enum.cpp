// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Enumerations underlyne integral types by creating collections. And their
 * named values are called enumerators, and when you use only the keyword
 * 'enum' they are considered to be unscopred, while by adding 'enumc class'
 * or 'enu struct' the convert to scoped enumerations that were introduced
 * in C++11.
*/

// Info #1: Declaration of scoped enumerations
enum class Grade {First, Second, Third };

int main(int argc, char* argv[])
{
    return 0;
}