// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Filling a range with values is an important operation, and this is
 * needed for every container, here we will illustrate some initialization
 * cases with std::vector, but it should work any standard container that has
 * a forward iterator defined. The libraries needed are <numeric> for
 * std::iota() and algorithm for the other ones.
 */

#include <algorithm>
#include <numeric>
#include <vector>

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);

int main(int argc, char* argv[])
{
    // Info #1: You can simply fill a vector with the same value for all the
    // positions of interest. For this purpose you can use std::fill().
    std::cout << "Filling a vector with a single value: " << std::endl
              << "\tEmpty vector: (";
    std::vector<float> vec_flt1(7);
    display_content(vec_flt1);
    std::cout << ")" << std::endl << "\tFilled vector: (";
    std::fill(vec_flt1.begin(), vec_flt1.end(), 16.20);
    display_content(vec_flt1);
    std::cout << ")" << std::endl;


    return 0;
}

// ------------------------------- FUNCTION DEFINITIONS -----------------------

/**
 * Generic displayer of the elements of the given container. 
 * 
 * @param vector Generic vector of interest
 */
template <typename T>
void display_content(std::vector<T> vector)
{
    for( const auto& element : vector )
    {
        std::cout << element << ", ";
    }
} // display_content