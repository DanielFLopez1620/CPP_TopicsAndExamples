// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream> 

/**
 * It isn't common to work with bit flags unless you work with Operating System
 * APIs or libraries that work in a similar way. But there are alternatives to
 * work with bits and bit operations such as using arrays or structures with
 * the desired members, however, this can be complicated. 
 * 
 * That is the reason, the std::bitset was provided as a container for fixed-size
 * sequences of bits. It is present in the header <bitset> and allow fixed-size
 * sequences of bits.
 */

#include <bitset>
#include <string>

int main(int argc, char* argv[])
{
    
    using namespace std::string_literals;
    
    // Info #1: There are various forms to initialize a bit set, they can be 
    // zero initialization, based on a numerical value, based on a string of
    // ones and zeros, or a string combination of two characters, the options
    // are presented below:
    std::bitset<4> bset1;
    std::bitset<4> bset2 {12};
    std::bitset<4> bset3 { "1100"s };
    std::bitset<4> bset4 { "lool"s, 0, std::string::npos, 'o', 'l'};
    std::cout << "BitSet intialization and construction: " << std::endl
              << "\tSet 1: {}:" << bset1 << std::endl
              << "\tSet 2: {12}: " << bset2 << std::endl
              << "\tSet 3: {\"1100\"}: " << bset3 << std::endl
              << "\tSet 4: {\"lool\"}: " << bset4 << std::endl;

    // Info #2: Let's explore some related methods for bit usage...
    std::cout << "Bit checker by considering bset 2: " << std::endl
              << "Count of ones: " << bset2.count() << std::endl
              << "Contians any ones?: " << bset2.any() << std::endl
              << "Is everything one?: " << bset2.all() << std::endl
              << "Is everything zero?: " << bset2.none() << std::endl;
    return 0;
}