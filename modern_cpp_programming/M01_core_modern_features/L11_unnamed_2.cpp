// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>
#include "L11_unnamed_2.h"

namespace
{
    int sum(int n1, int n2)
    {
        int res = n1 + n2;
        std::cout << n1 << " + " << n2 << " = " << res << std::endl;
        return res;
    }
}

namespace unnamed_2
{
    int run_custom_sum_2(int n1, int n2)
    {
        return sum(n1, n2);
    }
}
