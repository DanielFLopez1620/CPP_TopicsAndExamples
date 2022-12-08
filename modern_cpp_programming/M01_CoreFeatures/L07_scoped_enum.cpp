// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>

/* 
 * ENUMERATIONS: It is a basic type in C++ for collections of values, it can be:
 * - Unscoped enumeration: 'enum'.
 * - Scoped enumeration: 'enum class' or 'enum struct'. (Added in C++11)
 */

// -------- CLASS DECLARATIONS:
enum class Grade {First, Second, Third};

// --------  STRUCT DECLARATIONS:
struct nums
{
    enum class Percentage {Empty, Half, Full};
    using enum Percentage;
};

int main()
{
    Grade selected = Grade::Third;
    
    // In C++20, it can be combined with associate namespace with 'using':
    using Grade::Second;
    Grade optional = Second;

    // If namespace is available, you can use:
    nums::Percentage advance = nums::Half; // Instead of nums::Percentage::Half

    // It can be used in switch cases:
    switch (selected)
    {
        using enum Grade;

        case First:
            std::cout << "Selected is First" << std::endl;
        break;

        case Second:
            std::cout << "Selected is Second" << std::endl;
        break;

        case Third:
            std::cout << "Selected is Third" << std::endl;
        break;

        default:
        break;
    }
    
    return 0;
}