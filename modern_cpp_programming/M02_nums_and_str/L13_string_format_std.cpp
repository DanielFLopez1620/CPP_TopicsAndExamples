// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * In C++, you can use the inherited printf functions and it can be faster, but
 * streams library provides more safety and extensibility. Moreover, C++20
 * provides a new formatting library, which is called <format>.
*/

// #include <fmt/core.h>
#include <format>

int main(int argc, char** argv)
{
    // Info #1: Providing arguments in new format.
    auto text1 = std::format("My name is {} {} ", "Dan", 1620);
}



