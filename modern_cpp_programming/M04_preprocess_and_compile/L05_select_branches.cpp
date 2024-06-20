// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * C++17 came with a feature to simplify codes when wanting to define function
 * overloads and variadic arguments. It is a constexpr if, which result in 
 * a condition that will be evaluated at compile time that allows to select
 * certain branches of a code. The structure is the next one:
 * 
 *      if constexpr (init-statement condition) <statement-true>
 *      else <statement-false>
 * 
 * In compile time, the expression is evaluated to check if it is convertible
 * to a boolean type. If the condition is true, the body of the statement is
 * selected and ends in the traslation unit, but it is false, the else branch
 * is evlauated, discarded statements do not contribute to the function type
 * deduction.
 * 
 * The objective of this lesson is to show instructions easier to understand, 
 * decrease the quantity of code and make sure that the programmer doesn't
 * require advanced template metaprogramming skills.
 * 
 * NOTE: If you haven't asked about it... when we have std::point<T> it is 
 * referring to class templates defined in <type_trais> header, in this case if
 * it detects a pointer, it will provide the value (::value) meber, that is true
 * in case of pointer. On the other hand, std::is_pointer_v<T> refers to type
 * traits value constants, also defined in type traits, and they are more concise
 * in given the value.
 * 
 * You can compile and use this code with:
 *  
 *      g++ -std=c++20 L05_select_branches.cpp -o branches.out
 *      ./branches.out
*/

// --------------------------- REQUIRED HEADERS -------------------------------
#include <memory>       // For dynamic memory management
#include <type_traits>  // For type usages and related operations with types

// ------------------------- STRUCT AND CLASSES IMPLEMENTATION ----------------

// Info #1: You can change the usage of std::enable_if and still be relying on
// the SFINAE with a if constexpr to impose restrictions on function templates
// for your code...
/**
 * Simple getter function that considers if the argument passed is a variable
 * (acces the value) or a pointer (access to the pointed value).
 * 
 * @param value Element of interest to obtain the value.
 * 
 * @return Accessed value.
 */
template <typename T>
auto get_value(T value)
{
    if constexpr (std::is_pointer_v<T>)
        return *value;  // Return the dereferenced pointer
    else
        return value;   // Return the original value
}

// In constrast, you can use the enable_if command to obtain similar results:
/**
 * Getter of value that uses enable_if, just to get the value of elements by
 * considering pointed directions.
 * 
 * @param value Element of interest to obtain the value (ptr)
 * 
 * @return Pointed value
 */
template <typename T, typename = typename std::enable_if_t<
    std::is_pointer_v<T>, T>>
auto get_value_e_p(T value)
{
    return *value;
}

/**
 * Getter of value that uses enable_if, just to get the value of elements by
 * considering pointed directions.
 * 
 * @param value Element of interest to obtain the value (var)
 * 
 * @return Stored value
 */
template <typename T, typename = typename std::enable_if_t<!std::is_pointer_v<T>, T>>
auto get_value_e_v(T value)
{
    return value;
}

// Info #2: If you remeber from the module 2, when using user-defined-literals
// we created a bit implementation for 8-bit, 16-bit and 32-bit. There we used 
// a "compile recursion" by using templates. Here we use ifcconstexpr to check
// the types to produces a more readable code when creating user defined 
// implementations. Do not forget to compare and constrart changes with the
// L06_raw_user_literals.cpp from module 2 (nums_and_str).
namespace binary
{
    // Alias for bytes of size 8
    using byte8 = unsigned char;

    // Namespace oriented to user defined binary literals 
    namespace binary_literals
    {
        // Namespace oriented to functions and operators of the binary literals.
        namespace binary_literals_interns
        {
            // Function template that evaluates recursively a template a binary
            // chain, based on a CharT type, a letter or character d and a pack
            // of characters bits.
            template <typename CharT, char d, char... bits>
            constexpr CharT binary_eval()
            {
                // If the size of the pack is zero, converst the value of the
                // single character.
                if constexpr(sizeof...(bits) == 0)
                    return static_cast<CharT>(d-'0');
                // Otherwise, it recursively processes the remaining bits and
                // construct the rest values with left shifting and bit-wise 
                // OR with the other bits.
                else if constexpr(d == '0')
                    return binary_eval<CharT, bits...>();
                else if constexpr(d == '1')
                    return static_cast<CharT>((1 << sizeof...(bits)) | binary_eval<CharT, bits...>());
            }   
        }
        // Define of literal for b8, in other words, bits chains with size 8.
        template<char... bits>
        constexpr byte8 operator""_b8()
        {
            static_assert(
                sizeof...(bits) <= 8,
                "Binary b8 is longer than expected"
            );
            return binary_literals_interns::binary_eval<byte8, bits...>();
        }
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Lesson 5: Branch selection with if cosntexpr...\n" 
              << std::endl;
    // Using getter of value that is based on if const expr
    std::cout << "Getter of value (can be pointer or variable): " << std::endl;
    auto value1 = get_value(16.20);
    auto ptr = std::make_shared<float>(20.16);
    auto value2 = get_value(ptr);

    std::cout << "\tGet value of var: " << value1 << std::endl
              << "\tGet value of ptr: " << value2 << std::endl;

    // Using binary literals
    using namespace binary;
    using namespace binary_literals;

    std::cout << "\nReShaping binary literals with if constxpr.." << std::endl;
    auto my_8bit = 1100_b8;
    std::cout << "\tByte 8: " << (int) my_8bit << std::endl;
    return 0;

} // main