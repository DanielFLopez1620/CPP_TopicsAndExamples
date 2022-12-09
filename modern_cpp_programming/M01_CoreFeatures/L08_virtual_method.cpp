// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include<iostream>

/* 
 * Note: C++ does no tha ve a specific syntax for declaring interfaces.
 * Virtual methods are used with 'virtual' keyword, but this is optional 
 * which can lead to confussions in classes.
 * 
 * Some tips when declaring and managin virtual functions are:
 * - Always try to use 'virtual' for the virtual functions in a derived class.
 * - Always use 'override' after the declaration of a virtual function.
 */

// ----------- Classes Declaration:
// Usual Declaration:
class VirtualityOr
{
    public:
        virtual void member(char const & let) {return;}    
};
class DerivedOr : public VirtualityOr
{
    public:
        virtual void member(char const let) {return;}
};

// Another example:
class VirtualityCp
{
    virtual void member() = 0;
    virtual void addition() { return; }
};
class DerivedCp1 : public VirtualityCp
{
    virtual void member() override = 0;
    virtual void addition() override { return; }
};
// Ensure no more overrides or derivates:
class DerivedCp2 : public DerivedCp1
{
    virtual void member() final {}
};


int main()
{
    std::cout << "Refer to code: Virtual methods with final and override.\n";
    return 0;
}