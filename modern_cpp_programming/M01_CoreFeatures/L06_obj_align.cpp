// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>
/* 
 * OBJECT ALLIGMENT: It is important to boost performance for some processors,
 * and also to use specific instructions on particular aligments, for example,
 * a more effective copy and optimizing CPU reading and writing. This is very
 * important for games and trading apps.
 */

// -------- STRUCT DECLARATION:
// For types and objects, you use 'alignas' specifier:
struct alignas(8) pos
{
    int x;
    int y;
};
struct pos_aux
{
    alignas(8) int x;
    alignas(8) int y;
};
struct alignas(4) align_example
{
    alignas(8) int pos;
    alignas(2) char let;
};


int main()
{
    // You can also declare aligment for types:
    alignas(8) int opt;

    // To query the aligment, you use 'alignof' operator:
    auto align_type = alignof(pos);

    /*
     * REMEMBER: For the aligment...
     *  - It must match the size of the largest member to,
     *    avoid error while performing.
     *  - It must be greater than zero.
     *  - It can be used in the declaration of a variable or class data member.
     */

    // Finally, let's see some examples for alignof:
    std::cout << "Char: " << alignof(char) <<std::endl;
    std::cout << "Int: " << alignof(int) <<std::endl;
    std::cout << "Int*: " << alignof(int*) <<std::endl;
    std::cout << "Int[4]: " << alignof(int[4]) <<std::endl;
    std::cout << "Align_example: " << alignof(align_example) <<std::endl;

    return 0;
}