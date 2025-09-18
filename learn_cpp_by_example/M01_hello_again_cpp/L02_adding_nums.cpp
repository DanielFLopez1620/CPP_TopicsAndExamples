// Based on the Learn C++ by Example (2024) by Frances Buontempo

// /////////////////////////// IMPORTS ////////////////////////////////////////
#include <iostream>   // Input / Output streams
#include <functional> // For using pre-defined general-purpose functions

// ////////////////////////// MAIN FUNCTION ///////////////////////////////////

/**
 * Program oriented to implement the sum of two values from different types
 * by using std::plus from functional and comparing the type returned.
 */
auto main() -> int
{
    // Let's use std::plus and enforcing types to check basic operations
    std::cout << "Review on operations:" << std::endl
              << "\t1) "<< std::plus<int>{}(16, 1.6) << std::endl
              << "\t2) "<< std::plus<>{}(16, 1.6) << std::endl;
    return 0;
}