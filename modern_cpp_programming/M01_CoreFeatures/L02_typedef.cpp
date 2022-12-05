// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>
#include <vector>

int main()
{
    // typedef: Create synonums for a type name
    // It's mostly used for more meaningful names or for function pointers

    // Basic usage: using <identifier> = <type_id>
    using opt = char;
    using proto = void(opt);

    //Usage for templates (also see the declarations at the end):
    /*
    alias_ex<int>         vi;
    alias_ex<std::string> vs;
    */

    // TIPS:
    // * Do not mix 'typedef' and 'using' declarations.
    // * Prefer the use of 'using' for names of function pointers.
    // * Use them only to improve readability.
    // * Alias cannot be explicity specialized.
    // * Alias cannot use to make use of its own type.
    
    return 0;
}

/*
template <class example>
    class custom_allocator 
    {
        // Void
    };

template <typename example>
    using alias_ex = std::vector<example,
    custom_allocator<example>>;
*/
    
    
