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
 * Some functions and methods to consider are listed here:
 * 
 * - std::begin -> Returns beginning sequence of string.
 * - std::end -> Returns ending sequence of string.
 * - std::reverse -> Inverts the order of the given string/array.
 * - <str>.find_last_of_not -> Method that search for last different pattern.
 * - <str>.find_last_of -> Method that search for last same pattern.
 * - <str>.substr -> for returing substring of type (index, index + count).
 * 
 * The previous mentions aren't complete instructions, do not forget to check
 * the code below and the documentation for better understanding.
 * 
 * You can run this code with: 
 * 
 *      g++ -std=c++14 L08_string_helpers.cpp -o lib_str.out
 *      ./lib_str.out
 * 
 * NOTE: Do not forget to implement <string> and <algorithm> headers.
*/

#include <algorithm>  // For various purposes related with seacrhing, sorting...
#include <string>     // String and char array management
#include <vector>     // For vector structure management

namespace string_lib
{
    // Template for general string
    template <typename CharT>
    using tstring = std::basic_string<CharT, std::char_traits<CharT>, 
        std::allocator<CharT>>;

    // Template for general string stream
    template <typename CharT>
    using tstringstream = std::basic_stringstream<CharT, 
        std::char_traits<CharT>, std::allocator<CharT>>;

    // Iteratets throught the array and convert every letter to its uppercase
    // if it is lower. Symbols and numbers remain the same.
    template<typename CharT>
    inline tstring<CharT> to_upper(tstring<CharT> text)
    {
        std::transform(std::begin(text), std::end(text), std::begin(text), 
            toupper);
        return text;
    }

    // Iteratets throught the array and convert every letter to its lowercase
    // if it is upper. Symbols and numbers remain the same.
    template<typename CharT>
    inline tstring<CharT> to_lower(tstring<CharT> text)
    {
        std::transform(std::begin(text), std::end(text), std::begin(text), 
            tolower);
        return text;
    }

    // Rearrange the char array or string by its reverse
    template<typename CharT>
    inline tstring<CharT> reverse(tstring<CharT> text)
    {
        std::reverse(std::begin(text), std::end(text));
        return text;
    }

    // Trim the spaces at the beginning and at the end of an array.
    template<typename CharT>
    inline tstring<CharT> trim(tstring<CharT> const & text)
    {
        auto first{text.find_last_not_of(' ') };
        auto last{text.find_last_not_of(' ') };
        return text.substr(first, (last-first + 1));
    }

    // Trim the spaces of a string only at the beginning.
    template<typename CharT>
    inline tstring<CharT> trimleft(tstring<CharT> const & text)
    {
        auto first{ text.find_first_not_of(' ') };
        return text.substr(first, text.size() - first);
    }

    // Trim the spaces of a string only at the end.
    template<typename CharT>
    inline tstring<CharT> trimright(tstring<CharT> const & text)
    {
        auto last{ text.find_last_not_of(' ') };
        return text.substr(0, last + 1);
    }

    // Trim the certain pattern of chars from all the string.
    template<typename CharT>
    inline tstring<CharT> trim(tstring<CharT> const & text,
                            tstring<CharT> const & chars)
    {
        auto first{ text.find_first_not_of(chars) };
        auto last{ text.find_last_not_of(chars) };
        return text.substr(first, (last - first + 1));
    }

    // Trim the certain pattern of chars beginning from the left.
    template<typename CharT>
    inline tstring<CharT> trimleft(tstring<CharT> const & text,
                                tstring<CharT> const & chars)
    {
        auto first{ text.find_first_not_of(chars) };
        return text.substr(first, text.size() - first);
    }

    // Trim the certain pattern of chars beginning from the right.
    template<typename CharT>
    inline tstring<CharT> trimright(tstring<CharT> const &text,
                                    tstring<CharT> const &chars)
    {
        auto last{ text.find_last_not_of(chars) };
        return text.substr(0, last + 1);
    }

    // Remove a letter of a string (will not be substituted)
    template<typename CharT>
    inline tstring<CharT> remove(tstring<CharT> text, CharT const letter)
    {
        auto start = std::remove_if(
            std::begin(text), std::end(text), [=](CharT const c) 
            {
                return c == letter;
            });
        text.erase(start, std::end(text));
        return text;
    }

    // Split an array by considering a delimitator
    template<typename CharT>
    inline std::vector<tstring<CharT>> split (tstring<CharT> text, CharT const delimiter)
    {
        auto sstr = tstringstream<CharT> { text };
        auto tokens = std::vector<tstring<CharT>>{};
        auto token = tstring<CharT>{};
        while( std::getline(sstr, token, delimiter) )
        {
            if(!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }
} 

int main(int argc, char** argv)
{
    // Info #2: Using the library of string helpers:

    // Do not forget the proper namespace
    using namespace std::string_literals;

    // Create the different cases of usages 
    auto str1 {"  WhicH_letTERCase  "s};
    auto str1_up{ string_lib::to_upper(str1) };
    auto str1_lo{ string_lib::to_lower(str1) };
    auto str1_rv{ string_lib::reverse(str1) };
    auto str1_tl{ string_lib::trimleft(str1) };
    auto str1_tr{ string_lib::trimright(str1) };
    auto str1_tg{ string_lib::trim(str1) };
    auto str1_rm{ string_lib::remove(str1, 'e')};

    auto str2 { "!!  this % needs a lot\rof trimming  !\n"s };
    auto trimed {" !%\n\r"s };
    auto str2_tp { string_lib::trim(str2, trimed)};

    // Display the results
    std::cout << "String commands:\n\tOriginal: " << str1 << std::endl 
              << "\tUpper: " << str1_up << std::endl
              << "\t Lower: " << str1_lo << std::endl
              << "\t Reverse: " << str1_rv << std::endl
              << "\t Trim spaces left: " << str1_tl << std::endl
              << "\t Trim spaces right: " << str1_tr << std::endl
              << "\t Trim spaces: " << str1_tg << std::endl
              << "\t REmove e: " << str1_rm << std::endl
              << "String commands 2:\n\tOriginal: " << str2
              <<  "\tTrim chars %!\\h: " << str2_tp << std::endl; 

    return 0;
}
