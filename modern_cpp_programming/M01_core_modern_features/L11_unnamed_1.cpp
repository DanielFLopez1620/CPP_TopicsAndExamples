// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

// Include custom header for the prototype and namespace usage
#include "L11_unnamed_1.h"

// Usage of unnamed namespace (name will be resolved by the compiler)
namespace
{
    /**
     * Simple sum function that calculates the sum of two integers
     * and display just the result.
     * 
     * @param n1 First integer
     * @param n2 Second integer
     * 
     * @return Sum of the nums.
    */
    int sum(int n1, int n2)
    {
        int res = n1 + n2;
        std::cout << "The sum provided results in: " << res << std::endl;
        return res;
    }
} // unnamed namespace

namespace unnamed_1
{
    // Definition of the prototpye previosly created for calling the second sum
    int run_custom_sum_1(int n1, int n2)
    {
        // Return the value returned by the second sum (and display the msg)
        return sum(n1, n2);
    }

} // namespace unnamed_1