// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Aliases become handy when a custom type is repetitive or you want to create
 * custom types for your implementations. Here, your ally will be 'typedef' 
 * which can be used with declarations or templates to create custom aliases. 
 * But it can also be achieved with the 'using' declaration for type aliases.
 * 
 * 'typedef' doesn't introudce another type, like class, struct, union or enum,
 * so the you can use type declarations, to create you own type.
 * 
 * TIPS:
 * - Do not mix 'typedef' and 'using' declarations.
 * - Prefer the use of 'using' for names of function pointers.
 * - Use them only to improve readability.
 * - Alias cannot be explicity specialized.
 * - Alias cannot be used to make use of its own type.
 * 
 * You can try this code with: 
 *      g++ -std=c++20 L02_type_aliases.cpp -o aliases.out
 *      ./aliases.out
*/

// ------------------- CUSTOM CLASSES, PROTOTYPES AND DEFINITONS --------------

// Info #1: You can use alias templates of the form 
// 'template< <params> > <id> = <type> 
template <class T>
class custom_class { /* ... */};

// Info #2: typedef usage is: 'typedef <type> <name>;' and can be implemented
// with any type, function prototype of class.
typedef unsigned int numeral;
typedef unsigned int * numeral_ptr;

// --------------------- MAIN IMPLEMENTATION -----------------------------------
int main(int argc, char** argv)
{
    std::cout << "Lesson 2: Type aliases...\n" << std::endl;

    // Info #3: Basic usage of type aliases: using <identifier> = <type_id>
    using opt = char;
    using proto = void(opt);
    opt my_option = 'a';
    std::cout << "Opt as char: " << my_option << std::endl << std::endl; 

    // Info #4: Testing typedef definitions.
    numeral my_num = 16;
    numeral_ptr my_ptr = &my_num;
    std::cout << "Numeral: " << my_num << std::endl
              << "Ptr: " << my_ptr << std::endl
              << "Ptr value: " << *my_ptr << std::endl;

    return 0;
} // main