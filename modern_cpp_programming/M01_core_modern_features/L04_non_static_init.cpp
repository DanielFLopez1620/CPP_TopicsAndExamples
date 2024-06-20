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
 * Using assignments in constructor isn't efficient as it creates copies 
 * (temporals that are later discarded). Also, if no initilizer is provided in
 * the construct, it will use the default definitions present in the body.
 * 
 * For this process, consider that the non-static members are initialized in the
 * order they were decalred (not the order provided in the constructor), the
 * reverse case happens with destructors. 
 * 
 * So, when using built-int types, you should prefer constructor initializer
 * list. But, keep consisten with your initializations, as there are cases where
 * you cannot use a constructor list initializer:
 * 
 * - In cases that the member has been initialized with pointer 'this'.
 * - Elements with references to each other (complementaries).
 * - Test of inputs params for checking exceptions.
 * 
 * When ready, you can try and explore the code with:
 * 
 *      g++ -std=c++20 L04_non_static_init.cpp -o non_static.out
 *      ./non_static.out
*/
// ----------------- HEADERS AND IMPORTS --------------------------------------
#include <string>   // For string management

// ------------------ TYPES AND DEFINITIONS -----------------------------------
enum class PositionNum {One, Two, Three};
enum class PositionLetter {F1, D2, C3};

/**
 * Basic struct with some intended attributes.
 */
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
    BasicStruct(std::string const & name) : name(name) 
    {
        std::cout << "BasicStruct -> Name user constructor" << std::endl;
    }
    BasicStruct(std::string const & name,
                 PositionNum const pn,
                 PositionLetter const pl):
                 name(name), num(pn), letter(pl) 
    {
        std::cout << "BasicStruct -> Full user constructor" << std::endl;
    }
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
    {
        std::cout << "Label -> User constructor" << std::endl;
    }
};

// Info #5: In case you want to understand better the constructor options, take
// a look to the class below.
struct constructor_check
{
    constructor_check() 
    { std::cout << "CC -> Default constructor" << std::endl; }
    constructor_check(std::string const & text) 
    { std::cout << "CC -> Constructor " << text << std::endl; }
    constructor_check(constructor_check const & other) 
    { std::cout << "CC -> Copy constructor" << std::endl; }
    constructor_check(constructor_check&& other) 
    { std::cout << "CC -> Move constructor" << std::endl; }
    constructor_check& operator=(constructor_check const & other) 
    { std::cout << "CC -> Assignment" << std::endl; return *this; }
    constructor_check& operator=(constructor_check&& other)
    { std::cout << "CC -> Move assignment" << std::endl; return *this; }
    ~constructor_check()
    { std::cout << "CC -> Destructor" << std::endl; }
};

// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 4: Non static initialization...\n" << std::endl;

    // Using our basic structure and the non static initialization
    std::cout << "Check the different constructor usage for BasicStruct: "
              << std::endl;
    auto basic1{ BasicStruct("Dan") };
    auto basic2{ BasicStruct("Dan", PositionNum::Three, PositionLetter::C3) }; 

    // Using Label non-static initialization
    std::cout << std::endl << "Now, let's check the case with label: " 
              << std::endl;
    auto label1 { Label("Dan", 16) };

    // Checking constructor usage
    std::cout << std::endl << "Now, let's experiment with constructors:" 
              << std::endl;
    constructor_check ex1;
    constructor_check ex2{ "Hi!" };
    constructor_check ex3{ ex2 };
    constructor_check ex4 = ex3;

    return 0;
}  // main

