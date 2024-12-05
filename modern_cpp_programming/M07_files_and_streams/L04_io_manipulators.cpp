// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You know that the operators >> and << allow input/output streams by
 * considering strings. However, they are not limited to this and can use
 * manipulators to format the output to the console.
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
    // the filling of the characters
    std::cout << "Using aligment with left/right: " << std::endl
              << std::right << std::setw(10) << "\tOn your right" << std::endl
              << std::left << std::setw(10) << "\tOn your left" << std::endl;

    
    return 0;
}
