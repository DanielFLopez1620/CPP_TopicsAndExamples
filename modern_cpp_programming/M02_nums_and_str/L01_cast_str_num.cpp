// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

/**
 * Casting between string and nums wasn't easy before C++11, and the
 * convertion is possible by functions in the '<string>' header.
 * You can compile this code, with:
 * 
 *      g++ -std=c++11 L01_cast_str_num.cpp -o cast_str_num.out
 *      ./cast_str_num.out
 * 
 * For more info, you can check on: 
 *      https://en.cppreference.com/w/cpp/language/floating_literal
*/

// ----------------- MAIN IMPLEMENTATION --------------------------------------

int main(int argc, char** argv)
{
    std::cout << "Lesson 1: Casting between numeric and string types...\n"
              << std::endl;

    // INFO #1: Convertion of int or float to str, by using:
    // - std::to_string(n) -> Convert to basic string (with char of 8-bit)
    // - std::to_wstring(n) -> Conver to w_char array (wide character of 4 bytes)
    // Where 'n' is a number (interger or float)
    auto num_int_1 = std::to_string(16);
    auto long_int_2 = std::to_string(20L);
    auto unsign_int_3 = std::to_string(1620u);
    auto num_flt_1 = std::to_wstring(16.20);
    auto num_flt_2 = std::to_wstring(16.20L);

    std::cout<<"Integer to string: " << num_int_1 << std::endl;
    std::cout<<"Long integer to string: " << long_int_2 << std::endl;
    std::cout<<"Unsigned integer to string: "<< unsign_int_3 << std::endl;
    std::wcout<<"Float to string: " << num_flt_1 << std::endl;
    std::wcout<<"Long float to string: " << num_flt_2 << std::endl;

    // INFO #2: Convert string to int by using:
    // - std::stoi(s, ptr) -> String to integer.
    // - std::stol(s, ptr) -> String to long integer.
    // - std::stoll(s, ptr) -> String to long long integer.
    // - std::stoul(s, ptr) -> String to unsigned long int.
    // - std::stoull(s, ptr) -> String to unsigned long long int.
    // s is the str and prt is an internal prt to the conversion functions.
    auto str_to_num_1 = std::stoi("16");
    auto str_to_num_2 = std::stol("16201620");
    auto str_to_num_3 = std::stoi("0x2F", nullptr, 16);

    std::cout << "String to integer: " << str_to_num_1 << std::endl;
    std::cout << "String to long int: " << str_to_num_2 << std::endl;
    std::cout << "String to hex interpret: " << str_to_num_3 << std::endl;

    // INFO #3: Convert string to float by using:
    // - std::stof(s, ptr) -> String to float.
    // - std::stod(s, ptr) -> String to double.
    // - std::stold(s, ptr) -> String to long double.
    // s is the str to convert and prt is an internal ptr to the convert func.
    auto str_to_flt_1 = std::stof("16.20");
    auto str_to_flt_2 = std::stod("16.20e+2");
    
    std::cout << "String to float: " << str_to_flt_1 << std::endl;
    std::cout << "String to double: " << str_to_flt_2 << std::endl;

    // INFO #4: The convertion from string to a number discard whitespaces and
    // take the major number of characters to form the number. Also, you
    // can use prefix 0 to indicate octal base and 0x for hex.
    auto num_case_1 = std::stoi("    16");
    auto num_case_2 = std::stoi("  -16sixteen");

    std::cout << "Conversion 1 (strange): " << num_case_1 << std::endl;
    std::cout << "Conversion 2 (strange): " << num_case_2 << std::endl;

    // INFO #5: If the conversion cannot be achieved, it will return an
    // exception. Another possible error is out of range.
    // Keep in mind that you can use some special keywords to use in the
    // conversions:
    // e - E: For exponential usage.
    // 0x - 0X: For hex usage.
    // INF - INFINITY: For infinity expression.
    // NAN: Non number expression.

    try
    {
        // No number detected
        auto error_num = std::stoi("");
    }
    catch (std::exception const& e)
    {
        std::cout << "Invalid argument: "<< e.what() << std::endl;
    }

    try
    {
        // Invalid size for (normal) integer
        auto error_num = std::stoi("9999999999999");
    }
    catch(const std::exception& e)
    {
        std::cerr << "Out of bounds: " <<e.what() << '\n';
    }

    return 0;

} // main