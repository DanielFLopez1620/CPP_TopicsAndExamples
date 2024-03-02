// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

/**
 * Literals refers to built-in types that cannot be altered, in C++ (and ahead)
 * you can create your own literals for numerical, character and string types. 
 * Cooked literals refers to those processed by the compilers, and it will be
 * the focus here. They appeared in C++11, and some features have been added
 * over time.
 * 
 * The steps to consider a literal are:
 * 
 * 1. Define literals in a separate namespace to avoid clashes.
 * 2. Prefix using '_' the suffix.
 * 3. Define the literal operator, which must be related to one of these:
 * 
 *      T operator "" _suffix(unsigned long long int);
 *      T operator "" _suffix(long double);
 *      T operator "" _suffix(char);
 *      T operator "" _suffix(wchar_t);
 *      T operator "" _suffix(char16_t);
 *      T operator "" _suffix(char32_t);
 *      T operator "" _suffix(char const *, std::size_t);
 *      T operator "" _suffix(wchar_t const *, std::size_t);
 *      T operator "" _suffix(char16_t const *, std::size_t);
 *      T operator "" _suffix(char32_t const *, std::size_t);
 * 
*/

#include <array>
#include <complex>
#include <chrono>
#include <string>

// Info #1: Creating literal by defining const expression.
namespace bytes_related
{
    constexpr size_t operator "" _MB(unsigned long long const size)
    {
        return static_cast<size_t>(size * 1024 * 1024);
    }
} 

// Info #2: Overriding operators in literals.
namespace packing
{
    enum class pack
    {
        kilogram,
        squeared_meters,
        num_elements,
    };

    template <pack P>
    //class 


}



int main(int argc, char** argv)
{
    // Info #1: Using literal by calling our implementation.
    using namespace bytes_related;
    auto mb_size{ 2_MB };
    using byte = unsigned char;
    auto buffer = std::array<byte, 1_MB>{};
    std::cout << "Example of literal 2 MB to bytes: " << mb_size << std::endl;

    // Info #2:
    return 0;
}