// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Another way to manage bit is by considering unsigned int values, then in C++
 * the numeric library has some utilities related with bit manipulation. 
 * 
 * Do not forget to import <bit> library.
 * 
 * As a rule, when using bits in this context, the origin value should be a 
 * unsignmed integer (unsigned char, unsigned short, unsigned int, unsigned
 * long, uint8_t, uint64_t....), but this changes with the function 
 * 'std::bit_cast' where the argument can be reinterpreted (as long as the 
 * values are copyable) and the function itself contains objects that aren't a
 * union type, a volatile-qualified type and has non-static data of a reference
 * type.
 * 
 * Check the code below for checking other implementations with bit, you can
 * run it with:
 * 
 *      g++ -std=c++20 L04_bit_manipulation.cpp -o bit_manip.out
 *      ./bit_manip.out
 */

// -------------------------------- REQUIRED HEADERS --------------------------

#include <cstring> // For manipulation of strings according C
#include <vector>  // For dynamic sequences of objects
#include <bit>     // For using bits in its native form for C++
#include <bitset>  // Related with bit sequences and bit operations

// -------------------------------- FUNCTION DEFINITIONS ----------------------

/**
 * Using bitsets, obtain fromt he passsed char the binary of interest to become
 * it into a string for printing or other implementations. 
 * 
 * @param value Unsigned value for obtaining a bit sequence
 * 
 * @return Bit sequence into a string 
 */
std::string get_bin_str(unsigned char value) 
{
    std::bitset<8> binary(value);
    return binary.to_string();

} // get_bin_str

// ------------------------------- MAIN IMPLEMENTATION ------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 4: Bit manipulation...\n" << std::endl;
    // Info #1: You can use unsigned char and unsigned int values as bit
    // sequences, and you can perform operations with them, in this case
    // we have the circular shift (if a number is send to the margin, it
    // appear at the other site), the operators can be 'rotl' and 'rotr'.
    unsigned char my_bin = 0b00010100;
    std::cout << "Using circular shift operations:" << std::endl
              << "\tOriginal binary: " << get_bin_str(my_bin) << std::endl
              << "\tLeft Shift by 0: " << get_bin_str(std::rotl(my_bin, 0))
              << std::endl << "\tLeft Shift by 1: " 
              << get_bin_str(std::rotl(my_bin, 1))
              << std::endl << "\tLeft Shift by 2: " 
              << get_bin_str(std::rotl(my_bin, 2))
              << std::endl << "\tLeft Shift by 4: " 
              << get_bin_str(std::rotl(my_bin, 4))
              << std::endl << "\tRight Shift by 1: "
              << get_bin_str(std::rotr(my_bin, 1))
              << std::endl << "\tRight Shift by 6: "
              << get_bin_str(std::rotr(my_bin, 6))
              << std::endl << std::endl;
    
    // Info #2: Another interesting method is to use a counter of how many
    // positions until a one is found, it can be 'countl_zero' for start at the
    // left and 'countr_zero' for starting from the right. You can have a
    // similar behavior for ones with 'countl_one' and 'countr_one'.
    unsigned char my_bin2 = 0b01000000;
    unsigned char my_bin3 = 0b00011000;
    unsigned char my_bin4 = 0b11000001;
    unsigned char my_bin5 = 0b01101111;
    std::cout << "Count of zeros or count up to a one: " << std::endl
              << "\tBinary #2:" << get_bin_str(my_bin2) << std::endl
              << "\t\tC0 left: " << std::countl_zero(my_bin2) << std::endl
              << "\t\tC0 Right: " << std::countr_zero(my_bin2) << std::endl
              << "\tBinary #3:" << get_bin_str(my_bin3) << std::endl
              << "\t\tC0 left: " << std::countl_zero(my_bin3) << std::endl
              << "\t\tC0 Right: " << std::countr_zero(my_bin3) << std::endl
              << "\tBinary #4:" << get_bin_str(my_bin4) << std::endl
              << "\t\tC1 left: " << std::countl_one(my_bin4) << std::endl
              << "\t\tC1 Right: " << std::countr_one(my_bin4) << std::endl
              << "\tBinary #5:" << get_bin_str(my_bin5) << std::endl
              << "\t\tC1 left: " << std::countl_one(my_bin5) << std::endl
              << "\t\tC1 Right: " << std::countr_one(my_bin5) << std::endl
              << std::endl;

    
    // Info #3: You can also get the number of 1 active throught the element by
    // using popcount.
    std::cout << "Counting 1s present in a binary: " << std::endl
              << "\tBinary #1: " << get_bin_str(my_bin) << " -> " 
              << std::popcount(my_bin)  << std::endl << "\tBinary #2: " 
              << get_bin_str(my_bin2) << " -> " << std::popcount(my_bin2) 
              << std::endl << "\tBinary 3:" << get_bin_str(my_bin3) << " -> "
              << std::popcount(my_bin3) << std::endl << "\tBinary 4:" 
              << get_bin_str(my_bin4) << " -> " << std::popcount(my_bin4) 
              << std::endl << std::endl;

    // Info #4: You can easily detect if a number or bit sequence is a power of
    // two by comprobating if just one bit is active along the sequence, you can
    // achieve it with 'has_single_bit()' method.
    std::cout << "Checking if binaries are power of 2:" << std::endl
              << "\tBinary #1: " << get_bin_str(my_bin) << " -> " 
              << std::has_single_bit(my_bin) << std::endl << "\tBinary #2: "
              << get_bin_str(my_bin2) << " -> " 
              << std::has_single_bit(my_bin2) << std::endl << "\tBinary 3: " 
              << get_bin_str(my_bin3) << " -> " 
              << std::has_single_bit(my_bin3) << std::endl << std::endl;

    // Info #5: You can get how many bits are necesarry to represent 
    // certain num, based on ceil, floor or width cases.
    std::cout << "Checking binaries size for my_bin 4" << std::endl
              << "\tOriginal binary: " << get_bin_str(my_bin4) << std::endl
              << "\tCeil size: " << std::bit_ceil(my_bin4) << std::endl
              << "\tFloor size: " << std::bit_floor(my_bin4) << std::endl
              << "\tWidth size: " << std::bit_width(my_bin4) << std::endl
              << std::endl;

    // Info #6: There is also options for casting types, for example, a double to its
    // binary representation or hex.
    const double euler = 0.5772156649;
    const uint64_t bit_for_e = std::bit_cast<uint64_t>(euler);
    const double euler_pos = std::bit_cast<double>(bit_for_e);

    std::cout << "Conversion with bits: \n\tOriginal Euler: " << euler
              << std::endl << "\tHex representation: " << bit_for_e
              << std::endl << "\tReconversion to double: " << euler_pos
              << std::endl << std::endl;

} // main