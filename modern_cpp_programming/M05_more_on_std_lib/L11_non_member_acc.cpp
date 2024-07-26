// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasm't tested for C++20

#include <iostream>

/**
 * In the previous lesson we checked the standard container implementation
 * of begin() and end() member functions. However, there are more, like
 * cbegin()/cend(), rbegin()/rend(), crbegin()/crend() that return iterators. 
 * And after C++17 more appeared, like std::data() that returns a pointer to
 * the memory block, std::size() that returns the size of the container, 
 * std::empty() that specifies wheter the container is empty or not. Also,
 * in C++20 std::ssize() was added to return the size of a container as a 
 * signed int. In resume they are used for:
 * 
 *  - std::size() -> Returns the size of the container
 *  - std::empty() -> Checks if the array is empty
 *  - std::data() -> Return the position in memory
 * 
 * Then, they can be implemented in the definitions you create, but the
 */

// -------------------------... REQUIRED LIBRARIES ----------------------------
#include <vector>     // For using dynamic containers 
#include <algorithm>  // Collections of general purpose algorithms
#include <string>

#include "L11_custom_array.h"

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);


template<typename T, size_t N>
T* data(custom_array<T, N>& arr)
{
    return arr.begin() == arr.end() ? nullptr : &*arr.begin();
}

template<typename T, size_t N>
const T* data(const custom_array<T, N>& arr)
{
    return arr.begin() == arr.end() ? nullptr : &*arr.begin();
}

template<typename T, size_t N>
constexpr size_t size(const custom_array<T, N>&)
{
    return N;
}

template<typename T, size_t N>
constexpr bool empty(const custom_array<T, N>&)
{
    return N == 0;
}


// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 11: Using non-meber function for accesing info\n"
              << std::endl;
    
    std::vector<float> vec_flt1 {1.6, 2.0, 6.2, 1.0};
    auto s_v1 = std::size(vec_flt1);
    auto e_v1 = std::empty(vec_flt1);
    auto d_v1 = std::data(vec_flt1);
    std::cout << "Using a float container: " << std::endl
              << "\tSize: " << s_v1 << std::endl 
              << "\tIs empty?: " << e_v1 << std::endl
              << "\tData:" << d_v1 << std::endl
              << "\tContent: (";
    display_content(vec_flt1);
    std::cout << ")" << std::endl;

    int arr_int1[4] = {1620, 261, 162, 612};
    auto s_v2 = std::size(arr_int1);
    auto e_v2 = std::empty(arr_int1);
    auto d_v2 = std::data(arr_int1);
    std::cout << "Using a integer array: " << std::endl
              << "\tSize: " << s_v2 << std::endl 
              << "\tIs empty?: " << e_v2 << std::endl
              << "\tData:" << d_v2 << std::endl
              << "\tContent: (";
    for (int i = 0; i < s_v2; i++)
    {
        std::cout << arr_int1[i] << ", ";
    }
    std::cout << ")" << std::endl;


    custom_array<float, 4> cus_example;
    cus_example[0] = 1.6;
    cus_example[1] = 6.2;
    cus_example[2] = 2.0;
    cus_example[3] = 1.0;
    auto s_v3 = std::size(cus_example);
    auto e_v3 = std::empty(cus_example);
    auto d_v3 = std::data(cus_example);

    std::cout << "Using custom_array: " << std::endl
              << "\tSize: " << s_v3 << std::endl 
              << "\tIs empty?: " << e_v3 << std::endl
              << "\tData:" << d_v3 << std::endl
              << "\nHere, we didn't defined data or empty (yet)..."
              << "\tContent: (";
    for(auto const & element : cus_example)
    {
        std::cout << element << ", ";
    }
    std::cout << ")" << std::endl;
    

    return 0;
}

// ---------------------- FUNCTION DEFINITIONS --------------------------------

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



