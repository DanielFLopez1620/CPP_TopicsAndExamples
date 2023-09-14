// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with g++

#include <iostream>

/**
 * We have already check abstraction in C, now take a look what C++ can do with
 * 'pure virtual' functions.
 * 
 * So, do no forget to check the differences between the approach in C and the one
 * exposed here.
*/

enum class Movement {Aerical, Ground, Acuatic};

class Vehicle
{
public:
    virtual Movement GetMove() = 0;
};

class Car : public Vehicle
{
public:
    Movement GetMove() override
    {
        return Movement::Ground;
    }
};