// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Query object alignment refers to the alignment requirements imposed on
 * memory allocated for query objects in a computer program, in other words, 
 * the memory adress at which objects are stored, and it depends on the 
 * constraints according the data type. This aims to memory efficient and
 * proper data manipulation.
 * 
 * C++11 provided standardized mehtods for specifying this (previously it was
 * possible only with compiler methods). It was implemented in the way to boost
 * performance because it is not the same to work with an Intel SSE than a 
 * SSE2. The commands of interest of this section are 'alignof' and 'alignas'.
 * 
 * 
*/

// Info #1: Alignas can be used to control the alignment of a type in both,
// class level or data member level, keep in mind it must be consistent with
// the types you are using and the purpose of the implementation. 
struct alignas(4) double_char
{
    char l1;
    char l2;
};
struct access
{
    alignas(2) char type;
    alignas(8) unsigned int id;
};


int main(int argc, char* argv[])
{
    // Info #2: To query or get the alignment of a type, you use 'alignof'
    // operator, remember to use auto for better type deduction.
    auto double_char_align = alignof(double_char);

    return 0;
}