// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested, oriented with g++ in C++20

#include <iostream>

/**
 * Fold expressions appeared in C++17, they allo to reduce a parameter pack over
 * binary operators, then it simplifies variadic templates to make them more
 * concise and readble.
 * 
 * The fold operations are defined inside parenthesis and have a parapmeter pack,
 * one or two operators, and a ellipsis (...). Some examples of the syntax are:
 * 
 *  - Unary Right Fold: (<pack> <operator> ....)
 *  - Unary Left Fold: (... <operator> <pack>)
 *  - Binary Right Fold: (<pack> <operator> ... <operator> <init>)
 *  - Binary Left Fold: (<init> <operaator> ... <operator> <pack>)
*/


// Info #1: 
template <typename T>
T products(T value)
{
    return value;
}
template <typename T, typename... Ts>
T products(T begin, Ts... others)
{
    return begin * products(others...);
}

// Info #2:
// Unary left folding:
template <typename... Ts>
auto products(Ts... args)
{
    return (... * args);
}
// Binary left folding:
template <typename... Ts>
auto duplicate_product(Ts... args)
{
    return (2 * ... * args);
}
// Unary right folding:
template <typename... Ts>
auto products(Ts... args)
{
    return (args + ...);
}
// Binary right folding:
template <typename... Ts>
auto duplicate_product(Ts... args)
{
    return (args * ... * 2);
}


int main(int argc, char** argv)
{
    auto product1 = products(16, 20, 30);
    auto product2 = products(1.6, 2.0, 3.0, 5.2);
    auto product3 = duplicate_product(16, 20, 30);
    auto product4 = duplicate_product(1.6, 2.0, 3.0, 5.2);


    std::cout << "Products #1: " << product1 << std::endl
              << "Products #2: " << product2 << std::endl
              << "Duplicate products #1: " << product3 << std::endl
              << "Duplicate products #2: " << product4 << std::endl
              << std::endl;

    return 0;
}