// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Enumerations underlyne integral types by creating collections. And their
 * named values are called enumerators, and when you use only the keyword
 * 'enum' they are considered to be unscopred, while by adding 'enumc class'
 * or 'enu struct' the convert to scoped enumerations that were introduced
 * in C++11.
 * 
 * It is better to use scoped enumerations due to issues related with name
 * clashes, and it is not possible to use fully qualified names, the reason of
 * this two is related with the name resolve and enumerated value in 
 * compilance. Another point for this it is becasue of enumerations being ints
 * they ca be used in not proper context, for example, numeric operations.
 * 
 * Thenm the implementations of scoped enumerations aims to generator
 * enumerators that aren't exported, preventing name collisions. You can even
 * assign underlying values to the scoped enumerations. Check the code below to
 * understand the different cases.
 * 
 * When you are ready, you can run the code with:
 * 
 *      g++ -std=c++20 L06_scoped_enum.cpp -o scop_enum.out
 *      ./scop_enum.out
 * 
*/

// --------------------- CUSTOM DEFINITIONS -----------------------------------

// Info #1: Declaration of scoped enumerations with classes and structs
enum class Grade {First, Second, Third };
struct Reports
{
    enum class Report { Disapproved, Approved, Honorific};
    using enum Report;
};

// Info #2: You can specify the underlying type of the enumerations and 
// assign values at your convenience.
enum class Plants : unsigned int;
void value_of_plant(Plants const plant) {}
enum class Plants : unsigned int
{
    ROSEMARY = 0,
    CALENDULA = 1,
    CHAMOMILE = 0x00000FFFU
};


// --------------------- FUNCTION PROTOTYPES ----------------------------------
void display_grade(Grade current_grade);

// --------------------- MAIN IMPLEMENTATIONS ---------------------------------

int main(int argc, char* argv[])
{
    // Info # 3: Using local scoped enumerations identifier in the local scope
    using Grade::Third;
    Grade my_grade = Third;
    Reports::Report rep = Reports::Honorific;
    std::cout << "My Grade: ";
    display_grade(my_grade);

    // Info #4: You can use the enumerations as integers, but there are no 
    // longer implicit conversion of them. So you will have to create an 
    // explicit cast.
    int casted = static_cast<int>(Grade::Third);
    std::cout << "Static Cast of Grade Third is: " << casted << std::endl;

    return 0;
}

void display_grade(Grade current_grade)
{
    switch(current_grade)
    {
        using enum Grade;
        case First:
            std::cout << "First Grade "<< std::endl;
            break;
        case Second:
            std::cout << "Second Grade "<< std::endl;
            break;
        case Third:
            std::cout << "Third Grade "<< std::endl;
            break;
        default:
            std::cout << "Unknown grade" << std::endl;
    }
}