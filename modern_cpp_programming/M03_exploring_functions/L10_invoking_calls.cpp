// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested  with g++ in C++17

#include <iostream>

/**
 * There will be times when you need a uniform way to call all your 
 * implementations, in C++ this can be achieved with std::bind, std::function,
 * std::mem_fn and std::thread::thread. But with C++17, you have another option
 * and it is std::invoke that can be used to invoke any callable object, it
 * isn't a replacement of the calls but rather a useful template. Down below 
 * you can check examples implementations.
 * 
 * Another terms related with this topic are:
 * 
 * - std::is_invocable()
 * - std::is_nothrow_invocable()
 * - std::is_invocable_r():
 * - std::is_nothrow_invocabel_rs()
 * 
 * That are used to check if using std::invoke is valid as it is well formed
 * when threated as a unevaluated operand, so they can be used for test or
 * checks with static assert. You can check more info on:
 * 
 *  https://en.cppreference.com/w/cpp/types/is_invocable
 * 
 * NOTE: You can use 'auto' to simplify things, but in some cases you will need
 * to provide the type of pointers or objects in order to prevent errors or
 * warnings.
*/

// -------------------------- REQUIRED HEADERS --------------------------------
#include <functional> // For using function objects and the standard hash func.

// ------------------------- FUNCTION DEFINITIONS -----------------------------

/**
 * Simple function to calculate the product of two nums
 * 
 * @param n1 First floating factor
 * @param n2 Second floating factor
 * 
 * @return Product of the given nubers
*/
float product(float const n1, float const n2)
{
    return n1 * n2;

} // product

// ----------------------- STRUCT AND CLASSES DEFINTIONS ----------------------

/**
 * Structure that initialize a value, and has a method to calculate a product.
*/
struct factor
{
    float n1 = 16;
    void num_by(float const n2) { n1 *= n2; }

}; // struct factor

int main(int argc, char* argv[])
{
    std::cout << "Lesson 10: Invoking and calls of functions...\n" << std::endl;

    // Info #1: Using invoke with a function and providing the args.
    float n1 = 16.0, n2 = 20.0;
    auto call1 = std::invoke(product, n1, n2);
    std::cout << "Using nums: ( " << n1 << ", " << n2 << ")..." << std::endl
              << "Call 1: Product function: " << call1 << std::endl;

    // Info #2: Using a pointer to access a function and provide the args.
    auto call2 = std::invoke(&product, n1, n2);
    std::cout << "Call 2: Pointer to function: " << call2 << std::endl; 

    // Info #3: Creating a pointer to the proper function, then provide the
    // args.
    float(*p_product)(float const, float const) = &product;
    auto call3 = std::invoke(p_product, n1, n2);
    std::cout << "Call 3: Double pointer: " << call3 << std::endl;

    // Info #4: Accesing a struct and using its attributes and methods with
    // invoke.
    factor fac;
    auto call4 = std::invoke(std::multiplies<>(), std::invoke(&factor::n1, fac), n2);
    std::cout << "Call 4: Struct and attribute: " << call4 << std::endl; 

    // Info #5: Using invoke for names lambdas.
    auto l_product = [](auto n1, auto n2) { return n1*n2; };
    auto call5 = std::invoke(l_product, n1, n2);
    std::cout << "Call 5: Lambda function: " << call5 << std::endl;

    return 0;
}