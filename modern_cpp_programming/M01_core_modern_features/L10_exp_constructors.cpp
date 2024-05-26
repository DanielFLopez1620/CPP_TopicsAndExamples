// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Before C++11, every constructor was considered a 'converting constructor'
 * because it made a implicit conversion from one type to another. Now, with
 * C++11 a constructor without the 'explicit' specifier is considered a 
 * converting constructor. In this lesson, you will learn about conversion and
 * the usage of explicit constructors. 
 * 
 * QUICK NOTE: You can use std::initializer list to consider the
 * initialization to resolve the args passed between a {}.
*/

// Info #1: You can use the keyword 'explicit' to create explicit constructors
// or explicit converting operators, you justt need to add them to the
// beginning of the definition. 
struct just_an_example
{
    explicit just_an_example(float const num) : num(num) {}
    explicit operator bool() const { return num > 0.0; }

private:
    float num;
};

// Info #2: When you use explicit conversion, you aim to prevent some
// convertions that can be problematic to your code or are invalid in some
// context, but how can you check them? Well, check the code below and the main
// implementation to check which constructor is called, down below is just an
// implementation of type of constructors, for now, not using
struct which_con
{
    which_con()
        { std::cout << "Void constructor..." << std::endl; }
    which_con(int const num)
        { std::cout << "Constructor wit one int..." << std::endl; }
    which_con(int const num1, double const num2)
        { std::cout << "Constructo with one int and one double" << std::endl; }
    operator bool() const { return false; }
};

// Info #3: If we implement some operations like an addition between the objects
// of 'which_con' that we have created we will have an error and this won't pass 
// boolean operotrs, as they tend to convert to boolan objects rather than make
// the operation. This can also happen when having an enumeration and trying to
// define a variable with a state without using the enumerator type. This are
// some reasons why we use the explicit, to prevent this errors and ensure no
// implicit conversion is attempted. It seems like minor change, but it can be
// useful to prevent bugs in runtime.
struct which_con_with_explicit
{
    explicit which_con_with_explicit()
        { std::cout << "Void constructor..." << std::endl; }
    explicit which_con_with_explicit(int const num)
        { std::cout << "Constructor wit one int..." << std::endl; }
    explicit which_con_with_explicit(int const num1, double const num2)
        { std::cout << "Constructo with one int and one double" << std::endl; }
    operator bool() const { return false; }
};

int main(int argc, char* argv[])
{
    // Let's create some objects and check constructors
    std::cout << "Which constructors objects examples: " << std::endl;
    which_con obj1;
    which_con obj2(2);
    which_con obj3{};
    which_con obj4 = {16, 6.2};
    which_con obj5 = 1620;
    std::cout << "Just testing a boolean with the structure: "
              << bool(obj4) << std::endl << std::endl;


    return 0;
}