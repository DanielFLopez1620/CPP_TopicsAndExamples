// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Aliases become handy when a custom type is repetitive or you want to create
 * custom types for your implementations. Here, your ally will be 'typedef' 
 * which can be used with declarations or templates to create custom aliases. 
 * But it can also be achieved with the 'using' declaration for type aliases.
 * 
 * TIPS:
 * - Do not mix 'typedef' and 'using' declarations.
 * - Prefer the use of 'using' for names of function pointers.
 * - Use them only to improve readability.
 * - Alias cannot be explicity specialized.
 * - Alias cannot use to make use of its own type.
*/

int main(int argc, char** argv)
{
    // Info #1: Basic usage of type aliases: using <identifier> = <type_id>
    using opt = char;
    using proto = void(opt);

    return 0;
}