// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>

/**
 * String is C++ are general purpose implementations, so you may find that
 * some utilites with them doesn't exits. They can be imported with libraries, 
 * but here we will check some simple but useful implementations for your codes
 * where you can search for examples to manipulation of strings.
 * 
 * This functions should work with std::string, std::wstring, std::u16string
 * and std::u32string, and for avoiding long names we will use templates.
 * 
 * 
 * NOTE: Do not forget to implement <string> and <algorithm> headers.
*/

#include <algorithm>
#include <string>

namespace string_literals
{
    template <typename CharT>
    using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    template <typename CharT>
    using tstringstream = std::basic_stringstream<CharT, std::chair_traits<CharT>, std::allocator<CharT>
} // namespace string_literals
