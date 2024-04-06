// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// BASED TOO ON GEEKSFORGEEKS Website:
// https://www.geeksforgeeks.org/lambda-expression-in-c/
// Code wasn't tested, oriented with g++ in C++20

#include <iostream>

/**
 * Wait! There is more with lambdas, you can use them with templates. Remember
 * that lamndas are unmanned function objects that implement the call operator,
 * then it can be generic by using templates. Here we take advantage of auto as
 * a specifier of the params of the lambda.
 * 
 * NOTE: Here some command description in case you haven't use them before:
 * - std::count_if(first, last, condition);
 *   Returns the numbers of elements that satisfy the condition in the range
 *   of first and last.
 *
 * - std::accumulate(first, last, init);
 *   Computes the sum between init and the the elements provided in the range
 *    of first and last.
 * 
 * - std::decay_t<decltype(x);
 *   Used to deduce the type of the parameter x, decltype detects the type at
 *   compile time and decay_t, remove any qualifier (const, volatile...) to 
 *   leave the underlying type.
 * 
 * - std::forward<template>(args);
 *   Forwards lvalues as lvalue or rvalue depending on the template
 * 
 * Now, for C++20, there is the possibility of using template lambdas. And they
 * can be used to restrict the use of a generic lambda to only some types, make
 * sure that two or more arguments have the same type, retrieve the type of a
 * generic parameter (so it allows to use static methods or iterator) or
 * perform a perfect forwarding in a generic lambda.
 * 
 * You can try this code with:
 * 
 *      g++ -std=c++20 L04_gen_tem_lambdas.cpp -o gen_lambda.out
 *      ./gen_lambda.out
*/

#include <vector>     // Library for using vectors (sequence containers
                      // representing arrays that can change).

#include <algorithm>  // Collection of functions for range of elements.

#include <utility>    // Language support and general purpose library

#include <numeric>    // Common math functions and types

#include <string>     // Fro string and char array management

// Info #1: Creating a lambda that can only invoked with vector types.
std::vector<float> vec_ex {1.6, 2.0, 6.2, 2.6};
auto vector_lambda = []<typename T>(std::vector<T> const& vec)
{
    std::cout << "Size of vector is: " << std::size(vec) << std::endl;
};

// Info #2: When using lambdas, you can also use defaulted and delete
// members to prevent certain usage or specify user defined
// interactions.
struct generic_sum
{
    template<typename T1, typename T2>
    auto operator()(T1 const t1, T2 const t2) const { return t1 + t2; }
    generic_sum(const generic_sum&) = default;
    generic_sum(generic_sum&&) = default;
    generic_sum& operator=(const generic_sum&) = delete;
    ~generic_sum() = default;
};

int main(int argc, char** argv)
{
    // Info #3: Basic usage of lambda with int and text examples, but in this
    // case, using auto for a generic implementations.
    auto lambda_sum = [](auto const e1, auto const e2) { return e1 + e2; };

    auto my_nums = std::vector<int>{16, 17, 18, 19, 20};
    using namespace std::string_literals;
    auto my_texts = std::vector<std::string>{"Hi"s, " "s, "Dan"s, "!"s};

    auto sum = std::accumulate(std::begin(my_nums), std::end(my_nums), 0,
        lambda_sum);
    auto concatenate = std::accumulate(std::begin(my_texts), std::end(my_texts),
         ""s, lambda_sum);

    std::cout << "GENERIC LAMBDA\nFor the numeric vector: " << std::endl;
    for( auto num : my_nums) { std:: cout << num << ", "; }
    std::cout << std::endl << "The sum is: " << sum << std::endl;
    std::cout << "For the string vector: " << std::endl;
    for( auto str : my_texts) { std:: cout << str << ", "; }
    std::cout << std::endl << "Concatenation: " << concatenate << std::endl;

    // Info #4: Using a template for std::vectors lambdas with templates.
    std::cout << "TEMPLATE LAMBDA\nFor the numeric vector: " << std::endl;
    for( auto num : my_nums) { std:: cout << num << ", "; }
    vector_lambda(my_nums);
    //vector_lambda(1620); // Will fail because it is not vector.

    // Info #5: Using generic lambdas to create templates with two different
    // variables of the same type.
    auto displayer = []<typename T>(T x, T y)
    {
        std::cout << "Element 1: " << x << "\tElement 2: " << y << std::endl;
    };
    displayer(16, 20);
    displayer("Hi", "Dan");
    // displayer(10, "Dan"); // Will launch error


    // Info #6: There may be cases when you need to know the type of a 
    // parameter and then you can use the instances and the static methods,
    // then you can use type deducers and pointers.

    // Define a struct with a static member.
    struct str_member
    {
        static void disp() { std::cout << "Str member" << std::endl; }
    };

    auto type_detect = [](auto x)
    {
        // Determindate type of X and then use it with T
        using T = std::decay_t<decltype(x)>;

        // After identification, create type and call method disp.
        T other;
        T::disp();
    };

    // Call lambda
    type_detect(str_member{});

    // Info #7: Generic lambdas with templates also allow to work with multiple
    // data provided to the function argumetns
    template <typename ...T>
    void type_multi_detect(T&& ... args)
    { /* ... */}

    auto multi_args = [](auto&& ...args)
    {
        return type_multi_detect(std::forward<decltype(args)>(args)...);
        // Alternative:
        // reutrn type_multi_detect(std::forward<T>(args)...);
    };
    multi_args(1620, "Hi");

    return 0;
}