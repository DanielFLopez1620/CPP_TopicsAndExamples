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
 * Check the implementation in this code below.
 * 
 * You can compile this code with:
 *      g++ -std=c++20 L14_format_user_types.cpp -o format_t.out
 *      ./format_t.out
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

// Info #1: Template for implementing the formatter of type student 
template <>
struct std::formatter<student_t>
{
    // Info #2: Parse takes a single arg that returns a 
    // basic_format_parse_context iterator.
    constexpr aut parse(format_parse_context& ctx)
    {
        return ctx.begin();
    } 

    // Info #3: Format takes two arguments (the object of interest and then
    // the context), and it will write the output (formatted string) to the
    // ctx.out().
    auto format(student_t const & student, format_context& ctx)
    {
        return std::format_to(ctx.out(), "Student {} with ID {} has {} points",
            student.id, student.name, student.mean_grade);
    }
};

int main(int argc, char** argv)
{
    // Info #4: Creating an object and using format.
    student_t stu{ 16, "Dan", 4.8};
    auto report = std::format("{}", stu);
    return 0;
}