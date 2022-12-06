// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>
#include <string>
#include <chrono>
#include <thread>


// ------ CLASS DEFINITIONS:
enum class PositionNum {One,  Two, Three};
enum class PositionLetter {F1, S2, S3};

// ------- STRUCT DEFINITIONS:

// DEFAULT MEMBER INITIALIZATION...
struct basic
{
    //  For constants (static and non-static):
    const int First = 1;
    const char Second = 'b';

    std::string name;

    // For member of classes with multiple constructors:
    PositionNum num = PositionNum::One;
    PositionLetter let = PositionLetter::S2;

    // To initialize members that does not have default values:
    basic(std::string const & text) : name(text)
    { }
    basic(std::string const & text,
        PositionNum const pn,
        PositionLetter const pl):
        name(text), num(pn), let(pl)
    { }
};

// ORIGINAL INITIALIZATION WITH CONSTRUCTOR'S INITIALIZER LIST 
struct original
{
    float X, Y;

    // NOTE: Remember to keep the order of declaration while the initialization
    original (float const x = 0.0, float const y = 0.0) : X(x), Y(y) {}
};
// COMPARATIVE BETWEEN THE TWO FORMS:
struct common
{
    common () { std::cout << "Case: Default Constructor" << std::endl; }
    common (std::string & message) {std::cout << "Case: " << message << "Constructor " <<std::endl;}
    common (common const & copy) { std::cout << "Case: Copy Constructor" << std::endl;}
    common& operator=(common const & copy) { std::cout << "Case: Assignament" << std::endl; return *this; }
    common& operator=(common && copy) { std::cout << "Case: Move assignament" << std::endl; return *this; }
    ~common () { std::cout << "Case: Destructor" << std::endl; }
};

struct review1
{
    common com;
    
    review1 (common const & example)
    {
        com = example;
    }
};
struct review2
{
    common com;
    
    review2 (common const & example) : com(example) {}
};

int main()
{
    // Results for different initializations:
    std::cout << "First results: "<< std::endl;
    common com1;
    review1 example1(com1);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Second results: "<< std::endl;
    common com2;
    review2 example2(com2);

    return 0;
}