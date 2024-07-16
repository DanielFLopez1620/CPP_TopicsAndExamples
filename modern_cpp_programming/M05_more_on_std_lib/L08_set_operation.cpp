// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Set operations refer to those which allow su to do unions,
 * intersections or differences of sorted ranges. Their functionality
 * is related with iterators, then it works with any standar continer, array 
 * or custom type that is a sequences with iterators input available.
 * 
 */

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);

// -------------------------------- MAIN IMPLEMENTATION -----------------------

int main(int argc, char* argv[])
{
    return 0;
}

// ------------------------------- FUNCTION DEFINITION ------------------------

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