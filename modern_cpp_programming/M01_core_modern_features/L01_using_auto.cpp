// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * C++ has gone throug major transformations in the last decade, and everything
 * started with C++11, but has passed with C++14, C++17 and C++20. Here we are
 * going to focus on some of the core modern features, and we will start with
 * auto.
 * 
 * Auto is an automatic type deduction, and the focus will be Almost Always Auto
 * (AAA), as it has several benefits in the flow of the code. The usage is:
 * 
 *      auto <name> = <expression>
 * 
 * The expression is needed, otherwise the deduction wouldn't be possible.
 * 
 * NOTE: Keep in mind the next:
 * - Do not forget to initalize the variable when using auto
 * - It is used to ensure the correct datatype for the operation
 * - It promotes good OOP and mean less concern of the types
 * - Auto does not work with moveable, const or valatile types
 * - Do not try to use auto for multi-word types
 * - You cannot use const and volatile with auto, as they need a ref type.
 * - Combining auto with multi word types in the context isn't allowed.
 * 
 * You can even use auto in for loops. But in some cases you may need to give
 * more context, for example, when using maps.
 * 
 * You can run and compile this code with:
 * 
 *      g++ -std=c++20 L01_using_auto.cpp -o auto.out
 *      ./auto.out
*/

// -------------------------------- IMPORTS AND INCLUDES ----------------------

#include <vector> // For using dynamic arrays.

// ------------------------------- PROTOTYPES AND DEFINITIONS -----------------
// Check the info below.
auto ex_func(auto a, auto b);


// -------------------------------- MAIN IMPLEMENTATION -----------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 1: Using auto...\n" << std::endl;

    // Info #1: You can use auto with the types you are familiar with:
    auto num = 16;
    auto flt = 3.1416;
    auto text = "C++20";
    std::cout << "Using auto with common types: " << std::endl
              << "\tInteger: " << num << std::endl
              << "\tFloating: " << flt << std::endl
              << "\tString: " << text << std::endl << std::endl;

    // Info #2: The type deduction can go further if you want, you can use 
    // 'auto <name> = <type-id> {<value>}' to declare local variabels and 
    // commit specific types:
    auto letters = new char[3]{'a', 'b', 'c'};
    auto word = std::string {"Hi!"};
    auto nums = std::vector<float> {3.14, 2.71, 1.0};
    std::cout << "Using auto with more types: " << std::endl
              << "\tChar array: ";
    for(int i = 0; i < 3; ++i)
    {
        std::cout << letters[i] << " ";
    }
    std::cout << std::endl << "\tString: " << word << std::endl
              << "\tInteger vector: ";
    for(float num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl << std::endl;

    // Note: If you have never seen a for-each, in C++, continue exploring the
    // lessons of this module.
            

    //Info #3: You can even create lambda functions, by using: 
    // 'auto <name> = <lambda function>'. If you do not know about lambdas,
    // they are covered in the Module 03, but I encourage you to explore the 
    // modules in order.
    auto lower = [](char const letter) {return tolower(letter); };
    auto power = [](auto const a) {return a*a;};
    auto my_letter = 'D';
    auto my_num = 1620;
    std::cout << "Lambdas and auto:" << std::endl << "\tChar: " << my_letter
              << std::endl << "\tLambda to lower: " << lower(my_letter) 
              << std::endl << "\tNum: " << my_num << std::endl << "\tSquared:"
              << power(my_num) << std::endl;

    

    // Also, a lamba with autos is called "generic lambda"
    auto diff = [] (auto const a, auto const b){return a - b;};
    // It will be applied to if the operator- is allowed

    // NOTE: If a conversion is not allowed, for example, with int to int &.
    // You can use decltype(auto) in those cases. As 'decltype' is used to
    // inspect the declared type of an entity, for example, with labmdas or
    // template parameters.

    return 0;

} // main

// --------------------------------- FUNCTION DEFINITIONS ---------------------

/**
 * Info #4: You can also use auto to specify the return of a function. Keep
 * in mind that in C++11 you may need to provide an inferred type (check
 * the comment below), but after C++14 it isn't necesary.
 * 
 * Simple sum function with two auto arguments.
 * 
 * @param a Number 1
 * @param b Number 2
 * 
 * @return Sum of the nums.
*/
auto ex_func(auto a, auto b)  // -> int
{
    return a + b;
}