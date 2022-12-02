// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>
#include <vector>

auto ex_func(auto a, auto b);

int main()
{
    // auto: Automatic type deduction
    // As Andrei Alexandrecu coined the term AAA (Almost Always Auto)

    // Form #1: auto <name> = <value>
    auto num = 16;
    auto flt = 3.1416;
    auto text = "C++20";

    // Form #2: auto <name> = <type-id> {<value>}
    auto letters = new char[10]{0};
    auto word = std::string {"Hi!"};
    auto nums = std::vector<float> {3.14, 2.71, 1.0};

    //Form #3: auto <name> = <lambda function>
    auto lower = [](char const word) {return tolower(word); };
    auto power = [](auto const a) {return a*a;};

    // REMEMBER:
    // Do not forget to initalize the variable when using auto
    // It is used to ensure the correct datatype for the operation
    // It promotes good OOP and mean less concern of the types
    // Auto does not work with moveable, const or valatile types
    // Do not try to use auto for multi-word types

    // Also, a lamba with autos is called "generic lambda"
    auto diff = [] (auto const a, auto const b){return a - b;};
    // It will be applied to if the operator- is allowed

    return 0;
}
// Form #4: For functions return types
auto ex_func(auto a, auto b)
{
    return a + b;
}