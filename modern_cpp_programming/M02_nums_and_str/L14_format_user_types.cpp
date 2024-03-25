// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was not testedm but must be run with g++ in C++20

#include <iostream>

/**
 * As you discover in the previous lesson, <format> creates an alternative to
 * printf with better format options to the basic types. But it can also work
 * with custom types, like the user defined ones.
 * 
 * For this, you will need to define a specialization of the std::formatter
 * template, then implement a parse method and a finally a format method.
*/

#include <format>
#include <string>

// This will be our custom structure type to use
struct student_t
{
    int id;
    std::string name;
    float mean_grade;
};

int main(int argc, char** argv)
{
    return 0;
}