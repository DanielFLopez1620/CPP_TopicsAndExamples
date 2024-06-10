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
 * of data is smaller as it is only a pointer. Additionally, the passing a
 * string_view can still create temporaries, but the impact is pretty less than
 * allatocations at the heap and copying.
 * 
 * NOTE: You cannot convert from basic_string_view to basic_string. But you
 * can create your own constructor explictly. 
 * 
 * You can run this code with:
 *      g++ -std=c++17 L12_string_view.cpp -o str_view.out
 *      ./str_view.out
*/

// -------------------- REQUIRED HEADERS --------------------------------------
#include <string> 
#include <string_view>

// -------------------- FUNCTION PROTOTYPES -----------------------------------
std::string_view get_name(std::string_view word);
std::string_view trimming(std::string_view text);

// -------- ------------- MAIN IMPLEMENTATION ---------------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 12: About string_view...\n" << std::endl;
    
    // Info #1: Passing an argument as a string view. Do not forget to check 
    // Keep in mind that the path provided is for Windows as it uses "\\", you
    // can make it valid to Linux by changing it to "/".
    
    char const file[] {R"(c:\\Docs\\example1.txt)"};
    auto filename1 = get_name(file);

    std::cout << "Path: " << file << std::endl
              << "Name of file: " << filename1 << std::endl << std::endl;

    // Info #2: Using string_view and the converting to string.
    std::string_view str_vw { "preview" };
    std::string normal_str{ str_vw };

    std::cout << "String view:" << str_vw << std::endl
              << "String basic: " << normal_str << std::endl << std::endl;

    // Info #3: You can use two addtional methods when using string_view, they
    // are remove_prefix() and remove_suffix(), illustrated below with a custom
    // function, so do not forget to check it.

    auto text_to_trim { "  trim here     " };
    auto text_trimmed{ trimming(text_to_trim) };

    std::cout << "Text to trim: {" << text_to_trim << "}" << std::endl
              << "Text trimmed: {" << text_trimmed << "}" << std::endl;

    return 0;
}

// -------------------- FUNCTION DEFINITIONS ----------------------------------

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

}  // get_name

/**
 * Function that trimms spaces considering them suffix and prefix, so it return
 *  a string with no additional spaces.
 * 
 * @param text Sting to trim additional spaces
 * 
 * @return Trimmed string with no additional spaces as suffix or prefix.
*/
std::string_view trimming(std::string_view text)
{
    auto const ini{ text.find_first_not_of(" ") };
    auto const end{ text.find_last_not_of(" ") };
    text.remove_suffix(text.length() - end - 1);
    text.remove_prefix(ini);
    return text;

} // trimming