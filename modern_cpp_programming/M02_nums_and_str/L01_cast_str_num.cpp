// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

int main(int argc, char** argv)
{
    // Casting between string and nums wasn't easy before C++11, and the
    // convertion is possible by functions in the '<string>' header.
    // You can compile this code, with:
    //  g++ -std=c++11 L01_cast_str_num.cpp -o L01_cast_str_num.out


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
    auto str_to_num_1 = std::stoi("16");
    auto str_to_num_2 = std::stol("16201620");
    auto str_to_num_3 = std::stoi("0x2F", nullptr, 16);

    std::cout << "String to integer: " << str_to_num_1 << std::endl;
    std::cout << "String to long int: " << str_to_num_2 << std::endl;
    std::cout << "String to hex interpret: " << str_to_num_3 << std::endl;

    return 0;
}