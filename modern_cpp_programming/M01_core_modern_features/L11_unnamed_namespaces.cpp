// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * When your project increases size, it becomes more probable to have name
 * conflicts, in C you resolved this with static definitions. But there is
 * a better way to do it in C++ after C++11, and it is called 'unnamed 
 * namespaces', that creates namespaces automatically by the compiler, then
 * preventing name conflicts. And as you suppose, its structure is like this:
 * 
 *      namespace 
 *      {
 *          // Functions or variables to consider.
 *      }
 * 
 * This lesson is divided in mutiple files, let's mention brief notes on them:
 * 
 * ...
*/

#include "L11_unnamed_1.h"
#include "L11_unnamed_2.h"

int main(int argc, char* argv[])
{
    std::cout << "First sum implementation:\n\t";
    auto v1 = unnamed_1::run_custom_sum_1(16, 20);
    std::cout << "Second sum implementation:\n\t";
    auto v2 = unnamed_2::run_custom_sum_2(16, 20);

    return 0;
}