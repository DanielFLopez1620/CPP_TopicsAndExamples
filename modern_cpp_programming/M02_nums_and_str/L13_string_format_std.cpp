// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with C++20 with g++ Version 13

#include <iostream>

/**
 * In C++, you can use the inherited printf functions and it can be faster, but
 * streams library provides more safety and extensibility. Moreover, C++20
 * provides a new formatting library, which is called <format>.
 * 
 * The key here is two use {} in order to create the format of variables as 
 * inputs to the strings (if you need to add '{' you will need to use '{{').
 * It also relates with the usage of colon ':' in order to specify format
 * options. Keep in mind that if there is an error in the format, the
 * 'std::format_error' will be raised, for example, if you use more indexes
 * than the ones you provided.
 * 
 * NOTE: For time format info, refer to: 
 *  https://en.cppreference.com/w/cpp/chrono/system_clock/formatter
 * 
 * You can compile this code with:
 *      g++-13 -std=c++20 L13_string_format_std.cpp -o format.out
 *      ./format.out
 * 
 * For this code, you may have to update GCC manually, by installing:
 * 
 *      sudo apt install g++-13
*/


// -------------------- REQUIRED HEADERS --------------------------------------
#include <format>   // Library for a new format option for str
#include <chrono>   // Time management in different precisions
#include <vector>   // For dynamic arrays
#include <ctime>    // For standard time with C Library
#include <iterator> // For iteration of elements
#include <string>   // For word and str formatting 

// ------------------- FUNCTION PROTOTYPES ------------------------------------
std::string format_time(const std::tm& tm);

// -------------------- MAIN FUNCTION -----------------------------------------
int main(int argc, char** argv)
{
    std::cout << "\nLesson 13: Using std::format....\n" << std::endl;

    // Info #1: Providing arguments in new format.
    auto text1 = std::format("My name is {} {} ", "Dan", 1620);
    std::cout << "\nFormatted output: " << text1 << std::endl;
    
    // Info #2: Providing arguments with order.
    auto text2 = std::format("My name is {1} {0}", "Dan", 1620);
    std::cout << "\nChanged order of params: " << text2 << std::endl;

    // Info #3: You can specify format of numbers with ':'.
    auto num_hex = std::format("{0} equivalent hex is {0:08X}", 16);
    std::cout << "\nPrinting a number: " << num_hex << std::endl;

    // Info #4: You can specify time display properties related with chronos.
    auto now = std::chrono::system_clock::now();
    auto time_got = std::chrono::system_clock::to_time_t(now);
    auto time_str = std::format("Date: {}", format_time(*std::localtime(&time_got)));
    std::cout << "\nPrinting chrono time: " << time_str << std::endl;

    // Info #5: Writing buffers from std::format to std::string.
    std::vector<char> buffer;
    std::format_to(std::back_inserter(buffer), "{} + {}", "Dan", 1620);
    std::cout << "\nUsing buffer: " 
              << std::string(buffer.data(), buffer.size()) << std::endl;

    // Info #6: Considering the size of std::format for buffers and prevent
    // extra characters in buffer.
    auto text3 = std::format("{} {} is playing.", "Dan", 1620);
    std::vector<char> buffer2(text3.size());
    std::format_to(buffer2.data(),"{}", text3);
    std::cout << "\nUsing another buffer for format: "
              << std::string(buffer2.data(), buffer2.size()) << std::endl;

    // Info #7: Using format options to fill with characters.
    //  < : Forces left align
    //  > : Forces right align
    //  ^ : Centered according available spaces.
    //  + : Sign must be used for both negative and positive nums.
    //  - : Sign only for negatives.
    //  # : For alternative form.
    // Keep in mind that the order for the format should be:
    // fill-align, width, precision, chrono-spec
    // Finally, some special characters combinatations are:
    //  %% : Print a %
    //  %n : Newline char
    //  %t : Tab char
    //  %Y : Year as a decimal.
    //  %m : Month as a decimal.
    //  %d : Day as a decimal.
    //  %w : Write weekday (0 is Sunday).
    //  %D : Equivalent to %m/%d/%Y
    //  %F : Equivalent to %Y-%m-%d
    //  %I : For 12 hours clock.
    //  %M : Minutes as decimal.
    //  %S : Seconds as decimal.
    //  %T : Equivalent to %H:%M:%S
    //  %X : Writes the locale's time representation.

    auto txt1 = std::format("{:5}", 16);
    auto txt2 = std::format("{:*<5}", 'D');  // Left align
    auto txt3 = std::format("{:*>5}", 'D');  // Right align
    auto txt4 = std::format("{:*^5}", 'D');  // Centered
    auto txt5 = std::format("{0:+}", 16);
    auto txt6 = std::format("{:#05x}", 16);

    std::cout << "\nFinally, using align with format:" << std::endl
              << "Numeric align: " << txt1 << std::endl
              << "Text left align: " << txt2 << std::endl
              << "Text right align: " << txt3 << std::endl
              << "Centered align: " << txt4 << std::endl
              << "Num with sign: " << txt5 << std::endl
              << "Hex num: " << txt6 << std::endl;


    return 0;
} // main

// ---------------------- FUNCTION DEFINITIONS --------------------------------

/**
 * For formatting time tm structs
 * 
 * @param tm Time struct to consider
 * 
 * @return Char buffer for printing after conversion
 */
std::string format_time(const std::tm& tm)
{
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return buffer;

} // format_time

