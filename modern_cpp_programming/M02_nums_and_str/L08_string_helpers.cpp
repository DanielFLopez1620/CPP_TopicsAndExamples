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
#include <vector>

namespace string_lib
{
    template <typename CharT>
    using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    template <typename CharT>
    using tstringstream = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    template<typename CharT>
    inline tstring<CharT> to_upper(tstring<CharT> text)
    {
        std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
        return text;
    }

    template<typename CharT>
    inline tstring<CharT> to_lower(tstring<CharT> text)
    {
        std::transform(std::begin(text), std::end(text), std::begin(text), tolower);
        return text;
    }

    template<typename CharT>
    inline tstring<CharT> reverse(tstring<CharT> text)
    {
        std::reverse(std::begin(text), std::end(text));
        return text;
    }

    template<typename CharT>
    inline tstring<CharT> trim(tstring<CharT> const & text)
    {
        auto first{text.find_last_not_of(' ') };
        auto last{text.find_last_not_of(' ') };
        return text.substr(first, (last-first + 1));
    }

    template<typename CharT>
    inline tstring<CharT> trimleft(tstring<CharT> const & text)
    {
        auto first{ text.find_first_not_of(' ') };
        return text.substr(first, text.size() - first);
    }

    template<typename CharT>
    inline tstring<CharT> trimright(tstring<CharT> const & text)
    {
        auto last{ text.find_last_not_of(' ') };
        return text.substr(0, last + 1);
    }

    template<typename CharT>
    inline tstring<CharT> trim(tstring<CharT> const & text,
                            tstring<CharT> const & chars)
    {
        auto first{ text.find_first_not_of(chars) };
        auto last{ text.find_last_not_of(chars) };
        return text.substr(first, (last - first + 1));
    }

    template<typename CharT>
    inline tstring<CharT> trimleft(tstring<CharT> const & text,
                                tstring<CharT> const & chars)
    {
        auto first{ text.find_first_not_of(chars) };
        return text.substr(first, text.size() - first);
    }

    template<typename CharT>
    inline tstring<CharT> trimright(tstring<CharT> const &text,
                                    tstring<CharT> const &chars)
    {
        auto last{ text.find_last_not_of(chars) };
        return text.substr(0, last + 1);
    }

    template<typename CharT>
    inline tstring<CharT> remove(tstring<CharT> text, CharT const letter)
    {
        auto start = std::remove_if(
            std::begin(text), std::end(text), [=](CharT const c) 
            {
                return c = letter;
            });
        text.erase(start, std::end(text));
        return text;
    }

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
    using namespace std::string_literals;

    auto str1 {"  WhicH_uppERCase  "s};
    auto str1_up{ string_lib::to_upper(str1)};
    std::cout << "String commands :"  << std::endl << "\tOriginal: " << str1 
              << std::endl << "\tUpper: " << str1_up << std::endl;


    


}
