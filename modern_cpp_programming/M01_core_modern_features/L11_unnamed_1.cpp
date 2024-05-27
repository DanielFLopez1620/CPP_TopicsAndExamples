// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>
#include "L11_unnamed_1.h"

namespace
{
    int sum(int n1, int n2)
    {
        int res = n1 + n2;
        std::cout << "The sum provided results in: " << res << std::endl;
        return res;
    }
}

namespace unnamed_1
{
    int run_custom_sum_1(int n1, int n2)
    {
        return sum(n1, n2);
    }
}