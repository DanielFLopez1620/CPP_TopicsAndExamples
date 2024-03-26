// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

/**
 * When you have class you must implement special members like constructors,
 * destructors and assignment operators that have default, compiler and user
 * implementations, in this last implementation, you should think how to 
 * prevent bugs, optimize memory, avoid copying and others. And C++11 came
 * with some feature to do it. Before moving, keep an eye on this:
 * 
 * - Special members are the default constructor, destructur, copy constructor,
 *   move constructor, copy assignment operator, move assignment operator.
 * - When we say copy, we refer to using the copy constructor and assignment to
 *   make possible a copy.
 * - When we say move, we refer to using move constructor and move assignment
 *   so it is possible to move and object.
 * 
 * Now, let's mention some handler option to functions:
*/

class MySetOfFuncs
{
public:
    MySetOfFuncs (std::string name)
    {
        std::cout << "Method made by: " << name << std::endl;
    }
    
    MySetOfFuncs() = default;
};

int main(int argc, char** argv)
{
    // Info #: Calling the constructors implementations.
    MySetOfFuncs a;           // Default
    MySetOfFuncs name("Dan")  // Parameterized constructor
    return 0;
}