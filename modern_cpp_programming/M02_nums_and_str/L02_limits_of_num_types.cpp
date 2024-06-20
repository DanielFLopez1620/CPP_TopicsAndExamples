// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

/*
 * If you do not know the limits of your types, you will have problems of
 * resources later. Numeric types can be char, int and double. You may have
 * heard of the C Macros, but C++ has its own style with 'numeric_limits'
 * class.
 * 
 * Remember you can compile this code, with:
 *
 *     g++ -std=c++11 L02_limits_of_num_types.cpp -o limits_of_num_types.out
 *     ./limits_of_num_types.out
 */

// ---------------------- REQUIRED HEADERS ----------------------------------

#include <limits>   // Header oriented to numeric_limits class template
#include <bitset>   // For using bitset class (which stores bits)
#include <climits>  // Equivalent to limits.h, defines constant with max and min
                    // size of fundamental types.


// --------------------- CLASS AND TYPES DEFINITIONS --------------------------

// INFO #1: You can use numeric types to retrieve different properties of a num
// type. And if you implement it with a template, it can be more useful, you can
// get: 
// min() -> Minimum value that can manage
// max() -> Maximum value that can manage
// digits() -> Digits it have, excluding sign and padding bits.
// is_integer() -> Boolean validation wheter is int type.
// Do not forget to check the docs, to see more cases.
template <typename T>
void type_properties()
{
    std::cout   
        << "Min Value: " << std::numeric_limits<T>::min() << std::endl
        << "Max Value: " << std::numeric_limits<T>::max() << std::endl
        << "Digits: " << std::numeric_limits<T>::digits << std::endl;
} // type_properties

// -------------------- MAIN IMPLEMENTATION -----------------------------------
int main(int argc, char** argv)
{
    std::cout << "Lesson 2: Limit of the numeric types...\n" << std::endl;
    
    // Keep in mind, that there is no limitation on std::numerics_limits<T>, so
    // use it over C macros.
    std::cout << "Double properties:" << std::endl;
    type_properties<double>();

    std::cout << "Float properties:" << std::endl;
    type_properties<float>();

    std::cout << std::endl;

    // INFO #2: Use static methods or constants to retrieve conversions, for
    // example, with bitsets.
    auto n = 16;
    std::bitset<std::numeric_limits<decltype(n)>::digits>
        bits1 { static_cast<unsigned long long> (n) };
    
    auto m = 16.20;
    std::bitset<std::numeric_limits<decltype(m)>::digits>
        bits2 {static_cast<unsigned long long>(m) };

    // You can use templates to use numeric limits with any type, as the
    // templates will allow it. And remember, that all the members of 
    // 'std::numeric_limits' are 'constexpr' that implies they can be used
    // where constant expressions are needed.

    std::cout << "Bitset size obtained from n (16): " << bits1 << std::endl;
    std::cout << "Bitset size obtained from m (16.20): " << bits1 << std::endl;

    
    return 0;

} // main