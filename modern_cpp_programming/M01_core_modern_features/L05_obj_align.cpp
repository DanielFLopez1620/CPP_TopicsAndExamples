// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Query object alignment refers to the alignment requirements imposed on
 * memory allocated for query objects in a computer program, in other words, 
 * the memory adress at which objects are stored, and it depends on the 
 * constraints according the data type. This aims to memory efficient and
 * proper data manipulation.
 * 
 * C++11 provided standardized mehtods for specifying this (previously it was
 * possible only with compiler methods). It was implemented in the way to boost
 * performance because it is not the same to work with an Intel SSE than a 
 * SSE2. The commands of interest of this section are 'alignof' and 'alignas'.
 * 
 * This process is needed as the processor acces memory in chunks (2, 4, 8...),
 * then, it will need easy access to the data as if it isn' aligned, it will
 * take extra work to the compiler. The standard speciefies that chars (char,
 * unsigned char, char8_t and std::byte) must be 1, and it will change for
 * other types, like short (16 bits), long (32 bits) and long long (64 bits),
 * but some types sizes may vary according the platform and compiler. Then, the
 * only valid alignments are powers of 2 (and aligment 0 will be always 
 * ignored).
 * 
 * But... if it is already defined.... why we should check the align? It is
 * because we define structures and unions, and the alignment must match the size
 * of the largets member to avoid performance issues. You can think of it like:
 * 
 * struct letter
 * {
 *      char a; // Memory boxes analogy: |a|
 * }
 * 
 * struct two_letters
 * {
 *      char b; // Memory boxes analogy: |a|b|
 * }
 * 
 * struct letter_and_short
 * {
 *      char a;
 *      short c;  // Memory boxes analogy: |a.|cc|
 * }
 * 
 * The '.' dot refers to a padding byte, and it is the reason, it is better to
 * consider the larger type, and also to search a better organization of your
 * type to optimize memory and minimize paddings needed. You can check memory
 * registers by using pointers (with operator &), and check the distribution.
 * 
 * You can run and experiment with the code with:
 * 
 *      g++ -std=c++20 L05_obj_align.cpp -o obj_align.out
 *      ./obj_align.out
 * 
*/

// Info #1: Alignas can be used to control the alignment of a type in both,
// class level or data member level, keep in mind it must be consistent with
// the types you are using and the purpose of the implementation. 
struct alignas(4) double_char
{
    char l1;
    char l2;
};
struct access
{
    alignas(2) char type;
    alignas(8) unsigned int id;
};


int main(int argc, char* argv[])
{
    // Info #2: To query or get the alignment of a type, you use 'alignof'
    // operator, remember to use auto for better type deduction.
    auto double_char_align = alignof(double_char);
    auto access_align = alignof(access);

    // Info #3: Let's explore the align of some common and custom types.
    std::cout << "Align of some types: " << std::endl
              << "\tCustom double char: " << double_char_align << std::endl
              << "\tCustom access: " << access_align << std::endl
              << "\tChar: " << alignof(char) << std::endl
              << "\tInt: " << alignof(int) << std::endl
              << "\tDouble: " << alignof(double) << std::endl;


    return 0;
}