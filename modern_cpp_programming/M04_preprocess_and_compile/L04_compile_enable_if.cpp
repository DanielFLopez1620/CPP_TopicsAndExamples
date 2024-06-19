// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Templates allow to implement generic classes, this can lead to not having
 * a principle or mechanism for applying constraints in certain cases, but with
 * metaprogramming trick we can use the SFINAE (Substitution Fauilue Is Not An
 * Error) which is used to tell the compiler to discard a certain overload when
 * it fails, then producing a message error.
 * 
 * For the previous purpose, programmers have used 'enable_if', which has a 
 * family implementation in C++11 (and later versions).
 * 
 * The implementation of enable_if, can be understood as:
 * 
 *      template <bool Test, class T = void>
 *      struct enable_if
 *      {};
 *      template<class T>
 *      struct enable_if<true, T>
 *      {
 *          typedef T type;
 *      }; 
 * 
 * Why this works? Well... the compiler needs to build a set of possible
 * overloads when encountering a function call, and in case of templates
 * it needs to performa substituion for the specified or deduced types. But
 * when using SFINAE, a fails in the construction doesn't call an error, it 
 * just remove the certain function overload and continues.
 * 
 * In this code, you can check examples similar to the previous lesson, the
 * difference is that static_assert doesn't rely on SFINAE, then the result
 * is a failed assert at compile time, while std::enable_if doesn't trigger
 * compiler errores. Then you can use std::enable_if to more precise 
 * constructions of functions, because if a type or condition is not allowed
 * it will just do not write the overload, then preventing ambiguous call
 * of overloaded functions.
 * 
 * NOTE: For using std::enable_if, the header <type_traits> is required.
 * 
 * You can use this code with:
 * 
 *      g++ -std=c++17 L04_compile_enable_if.cpp -o enable.out
 *      ./enable.out
*/

// ------------------------ REQUIRED HEADERS ----------------------------------
#include <type_traits> // For type management and related utilties

// ---------------------- STRUCT AND CLASS DEFINITIONS ------------------------
// Info #1: If you need to specify that the args meet a condition, you can
// use the enable_if. Here we implement again a POD Checker as an example.
template <typename T, 
          typename = std::enable_if_t<std::is_pod_v<T>>>
class pod_checker
{
    T value;
};

// Info #2: You can also create an implementation that just works with certain
// types, by considering a template with enable_if.
/**
 * Simple divide function that check for integer args, but ends with a floating
 * result.
 * 
 * @param n1 First integer number
 * @parma n2 Second integer number
 * 
 * @return Result of the division with decimal precision
 */
template<typename T,
         typename = typename std::enable_if_t<
             std::is_integral_v<T>, T>>
auto divide(T const n1, T const n2)
{
    return n1 / n2;
} // divide

// Info #3: You can create an alias (or two) two prevent repetitive code while
// using enable_if. 
template <typename Test, typename T = void>
using EnableIf = std::enable_if_t<Test::value, T>;
template <typename Test, typename T = void>
using DisableIf = std::enable_if_t<!Test::value, T>;

// Info #4: You can use the previous alias, whenever you want to create a
// enable_if condition, just remeber to consider the proper cases when you
// make the implementation.For example, with the pod checker
template <typename T, typename = EnableIf<std::is_pod<T>>>
class pod_checker_aliased
{
    T value;

}; // class pod_checker_aliased

/**
 * Small class that isn't a POD type, just to test with the pod_checker.
*/
class NonPOD {
public:
    /**
     * Simple construct that logs its call.
     */
    NonPOD() 
    {
        std::cout << "Non-POD constructor called" << std::endl;

    } // NonPOD

    /**
     * Simple destructor that logs its calls
     */
    ~NonPOD() 
    {
        std::cout << "Non-POD destructor called" << std::endl;

    } // ~NonPOD

    /**
     * Function that just print something, just something.
     */
    void doSomething() 
    {
        std::cout << "Doing something" << std::endl;

    } // Do something

}; // class NonPOD

// --------------------------- MAIN IMPLEMENTATION ----------------------------
int main(int argc, char* argv [])
{
    std::cout << "Lesson 04: Enables in compilation time...\n" << std::endl;
    // Info #5: Using enable if to check pod types.
    std::cout << "POD Checker: " << std::endl
              << "Similar to the code in the previous lesson, you can check"
              << " that string and our class implementations aren't POD types"
              << " , if you uncomment the next lines, it will alert you"
              << std::endl << std::endl;
    pod_checker<int> t1;
    pod_checker_aliased<int> tl1;
    // pod_checker<NonPOD> t2;
    // pod_checker_aliased<NonPOD> t2;
    // pod_checker<std::string> t3;

    // Info #6: Using enable if to check type of arguments
    std::cout << "Arg Checker: " << std::endl
              << "You can use enable if to check the type of the parameters"
              << "too, then you can implement certain types. If you check the"
              << "code you will discover that only the integer implementation"
              << "works, then try uncomment the other to see the chaos."
              << std::endl << std::endl;

    auto n1 = divide(16, 20);
    // auto n2 = divide(1.6, 2.0);

    return 0;

} // main

