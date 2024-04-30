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
 * The structure of the assertion is:
 * 
 *      static_assert(<condition>, <message_in_case_of_true_condition>);
 * 
 * Do not forget to experiment with the different assertion present in the code.
 * You can compile and run the code with:
 * 
 *      g++ -std=c++17 L03_compile_and_assert.cpp -o assert.out
 *      assert.out
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
    static_assert(std::is_pod_v<T>,
        "POD class type expected here!");
    T value;
};


// Info #3: You can also check if hte arguments are of certain type, if not, you
// can launch an assertion. 
template <typename T>
auto divide(T const n1, T const n2)
{
    static_assert(std::is_integral_v<T>,
        "You can only use integral numbers in this division");
    return (double) n1 / n2;
}

/**
 * Small class that isn't a POD type, just to test with the pod_checker.
*/
class NonPOD {
public:
    NonPOD() {
        std::cout << "Non-POD constructor called" << std::endl;
    }

    ~NonPOD() {
        std::cout << "Non-POD destructor called" << std::endl;
    }

    void doSomething() {
        std::cout << "Doing something" << std::endl;
    }
};

int main(int argc, char** argv)
{
    // Using as size checker
    std::cout << "Size Checker: " << std::endl
              << "Passport type has two integers, one boolean and one char "
              << "then, the size should be 12, otherwise it will call assert. "
              << "\nEdit the size below in source code, to watch the assert."
              << std::endl << std::endl; 
    static_assert(sizeof(passport_t) == 12, "Size of passport must be 12");
    
    // Using as POD checker
    std::cout << "POD Checker: " << std::endl
              << "As you can see, the next classes are POD, but if you "
              << "uncomment the custom obj part, you can check the assertion"
              << std::endl << std::endl;
    pod_checker<int> t1; 
    pod_checker<float> t2;
    // pod_checker<NonPOD> t3;

    // Using argument checker
    std::cout << "Arg Checker: " << std::endl
              << "You can also use a checker of the arguments, so you ensure"
              << " about a proper type of them. The first definition is valid,"
              << " but if you uncomment the secound one, you will see the "
              << "assertion" << std::endl << std::endl;
    double coc = divide(16, 20);
    // double non = divide(1.5, 2.5);

    return 0;
}