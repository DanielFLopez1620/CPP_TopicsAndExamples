// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Another way to manage bit is by considering unsigned int values, then in C++
 * the numeric library has some utilities related with bit manipulation. 
 * 
 * Do not forget to import <bit> library.
 */

#include <cstring>
#include <vector>
#include <bit>

int main(int argc, char* argv[])
{
    // Info #1: You can use unsigned char and unsigned int values as bit
    // sequences, and you can perform operations with them, in this case
    // we have the circular shift (if a number is send to the margin, it
    // appear at the other site), the operators can be 'rotl' and 'rotr'.
    unsigned char my_bin = 0b00010100;
    std::cout << "Using circular shift operations:" << std::endl
              << "\tOriginal binary: " << my_bin << std::endl
              << "\tLeft Shift by 0: " << std::rotl(my_bin, 0) << std::endl
              << "\tLeft Shift by 1: " << std::rotl(my_bin, 1) << std::endl
              << "\tLeft Shift by 2: " << std::rotl(my_bin, 2) << std::endl
              << "\tLeft Shift by 4: " << std::rotl(my_bin, 4) << std::endl
              << "\tRight Shift by 1: " << std::rotr(my_bin, 1) << std::endl
              << "\tRight Shift by 6: " << std::rotr(my_bin, 6) << std::endl;
    
    // Info #2: Another interesting method is to use a counter of how many
    // positions until a one is found, it can be 'countl_zero' for start at the
    // left and 'countr_zero' for starting from the right. You can have a
    // similar behavior for ones with 'countl_one' and 'countr_one'.
    unsigned char my_bin2 = 0b01000000;
    unsigned char my_bin3 = 0b00011000;
    unsigned char my_bin4 = 0b11000001;
    unsigned char my_bin5 = 0b01101111;
    std::cout << "Count of zeros or count up to a one: " << std::endl
              << "\tBinary #2:" << my_bin2 << std::endl
              << "\t\tC0 left: " << std::countl_zero(my_bin2) << std::endl
              << "\t\tC0 Right: " << std::countr_zero(my_bin2) << std::endl
              << "\tBinary #3:" << my_bin3 << std::endl
              << "\t\tC0 left: " << std::countl_zero(my_bin3) << std::endl
              << "\t\tC0 Right: " << std::countr_zero(my_bin3) << std::endl
              << "\tBinary #4:" << my_bin4 << std::endl
              << "\t\tC1 left: " << std::countl_one(my_bin4) << std::endl
              << "\t\tC1 Right: " << std::countr_one(my_bin4) << std::endl
              << "\tBinary #5:" << my_bin5 << std::endl
              << "\t\tC1 left: " << std::countl_one(my_bin5) << std::endl
              << "\t\tC1 Right: " << std::countr_one(my_bin5) << std::endl;

    
    // Info #3: You can also get the number of 1 active throught the element by
    // using popcount.
}