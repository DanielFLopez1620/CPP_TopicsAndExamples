// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>

// ----------------- STRUCT DEFINITIONS:
struct useCommon { char l; };

// ----------------- NAMESPACES:
/*
 * UNNAMED NAMESPACES:
   To let the user choose between multiple library options that are provided,
   you need to consider:
     1) Define the content of the library inside a namespace.
     2) Define each version of the library inside an inner inline namespece.
     3) Use preprocessor and '#if' directives to enable the specified version.

    Usage: Using a fictionary library with to version:
 */
namespace generallib
{
    #ifndef LIB_VERSION_1
    inline namespace v_1 
    {
        template <typename Gen>
        char test (Gen data) { return 'a'; }
    }
    #endif

    #ifdef LIB_VERSION_2
    inline namespace v_2
    {
        template <typename Gen>
        char test (Gen data) { return 'b'; }
    } 
    #endif
}

// Example: Common library that evolves over time.
namespace commonlib1
{
    template <typename Gen>
    char test(Gen data) { return 'a'; }
}
// Example: Common library that evolves, but uses an struct as a param.
namespace commonlib2
{
    template <>
    char test(useCommon value) { return value.l; }
    //TODO: Finish usage and common lib
}



int main()
{
    std::cout << "Module 01 - Lesson 12: " << std::endl;
    std::cout << "Using unnamed namespaces..." << std::endl << std::endl;
    
    auto com_usage1 = commonlib1::test('l');

    auto com_usage2 = commonlib2::test( useCommon { 'a' });
    return 0;
}