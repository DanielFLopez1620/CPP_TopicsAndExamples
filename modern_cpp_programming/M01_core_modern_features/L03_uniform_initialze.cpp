// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Do you know about brace-initialization? It was introduced in C++ and later
 * called uniform initialization. You will check some comparation thoughout
 * this code for what a proper initialization should be and how can they be
 * improved.
*/

int main(int argc, char* argv[])
{
    // Info #1: There are two types of initialization, one that is make direct
    // by using braces and other that is based on a copy.
    std::string text1("direct");
    std::string text2 = "copy";
    std::cout << "Text1: " << text1 << " initialization" << std::endl
              << "Text2: " << text2 << " initialization" << std::endl;

    // Info #2: But, we want to create uniform initializations regardless the type,
    // so we then use braces '{}' which can be used with direct or copy initi.
    // T <obj> {<other>};  For direct list init
    // T <obj> = {<other>}; For copy list init.
    
    return 0;
}