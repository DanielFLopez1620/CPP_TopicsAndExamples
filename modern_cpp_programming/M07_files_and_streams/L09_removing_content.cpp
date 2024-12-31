// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Sometimes the 'filesystem' library doesn't cover the functionalities you may
 * need, for example, removing the content of a file, not matter if it is
 * binary or text. 
 * 
 * Here you can do the next steps:
 * 
 * 1. Create a temporary file.
 * 2. Copy the desired content from the original file.
 * 3. Deleting the original file.
 * 4. Rename/move the temporary file to the original file location.
 * 
 * You can delete certain content of the file based on a patter, for example,
 * comments of a text code (in C++ would be //)
 * 
 * The excersice of this lesson is to delete the comments of a source file
 * from a C++ code, so check the L09_remove_part.txt file. Make sure you pass
 * the correct path to the file.
 * 
 * Compile and run this code from the base workspace of this repo:
 * 
 * 
 */

// ------------------------ REQUIRED LIBRARIES ------------------------------
#include <filesystem>  // For using the filesystem in POSIX/WiN systems
#include <fstream>     // File stream

// -------------------------- NAMESPACES TO CONSIDER -------------------------
namespace my_machine = std::filesystem;

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 9: Removing content of a file\n" << std::endl;

    
    // Info #1: Based on the current location, provide the path to the file to
    // read and the file to write, also considering to instatiate a error_code
    auto path = my_machine::current_path();
    auto input_file = path / "modern_cpp_programming" / "M07_files_and_streams" /
        "L09_remove_part.txt";
    auto output_file = path / "modern_cpp_programming" / "M07_files_and_streams" /
        "L09_done_part.txt";
    auto err = std::error_code{};

    // Info #2: Open the file by considering the provided filesystem path. Log
    // an error if it is not possible to open it.
    std::ifstream my_input(input_file);
    if (!my_input.is_open())
    {
        std::cout << "File L09.remove_part.txt didn't open..." << std::endl;
        return 1;
    }

    // Info #3: Open temporary file for writing, in truncate mode in case
    // it already exists.
    std::ofstream my_output(output_file, std::ios::trunc);
    if(!my_output.is_open())
    {
        std::cout << "File L09.done_part.txt wasn't created..." << std::endl;
        return 1;
    }

    // Info #4: Read each line, and search for those that aren't comments. In
    // other words, if a line start with '//' it isn't added to the output
    // file.
    auto line = std::string{};
    std::cout << "Process to delete comments will start soon..." << std::endl;
    while (std::getline(my_input, line))
    {
        if (!line.empty() && line.find("//") !=0 )
        {
            my_output << line << "\n";
        }
    }
    std::cout << "Comments cleared from the file passed" << std::endl;

    // Info #5: Do not forget ot close the streams you have used.
    my_input.close();
    my_output.close();

    // Info #6: If you are interested, you can delete the old file.
    // auto del_succ = my_machine::remove(input_file, err);
    // if(!del_succ || err)
    // {
    //     std::cout << "Something happened with the removal process"
    //               << std::endl;
    //     return 1;
    // }
    std::cout << "Process finished..." << std::endl;

    return 0;
} // main()