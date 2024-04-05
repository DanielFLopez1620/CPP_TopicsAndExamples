// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * As lambda are object functions, then recursion is possible. But it is quite
 * different. Keep in mind that it can be argued that a recursive lambda may
 * not have sense in most cases, but let's continue exploring about lambda.
 * 
 * To create a recursive lambda, you will need to:
 *  
 *  1. Define lambda in the proper scope.
 *  2. Assign std::function wrapper.
 *  3. Caputre std::function by reference so it allows recursion.
 * 
 * 
*/

#include <functional>

constexpr int fibonacci(int const n);
void inner_lamda_fib(int num);

int main(int argc, char* argv[])
{
    return 0;
}

constexpr int fibonacci(int const n)
{
    return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

void inner_lamda_fib(int num)
{
    std::function<int(int const>) lambda_fib = 
    [&lambda_fib](int const n)
    {
        return n <= 2 ? 1 : lambda_fib(n - 1) + lambda_fib(n - 2);
    }
    auto fnum = lambda_fib(num);
}