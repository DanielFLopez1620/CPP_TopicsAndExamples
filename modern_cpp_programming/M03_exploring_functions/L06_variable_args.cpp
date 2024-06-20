// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with C++ 20 using G++

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
 * 
 * NOTE: When implementing ellipsion (...) the order doesn't matter when using
 * the template and the proper name.
 * 
 * You may discover that the implementation of the variable args aims to trick
 * the compiler, if you want to watch the signature of a function you can use:
 * 
 *      std::cout << __PRETTY__FUNCTION___ << std::endl; // Beginning the func
 * 
 * You can try this code with:
 * 
 *      g++ -std=c++20 L06_variable_args.cpp -o var_args.out
 *      ./var_args.out
*/

// ---------------------- REQUIRED HEADERS ------------------------------------
#include <vector>         // For using different types of dynamic arrays.
#include <type_traits>    // For given policy and implementation details.

// -------------------- STRUCT AND CLASS DEFINITIONS --------------------------

// Info #1: Implementing the steps to having variable arguments, you may notice
// it seems like a recursion, but to be more precise it is a compile time
// recursion rather than a runtime recursion. This makes the compiler generate
// multiple functions with a different nums of arguments. Also keep in mind:
// - typename... Ts : Is a template parameter packt.
// - typename... others : Is a function parameter pack for function with variable
//   number of arguments.
// - others... : Is a expansion of the parameter packt

/**
 * Generic implementation for a multiplication with just one value, in other 
 * words, multiplication of the given number by one.
 * 
 * @param value Number to consider in the multiplication
 * 
 * @return Product of the value by 1
 */
template <typename T>
T factors(T value)
{
    return value;

} // factors

/**
 * Generic implementation of a multiplication that considers a pack of 
 * arguments for a consecutive multiplication. By having as a root the
 * default 1 product defined previously.
 * 
 * @param first First factor to consider
 * @param others Pack of arguments for the multiplication
 * 
 * @return Consecutive product of the args passed.
 */
template<typename T, typename... Ts>
T factors(T first, Ts... others)
{
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    return first * factors(others...);

} // factors

// Info #2: Not every variable args implementation need a sort of recursion, it
// can be used also made by knowing the total size of the args.
/**
 * Function with variadic arguments implementation for generating a vector with
 * just odd numbers.
 * 
 * @param nums Pack of numbers to consider
 * 
 * @return Vector formed with the pack of numbers passed.
 * 
 * @exception Static assert if one of the provided args isnt' an odd number.
 */
template<typename... T>
auto make_odd_vector(T... nums)
{
    static_assert(sizeof...(nums)%2 != 0, "Error: expected odd number");
    using common_type = std::common_type_t<T...>;
    std::vector<common_type> vect {nums...};
    return vect;

} // make_odd_vector

// ---------------------------- MAIN IMPLEMENTATION ---------------------------

int main(int argc, char** argv)
{
    std::cout << "Lesson 6: Understaing variadic arguments for funcs...\n"
              << std::endl;

    // Info #3: Using variable args from multiple types.
    auto product1 = factors(16, 20, 30);
    auto product2 = factors(1.6, 2.0, 3.0, 5.2);

    std::cout << "Multiplication 1 (16, 20, 30): " << product1 << std::endl
              << "Multiplication 2 (1.6, 2.0, 3.0, 5.2): " << product2 
              << std::endl << std::endl;

    // Info #4: Using odd vector implementation
    auto num1 = 1, num2 = 7, num3 = 5;
    std::cout << "My odd vector is: " << num1 << " " << num2 << " "
              << num3 << std::endl;
    auto vector1 = make_odd_vector(num1, num2, num3);
    
    return 0;

} // main
