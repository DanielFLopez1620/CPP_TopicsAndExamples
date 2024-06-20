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
 * - L11_unnamed_1.h : Contains the prototype's call of the first sum function.
 * - L11_unnamed_1.cpp : Have the unnamed namespace and the implementation of
 *   the second function.
 * - L11_unnamed_2.h : Contains the prototype's call of the second sum func.
 * - L11_unnamed_2.cpp : Define another unnamed namespace and the
 *   implementation of the second sum function.
 * - L11_unnamed_namespaces.cpp : Contains the info of the lesson of unnamed
 *   namespaces and the call to test that there is no name conflicts.
 * 
 * Explore the different files and implementations, when you are ready, you can
 * use:
 * 
 *      g++ -std=c++20 L11_unnamed_1.cpp L11_unnamed_2.cpp 
 *           L11_unnamed_namespaces.cpp -o unnamed.out
 *      ./unnamed.out
*/

// ------------ Include custom headers for sum implementations ----------------
#include "L11_unnamed_1.h"
#include "L11_unnamed_2.h"

// ---------------------------- MAIN IMPLEMENTATION ---------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 11: Unnamed namespaces and usage:\n" << std::endl;

    // Using the first sum function
    std::cout << "First sum implementation:\n\t";
    auto v1 = unnamed_1::run_custom_sum_1(16, 20);

    // Using the second sum function
    std::cout << "Second sum implementation:\n\t";
    auto v2 = unnamed_2::run_custom_sum_2(16, 20);

    return 0;
}  // main