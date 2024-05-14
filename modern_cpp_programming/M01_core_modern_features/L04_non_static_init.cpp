// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Here we will discover about default member initialization.
 * 
 * In the basic structure, you can check some examples of the members
 * initialization, but keep in mind that you have to use assignments in
 * constructos when the options presented aren't possible.
 * 
*/

#include <string>
#include <chrono>
#include <thread>

// ------------------ TYPES AND DEFINITIONS -----------------------------------
enum class PositionNum {One, Two, Three};
enum class PositionLetter {F1, D2, C3};

struct BasicStruct
{
    std::string name;

    // Info #1: Default member initialization for constants (static or 
    // non-static
    int First = 1;
    const char Second = 'b';

    // Info #2: For member clases with multiple constructors that would use a
    // common initializer for those members.
    PositionNum num = PositionNum::One;
    PositionLetter letter = PositionLetter::D2;

    // Info #3: Constructor initialization for members that don't have default
    // values, but depend on parameters.
    BasicStruct(std::string const & name) : name(name) {}
    BasicStruct(std::string const & name,
                 PositionNum const pn,
                 PositionLetter const pl):
                 name(name), num(pn), letter(pl) {}
};

// Info #4: A simple struct with non-static data members initialization in the
// constructor list initialization is provided below:
struct Label
{
    // Attributes
    std::string name;
    int ID;

    // Initializer
    Label(std::string const name = " ", int const ID = 0) : name(name), ID(ID)
    {}
}

int main(int argc, char* argv[])
{

    return 0;
}

