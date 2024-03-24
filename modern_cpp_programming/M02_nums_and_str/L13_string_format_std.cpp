// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was not testedm but must be run with g++ in C++20

#include <iostream>

/**
 * In C++, you can use the inherited printf functions and it can be faster, but
 * streams library provides more safety and extensibility. Moreover, C++20
 * provides a new formatting library, which is called <format>.
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
    auto result = std::format_to_n(buffer3, sizeof(buffer3), text3)

    return 0;
}



