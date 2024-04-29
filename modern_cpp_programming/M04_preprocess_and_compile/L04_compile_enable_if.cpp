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
 * NOTE: For using std::enable_if, the header <type_traits> is required.
*/

#include <type_traits>

// Info #1: If you need to specify that the args meet a condition, you can
// use the enable_if. Here we implement again a POD Checker as an example.
template <typename T, 
          typename = typename 
          std::enable_if_t<std::is_standard_layout_v<T>, T>>
class pod_checker
{
    T value;
};



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

int main(int argc, char* argv [])
{
    pod_checker<int> t1;
    pod_checker<Non> t2;
    return 0;
}

