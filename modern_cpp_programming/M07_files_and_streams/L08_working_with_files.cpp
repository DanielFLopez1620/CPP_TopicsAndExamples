// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17, pending testing in Windows

#include <iostream>

/**
 * We explored a little of <filesystem> header related with paths. However, it
 * isn't it only focus as you can copy, move and delete files or directories,
 * no matter if it is Windows or POXIS filesystem.
 * 
 * NOTE: Where you compile the code, must have the /08_temp/08_text elements,
 * by default we are considering the path to the repository in the localtion
 * of the Module 7.
 */

#include <filesystem>
#include <iomanip>

namespace my_machine = std::filesystem;

int main(int argc, char* argv[])
{
    // Info #1: You can access to your current location and part from them to
    // explore the filesystem with the operator /:
    auto err = std::error_code{};
    auto current_path = my_machine::current_path();
    auto desired_path = current_path / "08_temp" / "08_text.txt";


    return 0;
}