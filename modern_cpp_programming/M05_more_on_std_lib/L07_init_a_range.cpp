// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Filling a range with values is an important operation, and this is
 * needed for every container, here we will illustrate some initialization
 * cases with std::vector, but it should work any standard container that has
 * a forward iterator defined. The libraries needed are <numeric> for
 * std::iota() and algorithm for the other ones.
 * 
 * Keep in mind that they work with iterators, but can work differently, for
 * example, a function or method can ask for the begin and end iterators while
 * other one just ask for the begin iterator and a count value. For the cases
 * of the algorithm you will see below which uses counts (to n values), they
 * can return the iterator to the first element if the count is not greater
 * than zero.
 * 
 * When ready, you can compile and run the code below with:
 * 
 *      g++ -std=c++20 L07_init_a_range.cpp -o init_range.out
 *      ./init_range.out
 */

// ------------------------------- REQUIRED HEADERS ---------------------------

#include <algorithm> // Collection of general purpose functions
#include <numeric>   // For function related with numeric representation
#include <vector>    // For using dynamic arrays or sequencial containers
#include <random>    // Pseudo random generation and related operations

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);

// ------------------------------- MAIN IMPLEMENTATION ------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 7: Initialization of elements in a range:\n" 
              << std::endl;
    
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

    // Info #2: You can also just fill the first n values with std::fill_n
    // but make sure that when you use it, you do not surpass the index of the
    // last element.
    std::cout << "Filling part of a vector with a single value: " << std::endl
              << "\tEmpty vector: (";
    std::vector<float> vec_flt2(7);
    display_content(vec_flt2);
    std::cout << ")" << std::endl << "\tFilled 3 first pos: (";
    std::fill_n(vec_flt2.begin(), 3, 16.20);
    display_content(vec_flt2);
    std::cout << ")" << std::endl;

    // Info #3: Remember the random number generation we used in the module 2?
    // Well... you can use it here too, in combination with std::generate(). 
    // Even, similar to the case with full, you can use std::generate_n(). Also,
    // consider that if you need o use the value of the elements to generate
    // new values, you should try std::transform() instaed.
    std::cout << "Filling a vector with pseudo-random values: " << std::endl
              << "\tEmpty vector: (";
    std::vector<float> vec_flt3(6);
    display_content(vec_flt3);
    std::cout << ")" << std::endl << "\tFilled vector: (";
    std::random_device rand_dev{};
    std::mt19937 mt { rand_dev() };
    std::uniform_real_distribution<> uniform_distro{16, 20};
    std::generate(vec_flt3.begin(), vec_flt3.end(), 
        [&uniform_distro, &mt] { return uniform_distro(mt); });
    display_content(vec_flt3);
    std::cout << ")" << std::endl;

    // Info #4: If you want to generate incremental ranges, you can use
    // std::iota(), but you should consider that the base type of the container
    // must have the operator++ implementated.
    std::cout << "Filling a vector with increments: " << std::endl
              << "\tEmpty vector: (";
    std::vector<float> vec_int1(10);
    display_content(vec_int1);
    std::cout << ")" << std::endl << "\tFilled vector (start is 15): (";
    std::iota(vec_int1.begin(), vec_int1.end(), 15);
    display_content(vec_int1);
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