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

#include <functional>

float product(float const n1, float const n2)
{
    return n1 * n2;
}

struct factor
{
    float n1 = 2;
    void num_by(float const n2) { n1 *= n2; }
};

int main(int argc, char* argv[])
{
    float n1 = 16.0, n2 = 20.0;
    auto call1 = std::invoke(product, n1, n2);

    auto call2 = std::invoke(&product, n1, n2);

    float(*p_product)(float const, float const) = &product;
    auto call3 = std::invoke(p_product, n1, n2);

    factor fac;
    auto call4 = std::invoke(std::multiplies<>(), std::invoke(&fac::n1), n2);

    auto l_product = [](auto n1, auto n2) { return a*b; };
    auto call5 = std::invoke(l_product, n1, n2);
    return 0;
}