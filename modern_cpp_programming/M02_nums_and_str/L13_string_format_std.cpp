// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was not testedm but must be run with g++ in C++20

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
 *      g++ -std=c++20 L13_string_format_std.cpp -o format.out
 *      ./format.out
*/

// #include <fmt/core.h>
#include <format>
#include <chrono>
#include <vector>

int main(int argc, char** argv)
{
    // Info #1: Providing arguments in new format.
    auto text1 = std::format("My name is {} {} ", "Dan", 1620);
    std::cout << text1 << std::endl;
    
    // Info #2: Providing arguments with order.
    auto text2 = std::format("My name is {1} {0}", "Dan", 1620);

    // Info #3: You can specify format of numbers with ':'.
    auto num_hex = std::format("{0} equivalent hex is {0:08X}", 16);
    std::cout << "Number: " << hum_hex << std::endl;

    // Info #4: You can specify time display properties related with chronos.
    auto now = std::chrono::sysmet_clock::now();
    auto time_got = std::chrono::system_clock::to_time_t(now);
    auto time_str = std::format("Date: {:{%Y-%m-%d}}", 
        *std::localtime(&time_got));

    // Info #5: Writing buffers from std::format to std::string.
    std::vector<char> buffer;
    std::format_to(std::back_inserter(buffer), "{} + {}", "Dan", 1620);

    // Info #6: Considering the size of std::format for buffers.
    auto text3 = std::format("{}{} is playing.", "Dan", 1620);
    auto size = std::formatted_size(text3);
    std::vector<char> buffer2(size);
    std::format_to(size.data(), text3);

    // Info #7: Prevent extra characters in buffers:
    char buffer3[100];
    auto result = std::format_to_n(buffer3, sizeof(buffer3), text3);

    // Info #8: Using format options to fill with characters.
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

    std::cout << "Numeric align: " << txt1 << std::endl
              << "Text left align: " << txt2 << std::endl
              << "Text right align: " << txt3 << std::endl
              << "Centered align: " << txt4 << std::endl
              << "Num with sign: " << txt5 << std::endl
              << "Hex num: " << txt6 << std::endl;


    return 0;
}



