// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Did you know that you may have performance issue by using strings? It is
 * because in the process of using strings, some temporals appear for copying
 * processes. To prevent this, you can use since C++17 the 
 * std::basic_string_view which refers to a non owning constnat reference to a
 * string, so you can pass a parameter to a function in a better way.
 * 
 * For this purposes, you may neeed the string_view header.
 * 
 * Keep in mind that string_view can be used for: 
 * 
 *  - typedef basic_string_view<char>     string_view;
 *  - typedef basic_string_view<wchar_t>  wstring_view;
 *  - typedef basic_string_view<char16_t> u16string_view;
 *  - typedef basic_string_view<char32_t> u32string_view;
 * 
 * It defines a reference to a constant contiguous sequence of characters, it
 * can only view the string, so no modifications are allowed. And this type
 * of data is smaller as it is only a pointer.
 * 
 * NOTE: You cannot convert from basic_string_view to basic_string. But you
 * can create your own constructor explictly. 

*/

#include <string>
#include <string_view>

std::string_view get_name(std::string_view word);

int main()
{
    // Info #1: Passing an argument as a string view. Do not forget to check 
    // Keep in mind that the path provided is for Windows as it uses "\\", you
    // can make it valid to Linux by changing it to "/".
    
    char const file[] {R"(c:\\Docs\\example1.txt)"};
    auto filename1 = get_name(file);

    std::cout << "Path: " << file << std::endl
              << "Name of file: " << filename1 << std::endl;

    return 0;
}

/**
 * Obteain the name of a file, bu considering a windows path provided as an
 * argument, the argument uses string view, so no copy is made during the 
 * process.
 * 
 * @param word Path provided to check the name of the file
 * 
 * @return String or char array of the name of the file (without extension).
*/
std::string_view get_name(std::string_view word)
{
    auto const index1 {word.find_last_of(R"(\)")};
    auto const index2 {word.find_last_of('.')};
    return word.substr(index1 + 1, index2 - index1 - 1);
}