// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>
#include <vector>
#include <map>

int main()
{
    // UNIFORM INITALIZATION: Implemented in C++11
    // It removes previous distinction of fundamental, aggregate and non-aggregat type.

    // You know direct initialization, based on constructor:
    std::string direct("Example");

    // And yo also know copy initialization, based on other obj:
    std::string copy = "Example";

    // USAGE of 'Uniform Initialization':
    // For direct-list: <type> <name> {<other>};
    // For copy-list: <type> <name> = {<other>};
    std::vector<char> vowels {'a', 'e', 'i', 'o', 'u'};
    std::map<char, char> vow_case { {'a','A'}, {'e','E'}};
    int* odd = new int[4] {1, 3, 5, 7 };
    float flt { 42 };
    
    // It can also work with user-defined types and POD types like structs.
    // Also remember that POD (Plain Old Data) is deprecated in C++, 
    // better use std layout types.

    // COMBINING WITH AUTO: That will use the 'std::initializer_list<type>':
    auto letter {'d'};
    auto const_list = {3.14, 2.79};

    return 0;
}