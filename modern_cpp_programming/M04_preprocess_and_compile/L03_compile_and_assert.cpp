// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * It is possible to have assertion in compile-time and runtime. Then, you can
 * ensure the status of your code. But in the case of runtime, it can be
 * problmeatic if the assertion only occurs when the control flow reaches them.
 * In C++11 and later, you can have compile-time assertions with the
 * 'static_assert' command.
 * 
 * This assertions are usually used to with templates to validate preconditions
 * like if a type is copy-constructible, it is a reference type or the objects
 * have a specific size.
 * 
*/

// Info #1: You can use static assertion to check the size of a type, and
// ensure it accomplishes certain aspects.
struct passport_t
{
    int id;
    int code;
    bool major;
    char letter;
};

// Info #2: You can use static assertion to check if a class is a POD type,
// which comes from Plain Old Data, in other words, that it doesn't have any
// user_defined constructors. They only contain trivial default constructors,
// trivial copy constructors and trivial destructors. 
template <typename T>
class pod_checker
{
    static_assert(std::is_standard_layout_v<T>,
        "POD class type expected here!");
    T value;
};

int main(int argc, char** argv)
{
    // Using as size checker
    std::cout << "Passport type has two integers, one boolean and one char "
              << "then, the size should be 12, otherwise it will call assert. "
              << "\nEdit the size below in source code, to watch the assert."
              << std::endl; 
    static_assert(sizeof(passport_t) == 12, "Size of passport must be 12");
    
    // Using as POD checker
    std::cout << "";

    pod_checker<int> t1; 
    return 0;
}