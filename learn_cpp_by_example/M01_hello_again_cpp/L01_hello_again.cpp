// Based on the Learn C++ by Example (2024) by Frances Buontempo

// /////////////////////////// IMPORTS ////////////////////////////////////////
// Include is used to import libraries.
#include <iostream>

// ////////////////////////// MAIN FUNCTION ///////////////////////////////////

/**
 * Main function oriented to print a message
 *
 * Do not forget that you can compile and run with:
 *      g++ L01_hello_again.cpp -o ./hello.out
 *      ./hello.out
 */
auto main() -> int
{
    // As you can check, auto can be used on function definition with
    // with a trailing return

    // The operator << help us to output something
    std::cout << "Hello C++! Again?" << std::endl;

    // As the trailing was defined, it is not mandatory the return
    return 0;
}