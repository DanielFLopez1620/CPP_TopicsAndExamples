// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You know that the operators >> and << allow input/output streams by
 * considering strings. However, they are not limited to this and can use
 * manipulators to format the output to the console.
 * 
 * The manipulators can affect a field (like setw) or a full stream, by
 * considering arguments (width, setprecision...) or not (like boolapha, dec,
 * hex, oct...) that are possible as the operator<< has overloads with 
 * pointers to these functions.
 * 
 * They can be combined to generate more complex output formats,for example,
 * when you want to achieve a index from a book in a ordered way.
 */

#include <ios>
#include <iomanip>

int main(int argc, char* argv[])
{
    // Info #1: Tired of using the ternary operator to display 'false' or 
    // 'true' when using booleans, say no more to that and start using
    // 'std::boolalpha' and 'std::noboolalpha'.
    std::cout << "Testing boolalpha for diplaying booleans: " << std::endl
              << std::boolalpha << "\tIs Pluto a planet? " << false << std::endl
              << std::noboolalpha << "\tIs Pluto a planet? " << false 
              << std::endl;
    
    // Info #2: You can use alligment 'left', 'right' and 'internal' to affect
    // the filling of the characters. Where std::setw changes the width of the
    // input or field (default is 0) and width refers to the witd.
    std::cout << "Using aligment with left/right (width of 20): " << std::endl;
    std::cout.width(20); std::cout<< std::right << "  On your right" << std::endl;
    std::cout.width(20); std::cout << std::left << std::setw(20) << 
        "  On your left" << std::endl;

    // Info #3: You can also modify the numeric format to adapt it in a fixed,
    // scientific or hexfloat format.
    float dan_flt = 1.62;
    std::cout << "Testing number formats for floats: " << std::endl
              << "\tFixed: " << std::fixed << dan_flt << std::endl
              << "\tScientific: " << std::scientific << dan_flt << std::endl
              << "\tHexfloat: " << std::hexfloat << dan_flt << std::endl
              << "\tDefault: " << std::defaultfloat << dan_flt << std::endl;
    
    // Info #4: You can also control the integer type for display
    int dan_int = 1620;
    std::cout << "Testing integer types for display: " << std::endl
              << "\tOct:"  << std::oct << dan_int << std::endl
              << "\tHex: " << std::hex << dan_int << std::endl
              << "\tDec: " << std::dec << dan_int << std::endl;
    
    // Info #5: You can make indexes and patterns to fill a word if it is
    // not long enough, with points or the character of your preference.
    std::cout << "Filling content and make spaces: " << std::endl
              << "\t" << std::right << std::setfill('-') << std::setw(20)
              << "Fill right" << std::endl;

    // Info #6: If you want a certain precision (number of decimal units)
    // you cna use std::setprecision().
    std::cout << "Using different precisions with floats: " << std::endl
              << "\tNumber: " << dan_flt << std::endl << "\t2 precision: "
              << std::fixed << std::setprecision(dan_flt) << std::endl;
    
    return 0;
}
