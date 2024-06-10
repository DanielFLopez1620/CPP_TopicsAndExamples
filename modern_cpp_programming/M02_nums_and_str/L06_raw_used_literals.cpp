// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>

/**
 * Raw literals refer to those cases where the literal isn't processed by the
 * compiler, and it only owrks for integral and floating-point types.
 * 
 * We will illustrate them with binary literals refering to the size of each
 * one, in the case will be _b8 (byte8), _b16(byte16) and _b32(byte32), the
 * steps for creation are:
 * 
 *  1. Use a namespace to avoid name clashes.
 *  2. Consider a suffix (including the underscore)
 *  3. Define a literal operator (or template):
 *      T operator "" _suffix(const char*);
 * 
 * NOTE: The ellipsis ('...') used in the templates below are used to declare a
 * parameter pack, in this case, it will be a pack of char types related with 
 * ones and zeros for the bits.
 * 
 * When ready, you can runt his code with:
 * 
 *      g++ -std=c++14 L06_raw_used_literals.cpp -o raw_literals.out
 *      ./raw_literals.out
*/

// -------------------- CLASS AND STRUCT DEFINITIONS --------------------------

// Info #1: Here we define a namespace 'binary' and define type aliases, we
// want to use types like 1111_b8 or 000010100000_b16. The literal operators
// are nested in the namespace called 'binary_literals' (which is made to 
// avoid name collisions).
// The usage of two additional namespaces 'binary_literals' and 
// 'binary_interns' is to achieve a good pratice and hides the implementation
// details from the client.
namespace binary
{
    using byte8 = unsigned char;
    using byte16 = unsigned short;

    namespace binary_literals
    {
        namespace binary_interns
        {
            // The implementation below seems to be recursive but it isn't true
            // runtime recursion, this is because of the extension that is made
            // by the compiler when using templates.
            
            // Base template that includes parameter pack of chars
            template <typename CharT, char... bits>
            struct binary_struct;

            // Specialization for '0'
            template <typename CharT, char... bits>
            struct binary_struct<CharT, '0', bits...>
            {
                static constexpr CharT value
                    { binary_struct<CharT, bits...>::value };
            };

            // Specialization for '1'
            template <typename CharT, char... bits>
            struct binary_struct<CharT, '1', bits...>
            {
                static constexpr CharT value
                    { binary_struct<CharT, bits...>::value };
            };

            // Last specialization (empty)
            template <typename CharT>
            struct binary_struct<CharT>
            {
                static constexpr CharT value{ 0 };
            };
        }
        template<char... bits>
        constexpr byte8 operator""_b8()
        {
            // Check that the size is 8 (it cannot have trailing zeros)
            static_assert(
                sizeof...(bits) <= 8,
                "Binary byte8 must be up to 8 digits long");
            return binary_interns::binary_struct<byte8, bits...>::value;
        }
        template<char... bits>
        constexpr byte16 operator""_b16()
        {
            // Check that the size is 16 (it cannot have trailing zeros)
            static_assert(
                sizeof...(bits) <= 16,
                "Binary byte8 must be up to 16 digits long");
            return binary_interns::binary_struct<byte8, bits...>::value;
        }
    }
}

// -------------------------- MAIN IMPLEMENTATION -----------------------------

int main(int argc, char** argv)
{
    std::cout << "Lesson 6: Creating raw user literals...\n" << std::endl;
    
    // Info #2: Implementing our own raw literals, for this remember to use the
    // proper namespaces.

    using namespace binary;
    using namespace binary_literals;

    auto byte1 = 1001_b8;
    auto byte2 = 100010001001_b16;

    std::cout << "Example by using binary literals to indicate its size:"
              << std::endl << "Byte1: (8 bits)" << (int) byte1 << std::endl
              << "Byte2: (16 bits)" << (int) byte2 << std::endl 
              << "For properly using raw literals you will also need to "
              << "override the operator<< and specify the proper string."
              << std::endl;

    return 0;

} // main