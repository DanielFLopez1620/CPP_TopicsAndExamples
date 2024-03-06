// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

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
 *  3. Define a literal operator (or template).
*/

namespace binary
{
    using byte8 = unsigned char;
    using byte16 = unsigned short;
    using byte32 = unsigned int;

    namespace binary_literals
    {
        namespace binary_interns
        {
            template <typename CharT, char... bits>
            struct binary_struct;

            template <typename CharT, char... bits>
            struct binary_struct<CharT, '0', bits...>
            {
                static constexpr CharT value
                    { binary_struct<CharT, bits...>::value> };
            };
        }
    }
}