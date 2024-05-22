// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * C++ during a lot of time didn't have a 'for each' implementation to iterate
 * over arrays, list, vectors and more. Originally, it was made with a general
 * purpose algorithm called std::for_each, but after C++11 now there is an
 * option to implement for iterating loops better, its own 'for each'.
 * 
 * Behind, in compilation, the equivalent of the for each uses the next
 * structure: 
 * 
 *      // Before C++17
 *      {
 *        auto && __range = range_expression;
 *        for (auto __begin = begin_expr, __end = end_expr;
 *        __begin != __end; ++__begin) {
 *          range_declaration = *__begin;
 *          loop_statement
 *        }
 *      }
 * 
 *      // After C++17
 *      {
 *        auto && __range = range_expression;
 *        auto __begin = begin_expr;
 *        auto __end = end_expr;
 *        for (; __begin != __end; ++__begin) {
 *          range_declaration = *__begin;
 *          loop_statement
 *        }
 *      }
 *      
 *      
 * Where __range and __bound allow to know the number of elements in the array,
 * __begin and __end ensure you do not access to memory not related to the
 * array, and the loops statement is the loop process. Note that after C++17
 * the __begin and __end doesn't have to be of the same type, then a range can
 * be delimited by a predicate, and as end is only evaluated once, it increase
 * the performance.
 * 
 * You can run this code with:
 * 
 *      g++ -std=c++20 L08_range_fors.cpp -o foreach.out
 *      ./foreach.out
 * 
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
    std::cout << std::endl << std::endl << "Map (Char, integer): ";
    std::map<char, int> my_map { {'a', 1}, {'b', 2}, {'c', 3}};
    for( auto &&[letter, num] : my_map)
    {
        std::cout << "(" << letter << ", " << num << "), ";
    }
    std::cout << std::endl;

    return 0;
}