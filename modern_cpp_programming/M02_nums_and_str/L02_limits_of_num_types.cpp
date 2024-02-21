// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

// If you do not know the limits of your types, you will have problems of
// resources later. Numeric types can be char, int and double. You may have
// heard of the C Macros, but C++ has its own style with 'numeric_limits'
// class.

// INFO #1: Usage of min() and max() static methods for numbers types, with
// template.

#include <limits>   // Header oriented to numeric_limits class template
#include <bitset>   // For using bitset class (which stores bits)
#include <climits>  // Equivalent to limits.h, defines constant with max and min
                    // size of fundamental types.

int minimum(int const* const start, int const, int const * const end)
{
    int minval = INT_MAX;
    for (int const * p = start; p != end; ++p)
    {
        if(*p < minval) minval =  *p;
    }
    return minval;
}

template<typename T, typename Iter>
T minimum(Iter const start, Iter const end)
{
    T minval = std::numeric_limits<T>::max();
    for(auto i= start; i < end; i++)
    {
        if (*i < minval) minval = *i;
    }
    return minval;
}

int main(int argc, char** argv)
{
    // INFO #2: Use static methods or constants to retrieve properties.
    // Keep in mind, that there is no limitation on std::numerics_limits<T>, so
    // use it over C macros.
    auto n = 16;
    std::bitset<std::numeric_limits<decltype(n)>::digits>
        bits { static_cast<unsigned long long> (n) };

    std::cout << "Bitset size obtained from n (16): " << bits << std::endl;
    return 0;
}