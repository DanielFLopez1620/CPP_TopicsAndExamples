// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * There will be some times, when you need to use a undefined number of args
 * for your functions, like when printing. After C++11, it is possible to use
 * templates for using a variable num of arguments. To implement them, you have
 * to consider:
 * 
 * 1) Define an overlaod with a fix number of args to end compile-time
 *    recursion.
 * 2) Define a template parameter pack.
 * 3) Defime a function parameter pack. (Consider sizeof...)
 * 4) Expand the parameter pack to replace it with the actual arg.
*/

// Info #1: Implementing the steps to having variable arguments
template <typename T>
T factors(T value)
{
    return value;
}
template<typename T, typename... Ts>
T factors(T first, Ts... others)
{
    return first * factors(others...);
}

int main(int argc, char** argv)
{
    return 0;
}
