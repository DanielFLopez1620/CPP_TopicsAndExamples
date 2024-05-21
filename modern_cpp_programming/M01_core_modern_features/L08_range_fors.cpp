// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * C++ during a lot of time didn't have a 'for each' implementation to iterate
 * over arrays, list, vectors and more. Originally, it was made with a general
 * purpose algorithm called std::for_each, but after C++11 now there is an
 * option to implement for iterating loops better, its own 'for each'.
*/

#include <vector>
#include <map>

int main(int argc, char* argv[])
{
    // Info #1: The implementation of the for each in C++ is:
    //     for ( <element> : <range> ) <loop_statement>
    // In the element, you have to specify a type, but you can simply use auto,
    // just keep in mind that if you need a specific type it is better to
    // define it. 
    std::cout << "Floating numbers: ";
    std::vector<float> my_nums {1.6, 6.2, 2.0};
    for ( auto num : my_nums)
    {
        std::cout << num << ", ";
    }
    std::cout << "Map (Char, integer): ";
    std::map<char, int> my_map { {'a', 1}, {'b', 2}, {'c', 3}};
    for( auto &&[letter, num] : my_map)
    {
        std::cout << "( " << letter << ", " << num << "), ";
    }
    std::cout << std::endl;

    

    
    return 0;
}