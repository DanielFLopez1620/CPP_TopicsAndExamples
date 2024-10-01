// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * In the previous lesson we explored about type trait, but what if I told you
 * that you can create your own?
 * 
 * For this purpose, this example is based on multiple classes that allow
 * serialization with different types and precisions, then you can create
 * a uniform API for serialize the types. 
 */


struct plain_text
{
    std::string serial()
    {
        return "serialized";
    }
};

struct encoded_text
{
    std::string serial_encoded()
    {
        return "encoded";
    }
};