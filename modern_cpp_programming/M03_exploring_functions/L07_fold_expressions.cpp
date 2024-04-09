// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested  with g++ in C++17

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
 * 
 * In this cases there are a set of operators supported:
 * 
 * - Binary: +, -, *, /, %, ^, &, |, =, >>, +=, -=, *=, /=, %=, ^=, &=, |=, !=,
 *   <=, >=, &&, || , .*, >*.
 * - Unary: +(0), *(1), &(-1), | (0), &&(true), ||(false), ,(void())
 * 
 * When you are ready, you can compile the code with:
 * 
 *      g++ -std=c++17 L07_fold_expressions.cpp -o fold.out
 *      ./fold.out
 * 
*/

// Info #1: As you may remember, the correct form for implementing variable
// nums of args, is by using templates with a pack:
template <typename T>
T products1(T value)
{
    return value;
}
template <typename T, typename... Ts>
T products1(T begin, Ts... others)
{
    return begin * products1(others...);
}

// Info #2: Let's use examples of folding expressions as they where previously
// mentioned and classified:

//  - Unary left folding:
template <typename... Ts>
auto products2(Ts... args)
{
    return (... * args);
}

//  - Binary left folding:
template <typename... Ts>
auto duplicate_product1(Ts... args)
{
    return (2 * ... * args);
}

//  - Unary right folding:
template <typename... Ts>
auto products3(Ts... args)
{
    return (args + ...);
}

//  - Binary right folding:
template <typename... Ts>
auto duplicate_product2(Ts... args)
{
    return (args * ... * 2);
}

// Info #3: Even though fold expressions work with overloads of supported
// binary operators, it doesn't work with arbitrary binary functions. For
// example, implementing a wrapper that holds a reference to a constant value,
// it can also be used then for implementing a max value by considering the 
// operator>
template <typename T>
struct wrapper
{
    T const & value; 
};

template <typename T>
constexpr auto operator>(wrapper<T>  const lhs, wrapper<T> const & rhs)
{
    return wrapper<T> {lhs.value > rhs.value ? lhs.value : rhs.value};
}

template <typename... Ts>
constexpr auto max(Ts&&... args)
{
    return(wrapper<Ts>{args} > ...).value;
}


int main(int argc, char** argv)
{
    // Info #4: Implementing folds products
    auto product1 = products1(16, 20, 30);
    auto product2 = products2(1.6, 2.0, 3.0, 5.2);
    auto product3 = duplicate_product1(16, 20, 30);
    auto product4 = duplicate_product2(1.6, 2.0, 3.0, 5.2);

    std::cout << "Products #1: " << product1 << std::endl
              << "Products #2: " << product2 << std::endl
              << "Duplicate products #1: " << product3 << std::endl
              << "Duplicate products #2: " << product4 << std::endl
              << std::endl;

    // Info #5: Implementing max of the values passed with fold expressions.
    auto searching_max = max(16, 20, 15);
    std::cout << "The minimum value between 16, 20, 15 is: " << searching_max
              << std::endl;

    return 0;
}