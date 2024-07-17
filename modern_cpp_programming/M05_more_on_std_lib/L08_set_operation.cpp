// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Set operations refer to those which allow su to do unions,
 * intersections or differences of sorted ranges. Their functionality
 * is related with iterators, then it works with any standar continer, array 
 * or custom type that is a sequences with iterators input available.
 * 
 * The set operation available are: 
 * 
 *      - Union: Considers all the elements present in the sets, but repetitive
 *        ones are just considered once.
 *      - Merge: Considers all the elements present in the set and combine them
 *      - Intersect: For obtaining just the element in common among the sets.
 *      - Difference: To obtain the different elements of each other range.
 *      - Includes: To check for subranges presence.
 * 
 * This operations should work for any standard container, and you can use them
 * for custom structures and classes, but you should have implemented the 
 * comparison operators.
 * 
 * Check the code below, you can run it with:
 * 
 *      g++ -std=c++20 L08_set_operations.cpp -o set_op.out
 *      ./set_op.out
 * 
 */

// -------------------------------- REQUIRED HEADERS --------------------------

#include <vector>     // For using dynamic arrays (containers) 
#include <algorithm>  // Collection of general purpose functionalities

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);

// -------------------------------- MAIN IMPLEMENTATION -----------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 8: Using set operations with a range\n" << std::endl;
    
    // Vector considerer for the practice of the lesson:
    std::vector<char> vec_chr1 {'b', 'c', 'd', 'e', 'h', 'i'};
    std::vector<char> vec_chr2 {'a', 'b', 'c', 'd', 'f', 'g'};
    std::vector<char> vec_chr3;
    std::cout << "For the set operations, consider the next vectors:"
              << std::endl << "\tFirst char array: ( ";
    display_content(vec_chr1);
    std::cout << ")" << std::endl << "\tSecond char array: (";
    display_content(vec_chr2);
    std::cout << ")" << std::endl;

    // Info #1: You can consider the union of elements (sum of the elements 
    // of both sets omitting repetions, as the elements appear one time).
    std::set_union(vec_chr1.cbegin(), vec_chr1.cend(), vec_chr2.cbegin(), 
        vec_chr2.cend(), std::back_inserter(vec_chr3));
    std::cout << "Let's consider the set operations: " << std::endl
              << "\tUnion: (";
    display_content(vec_chr3);
    std::cout << ")" << std::endl;

    // Info #2: You can consider merging two vectors, in this case, the union
    // considers elements that are present more than once too.
    vec_chr3.clear();
    std::merge(vec_chr1.cbegin(), vec_chr1.cend(), vec_chr2.cbegin(), 
        vec_chr2.cend(), std::back_inserter(vec_chr3));
    std::cout << "\tMerge: (";
    display_content(vec_chr3);
    std::cout << ")" << std::endl;

    // Info #3: Another operation is the intersection, just to check the 
    // elements that are present more of one time.
    vec_chr3.clear();
    std::set_intersection(vec_chr1.cbegin(), vec_chr1.cend(), vec_chr2.cbegin(), 
        vec_chr2.cend(), std::back_inserter(vec_chr3));
    std::cout << "\tIntersection: (";
    display_content(vec_chr3);
    std::cout << ")" << std::endl;

    // Info #4: You can make a difference, which implies that it will return the
    // elements from the first range that are not present in the second range, for
    // that you can use std::set_difference(), but you can also check simetric
    // differences with std::set_symmetric_difference().
    vec_chr3.clear();
    std::set_difference(vec_chr1.cbegin(), vec_chr1.cend(), vec_chr2.cbegin(), 
        vec_chr2.cend(), std::back_inserter(vec_chr3));
    std::cout << "\tDifference: (";
    display_content(vec_chr3);
    std::cout << ")" << std::endl;
    vec_chr3.clear();
    std::set_symmetric_difference(vec_chr1.cbegin(), vec_chr1.cend(), 
        vec_chr2.cbegin(), vec_chr2.cend(), std::back_inserter(vec_chr3));
    std::cout << "\tSymetric Difference: (";
    display_content(vec_chr3);
    std::cout << ")" << std::endl;

    // Info #4: You can check if a subset or subrange is present inside another
    // one with std::includes.
    std::vector<char> vec_chr4 {'c', 'd', 'f'};
    std::cout << "Searching for pattern: (";
    display_content(vec_chr4);
    std::cout << ")" << std::endl << "\tPresent in vector 1?: "
              << std::includes(vec_chr1.cbegin(), vec_chr1.cend(), 
                    vec_chr4.cbegin(), vec_chr4.cend())
              << std::endl << "\tPresent in vector 2?: "
              << std::includes(vec_chr2.cbegin(), vec_chr2.cend(), 
                    vec_chr4.cbegin(), vec_chr4.cend())
              << std::endl;

    return 0;

}  // main

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