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
 * 
 * In case you haven't worked with bit sets, they can be used for:
 * 
 *  - Define bit flags for style, options and more (even with macros).
 *  - Easy change of fligs by using operator OR or negated AND flag.
 *  - Checking the correspondy between flags (value & FLAG == FLAG)
 * 
 * With the implemantion of bitset class, the aim was set to write more robust
 * and safer code, by considering the new methods of set() and reset(), use
 * a proper check with test() and allow valid conversions to string and numeric
 * types.
 * 
 * In case, you cannot use bitset, there is an option called std::Vector<bool>
 * that you will check on the next lesson.
 * 
 * When you are ready, you can compile an run this code with:
 * 
 *      g++ -std?c++20 L02_bitset_sequence.cpp -o bitset.out
 *      ./bitset.out 
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
              << "Is everything zero?: " << bset2.none() << std::endl
              << "Is it event (test)?: " << bset2.test(0) << std::endl;

    // Info #3: You can perform binary operations between among bitsets or
    // one bitset with itself. They can be OR, AND, XOR and NOT bitwise or
    // even shifting operations (left or right), let's check some examples:
    std::cout << "\nLet's use the bitset 3 and 4 for some binary operations: "
              << std::endl << "B3: " << bset3 << ", B4: " << bset4
              << std::endl << "\tb3 | b4: " << (bset3 | bset4)
              << std::endl << "\tb3 & b4: " << (bset3 & bset4)
              << std::endl << "\tb3 ^ b4: " << (bset3 ^ bset4)
              << std::endl << "\t~b3" << (~bset3)
              << std::endl << "\tb3 >> 2: " << (bset3 >> 2)
              << std::endl << "\tb3 << 2: " << (bset3 << 2)
              << std::endl << "\tflip(b3): " << (bset3.flip())
              << std::endl;
    
    // Info #4: In case yo need to convert a bit set to a value or a string, 
    // C++ has proper methods to no the conversion. But be careful with the
    // ones that convert to numerical values, as you may need to handle the
    // std::overflow_error excception.
    std::cout << "\nLet's convert the bitset2 to different types: "
              << std::endl << "\tUnsigned long: " << bset2.to_ulong()
              << std::endl << "\tUnsigned long long: " << bset2.to_ullong()
              << std::endl << "\tString: " << bset2.to_string()
              << std::endl << "\tString(x,o): " << bset2.to_string('o', 'x')
              << std::endl;

    return 0;
}