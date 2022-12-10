// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>
#include <vector>
#include <map>

// ---------- FUNCTION'S PROTOTYPES:
std::vector<char> moves();
std::multimap<int, char> odds();

int main()
{
    std::cout << "Lesson 09: Using 'for each' in C++" << std::endl;

    /*
     * FOR EACH: Loop that consists in repeating over the elements of a 
     * collection until it's over. This was added in C++11.
     * Usage: for (<range_declaration> : <range_expression ) { <statment> }
     * 
     * Let's see some examples...
     */

    // By committing to specific type:
    auto movements = moves();
    std::cout << "(Specific type) Available movements with keys: " << std::endl;
    for (char move : movements)
        std::cout << move << std::endl;

    // By letting the compiler to deduce the type:
    std::cout << "(Compiler deduced) Available moves are:" << std::endl;
    for (auto&& auto_move : moves())
        std::cout << auto_move << std::endl;
    
    // By using structured bindings and descomposition (C++17)
    std::cout << "(Structured bindings): Displaying a map for odds" << std::endl;
    for (auto&& [num, opt] : odds())
        std::cout << num << " : " << opt << std::endl;
    
    return 0;
}

// ----------- FUNCTION'S DEFINITIONS:
std::vector<char> moves()
{
    return std::vector<char> {'a', 'w', 's', 'd'};
}
std::multimap<int, char> odds()
{
    return std::multimap<int, char> 
    {
        { 1, 'o'},
        { 2, 'e'},
        { 3, 'o'}
    };
}