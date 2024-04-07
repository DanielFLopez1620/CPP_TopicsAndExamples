// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested, oriented with g++ in C++20

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
 * It is possible as lamdas functions aer callable objects and it is allowed
 * to call them from inside the function the lambda (by including itself) in
 * the capture. Then, it must have a name, it can only be defined in a
 * function scope, itmust not be from a unspecified type and the capture must
 * be by reference.
 * 
 *  You can try this code with:
 * 
 *      g++ -std=c++20 L05_recursive_lambda.cpp -o rec_lambda.out
 *      ./rec_lambda.out
*/

#include <functional>  // For std::function and related usage of functions

// Prototype for recursive func implementation
constexpr int fibonacci(int const n);

// Prototype for recursive lambda implementation
void inner_lamda_fib(int num);

int main(int argc, char* argv[])
{
    std::cout << "Let's test fibonacci with lambda for 10:";
    inner_lamda_fib(10);
    return 0;
}

/**
 * Recursive function to implement fibonacci.
 * 
 * @param n Number of iterations to consider while calculating.
 * 
 * @return Fibonacci result of the iteration given.
*/
constexpr int fibonacci(int const n)
{
    return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

/**
 * Function that uses a inner recursive lambda to calculate fibonacci.
 * It will display the value of the calculation
 * 
 * @param num Number of iterations to consider the fibonacci series.
*/
void inner_lamda_fib(int num)
{
    std::function<int(int const>) lambda_fib = 
    [&lambda_fib](int const n)
    {
        return n <= 2 ? 1 : lambda_fib(n - 1) + lambda_fib(n - 2);
    }
    auto fnum = lambda_fib(num);
    std::cout << fnum << std::endl;
}