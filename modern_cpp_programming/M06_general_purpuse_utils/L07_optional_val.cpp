// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Have you ever wondered how can you make the returns in a function
 * according to a case? No, well, have you ever tried to return keys of a 
 * dictionary, but when you do not find one you end up depending on
 * exceptions rather that error codes?
 * 
 * In that case, or just if you are curious, after C++17 std::optional
 * was added to store values that may or may not exist. It is present
 * in the <optional> header.
 * 
 * 
 * 
 */

#include <optional>

struct custom_struct
{
    int num;
    char letter;
};

int main(int argc, char *argv[])
{
    // Info #1: You can create an optional value by using assing, the 
    // default constructor and the copy constructor, just remember that for
    // printing you have to use the member function value():
    std::optional<int> opt_num1;
    opt_num1 = 16;
    std::optional<float> opt_num2 = 4.2;
    std::optional<float> opt_num3 = opt_num2;
    std::cout << "Creating optional values: " << std::endl
              << "\tDefault, then assign: " << opt_num1.value() << std::endl
              << "\tAssign value: " << opt_num2.value() << std::endl
              << "\tCopy optional: " << opt_num3.value() << std::endl; 

    // Info #2: To read the stored values, you can use  operator* or 
    // operator*
    std::optional<custom_struct> opt_struct{ custom_struct{16, 'd'}};
    std::cout << "Reading the values of the optional variables: " << std::endl
              << "\topt_num1: " << *opt_num1 << std::endl
              << "\topt_struct: (num = " << opt_struct->num << ") (letter = "
              << opt_struct->letter << ")" << std::endl;
    
    // Info #3: You already know that you can use value, to access the value of
    // a given optional value, but if the optional value is empty, what will it
    // show? For this cases, you can use the member function "value_or(<str>)"
    // to specify what to show (a default) in case there is no type in the opt.
    std::optional<int> opt_num4 {1620};
    std::optional<int> opt_num5;
    std::optional<std::string> opt_str;
    std::cout << "Displaying the value, but checking content: " << std::endl
              << "\topt_num4: " << opt_num4.value_or(0) << std::endl
              << "\topt_num5: " << opt_num5.value_or(0) << std::endl
              << "\topt_str1: " << opt_str.value_or("Empty") << std::endl;

    return 0;
}