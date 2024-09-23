// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * In the module 2 we explored about std::string_view as an option for 
 * considering a string based on the contiguous sequences of characters,
 * this was added in C++17. But it is just one of the cases that could be used
 * with contiguous sequences, and that is the reason why C++20 came with
 * std::span as it allows to acess contiguous sequences of objects.
 * 
 * You will require the <span> header.
 * 
 * This aims to change the C-like interfaces of:
 *      
 *      void func(int* buffer, size_t length) { ... }
 *
 * With the option below:
 * 
 *      void func(std::span<int> buffer) { ... }
 */

#include <span>

int main(int argc, char* argv[])
{
    // Info #1: You can declare an span based on a vector/array/container
    // in a static way (defined size in compile time) or dynamic way (size is
    // obtained in runtime).
    float num_array[] = { 16.0 , 20.0, 16.20, 20.16};
    std::span <float, 4> stc_extent {num_array};
    std::span <float> dyn_extent {num_array};

    // Info #2: You can combine boht static and dynamic extent span and
    // use then with a for each.
    std::cout << "Using span with for each: " << std::endl
              << "\tStatic extent: (";
    for(auto const n : stc_extent)
    {
        std::cout << n << ", ";
    } 
    std::cout << ")" << std::endl;
    std::cout << "\tdynamic extent: (";
    for(auto const n : dyn_extent)
    {
        std::cout << n << ", ";
    }
    std::cout << ")" << std::endl;

    // Info #3: For accessing the element of a span you can use operator[] (as
    // usual), or the methods front(), back(), data().
    std::cout << "Accessing elements of a span: " << std::endl
              << "\tFirst element: " << stc_extent.front() << std::endl
              << "\tLast element: " << stc_extent.back() << std::endl
              << "\tThird element: " << stc_extent[2] << std::endl;

    // Info #4: You can obtain sub spans when using first(), last() or 
    // subspan() methods.
    std::span<float> first_2 = stc_extent.first(2);
    std::span<float> last_2 = stc_extent.last(2);
    std::span<float> mid_2 = stc_extent.subspan(1,1);
    return 0;
}