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
 * Then, they can be implemented in the definitions you create, but the here we
 * prefered the non-member implementation, you can check the prototypes and 
 * definitions in this code. Also, we created a header file that contains the
 * previous definition of the custom_array we made in the lesson 10 of this
 * module.
 * 
 * When you are ready, you can run the code with:
 * 
 *      g++ -std=c++20 L11_non_member_acc.cpp -o non_member_acc.out
 *      ./non_member_acc.out
 */

// -------------------------... REQUIRED LIBRARIES ----------------------------
#include <vector>     // For using dynamic containers 
#include <algorithm>  // Collections of general purpose algorithms

#include "L11_custom_array.h"  // Import of the custom array class

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);

template<typename T, size_t N>
T* std::data(custom_array<T, N>& arr);

template<typename T, size_t N>
const T* std::data(const custom_array<T, N>& arr);

template<typename T, size_t N>
constexpr size_t std::size(const custom_array<T, N>&);

template<typename T, size_t N>
constexpr bool std::empty(const custom_array<T, N>&);


// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 11: Using non-meber function for accesing info\n"
              << std::endl;
    
    // Checking with standard float vector 
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

    // Checking with integer array
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

    // Using non-memnber definitions for custom array
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
              << "\tContent: (";
    for(auto const & element : cus_example)
    {
        std::cout << element << ", ";
    }
    std::cout << ")" << std::endl;
    

    return 0;
} // main

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

/**
 * Non member function to obtain the direction in memory where the container
 * begins.
 * 
 * @param arr Custom generic container that considers a type and a size
 * 
 * @return Direction that can be pointed to achieve the beginning of the cont.
 */
template<typename T, size_t N>
T* std::data(custom_array<T, N>& arr)
{
    return arr.begin() == arr.end() ? nullptr : &*arr.begin();

} // std::data

/**
 * Non member funtion to obtain the direction in memory where the container
 * (a constant container) begins.
 * 
 * @param arr Custom generic container that considers a type and a size
 * 
 * @return Direction that can be pointed to achieve the beginning of the cont.
 */
template<typename T, size_t N>
const T* std::data(const custom_array<T, N>& arr)
{
    return arr.begin() == arr.end() ? nullptr : &*arr.begin();
} // std::data const

/**
 * Non member function to obtain the size of a custom array.
 * 
 * @param array Constant pointer to specified custom array.
 * 
 * @return Attribute that stores the current size of the container.
 */
template<typename T, size_t N>
constexpr size_t std::size(const custom_array<T, N>&)
{
    return N;
} // std::size

/**
 * Non member function to check if the custom array is empty.
 * 
 * @param Constant pointer to specified custom array
 * 
 * @return True if the custom array is empty, False otherwise.
 */
template<typename T, size_t N>
constexpr bool std::empty(const custom_array<T, N>&)
{
    return N == 0;
} // std::empty