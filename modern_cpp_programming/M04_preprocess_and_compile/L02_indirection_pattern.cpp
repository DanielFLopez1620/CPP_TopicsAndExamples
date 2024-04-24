// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * To give more details, the '#' symbol we used for the defintions and
 * conditions presented in the previous lesson, is called 'stringizing
 * operator'. But we have the operand '##' too, that is called 'token-pasting',
 * 'merging' or 'concatenating operator'. 
 * 
 * Here we will check more forms of definitions that can be considered with
 * the preprocesor.
 * 
*/

#define MAKE_WORD2(w)   #w

#define MAKE_WORD(w)    MAKE_WORD2(w)

#define CONCATENATE2(x, y)  x##y

#define CONCATENATE(x,y)    CONCATENATE2(x,y)

int main(int argc, char* argv[])
{
    std::string { MAKE_WORD(no_string_provieded) };
    std::string { MAKE_WORD2(no_string_provieded) };

    #define MY_NUM 1620

    return 0;
}