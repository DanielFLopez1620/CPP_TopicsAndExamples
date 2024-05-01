// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * C++17 came with a feature to simplify codes when wanting to define function
 * overloads and variadic arguments. It is a constexpr if, which result in 
 * a condition that will be evaluated at compile time that allows to select
 * certain branches of a code. The structure is the next one:
 * 
 *      if constexpr (init-statement condition) <statement-true>
 *      else <statement-false>
 * 
 * NOTE: If you haven't asked about it... when we have std::point<T> it is 
 * referring to class templates defined in <type_trais> header, in this case if
 * it detects a pointer, it will provide the value (::value) meber, that is true
 * in case of pointer. On the other hand, std::is_pointer_v<T> refers to type
 * traits value constants, also defined in type traits, and they are more concise
 * in given the value.
*/

// Info #1: You can change the usage of std::enable_if and still be relying on
// the SFINAE with a if constexpr to impose restrictions on function templates
// for your code.

template <typename T>
auto get_value(T value)
{
    if constexpr (std::is_pointer_v<T>)
        return *value;
    else
        return value;
}


int main(int argc, char* argv[])
{
    return 0;
}