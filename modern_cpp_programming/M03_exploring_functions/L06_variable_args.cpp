// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested, oriented with g++ in C++20

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

#include <vector>

// Info #1: Implementing the steps to having variable arguments, you may notice
// it seems like a recursion, but to be mroe precise it is a compile time
// recursion rather than a runtime recursion. This makes the compiler generate
// multiple functions with a different nums of arguments. Also keep in mind:
// - typename... Ts : Is a template parameter packt.
// - typename... others : Is a function parameter pack for function with variable
//   number of arguments.
// - others... : Is a expansion of the parameter packt
template <typename T>
T factors(T value)
{
    return value;
}
template<typename T, typename... Ts>
T factors(T first, Ts... others)
{
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    return first * factors(others...);
}

// Info #2: Not every variable args implementation need a sort of recursion, it
// can be used also made by knowing the total size of the args.
template<typename... T>
auto make_odd_vector(T... nums)
{
    static_assert(sizeof...(nums)%2 != 0, "Error: expected odd number");
    std::vector<T...> vect {nums... };
    return vect;
}

int main(int argc, char** argv)
{
    // Info #3: Using variable args from multiple types.
    auto product1 = factors(16, 20, 30);
    auto product2 = factors(1.6, 2.0, 3.0, 5.2);

    std::cout << "Multiplication 1: " << product1 << std::endl
              << "Multiplication 2: " << product2 << std::endl << std::endl;
    return 0;

    // Info #4: Using odd vector implementation
    auto num1 = 1, num2 = 7, num3 = 5;
    std::cout << "My odd vector is: " << num1 << " " << num2 << " "
              << num3 << std::endl;
    auto vector1 = make_odd_vector(num1, num2, num3);
}
