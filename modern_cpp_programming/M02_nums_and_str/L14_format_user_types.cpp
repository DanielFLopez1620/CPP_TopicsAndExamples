// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with C++20 with g++ Version 13

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
 *      g++13 -std=c++20 L14_format_user_types.cpp -o format_t.out
 *      ./format_t.out
*/

// ------------------------ REQUIRED HEADERS ----------------------------------
#include <format>  // For formatting options of strings
#include <string>  // For string management

// ----------------------- STRUCT DEFINITIONS ---------------------------------
// This will be our custom structure type to use (one attribute)
struct element_t
{
    unsigned int id {0};
};

// This will be another custom structure for trying formatting (multi attr)
struct student_t
{
    int id;
    std::string name;
    float mean_grade;
};

// Info #1: Template for implementing the formatter of type student
/**
 * Simple formatter for a one attribute structure.
 */ 
template<>
struct std::formatter<element_t>
{
    // Info #2: Parse takes a single arg that returns a 
    // basic_format_parse_context iterator.
    /**
     * Parse context instruction, to indicate beginning of the operation
     * 
     * @param ctx Reference for format parse context
     * 
     * @return Begin of the context to consider when formating.
     */
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    // Info #3: Format takes two arguments (the object of interest and then
    // the context), and it will write the output (formatted string) to the
    // ctx.out().
    /**
     * Give custom format to one attribute structure, then std::cout operation
     * will be able to understand the format.
     * 
     * @param element Element of interest to display the info
     * @param ctx Format context
     * 
     * @return Formatted output for the structure
     */
    auto format(const element_t& element, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "Element: {}", element.id);
    }

};

/**
 * Simple formatter for a one attribute structure.
 */ 
template <>
struct std::formatter<student_t>
{
    /**
     * Parse context instruction, to indicate beginning of the operation
     * 
     * @param ctx Reference for format parse context
     * 
     * @return Begin of the context to consider when formating.
     */
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    /**
     * Give custom format to one attribute structure, then std::cout operation
     * will be able to understand the format.
     * 
     * @param element Element of interest to display the info
     * @param ctx Format context
     * 
     * @return Formatted output for the multiple attribute structure 
     */
    auto format(const student_t& student, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "Student {} with ID {} has {} score",
                              student.name, student.id, student.mean_grade);
    }
};

// ---------------------- MAIN IMPLEMENTATION ---------------------------------

int main(int argc, char** argv)
{
    std::cout << "Lesson 14: Using format for structs\n" << std::endl;

    // Info #4: Creating an object and using format.
    element_t element { 16 };
    std::cout << std::format("{}", element) << std::endl << std::endl;

    student_t student { 1620, "Dan", 4.5};
    std::cout << std::format("{}", student) << std::endl;

    return 0;
}