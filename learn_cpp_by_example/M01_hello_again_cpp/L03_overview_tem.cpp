// Based on the Learn C++ by Example (2024) by Frances Buontempo

// /////////////////////////// IMPORTS ////////////////////////////////////////
#include <iostream>   // Input / Output streams
#include <functional> // For using pre-defined general-purpose functions

// ////////////////////////// GLOBAL DEFINITIONS //////////////////////////////

/**
 * Simple template for operating two values of a given type, where the sum
 * considers the left-hand side and the right-hand side values.
 *
 * @param lhs First value
 * @param rhs Second value
 *
 * @return Sum of the values
 *
 */
template <typename T, typename U>
auto generic_addition(T lhs, U rhs) -> decltype(lhs + rhs)
{
    // The trailing operator above help to define the return type
    return lhs + rhs;
}

// ////////////////////////// MAIN FUNCTION ///////////////////////////////////

/**
 * Program oriented to use a templated previously defined for a sum.
 */
auto main() -> int
{
    auto a = 162;
    auto b = 26.1;
    std::cout << "Using a sum on a template:\n\t" << a << " + " << b
              << " = " << generic_addition(a,b) << std::endl;

    return 0;
}