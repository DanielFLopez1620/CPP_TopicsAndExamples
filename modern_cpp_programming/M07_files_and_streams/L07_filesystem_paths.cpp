// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17, pending testing in Windows

#include <iostream>

/**
 * C++17 came with the 'filesystem' library that enable to work with paths,
 * files and directories in hierachical filesystems. It also enabled querying
 * and searching in the system.
 * 
 * This allows to works with POSIX or Windows systems, even with Universal
 * Naming Convention (UNC) format. Where:
 * 
 * - POSIX: Single tree with no root name and a single root dir, with '/'
 *   as the separator, coded in UTF-8.
 * - WINDOWS:  Can have multiple trees and uses "\" coded in UTF-16.
 * 
 * It also allows recognition of symbol like (.) for current directory, (..)
 * for parent directory.
 * 
 * Consider the information below that is centered for Ubuntu/Debian systems.
 * 
 * It would be proper to have a structure ounted on your home dir like:
 * 
 * examples
 * └── folder1
 *     └── folder1-1
 *         └── hi.txt
 * 
 * NOTE: Make sure to change your user when doing this in line 52.
 * 
 * So when you are ready, you can compile and run with:
 * 
 *      g++ -std=c++17 L07_filesystem_paths.cpp -o file_paths.out
 *      ./file_paths.out
 */

// -------------------------- REQUIRED LIBRARIES ------------------------------
#include <filesystem> // Library to manage filesystems
#include <iomanip>    // I/O Manipulators

// -------------------------- NAMESPACE CONSIDERED ----------------------------
// Info #1: You can create a namespace for using the local filesystem easier
namespace my_machine = std::filesystem;

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 7: Working with filesystem path...\n" << std::endl;
    // Info #2: To create a path you use the 'path' member of the filesystem
    // and pass a valid absolute path
    auto desired_path = my_machine::path{"/home/dan1620/example"};

    // Info #3: You can add elements to the path with the operator/= and
    // operator / or the append method. Make sure what you add is valid for
    // the path. You can also concatenate with operator+= and operator +.
    desired_path /= "folder1";
    desired_path.append("folder1-1");
    desired_path /= "hi.txt";

    // Info #4: You can decompose the paths in differn elements with 
    // 'root_name()'. 'root_dir()', 'filename()', 'stem()' and 
    // 'extension()' and so on...
    std::cout << "Considering a path...\nWe have the next info:"
              << std::endl << "\tRoot: " << desired_path.root_name()
              << std::endl << "\tRoot Dir: " << desired_path.root_directory()
              << std::endl << "\tRoot Path: " << desired_path.root_path()
              << std::endl << "\tRel path: " << desired_path.relative_path()
              << std::endl << "\tFilename: " << desired_path.filename()
              << std::endl << "\tStem: " << desired_path.stem()
              << std::endl << "\tExtension: " << desired_path.extension()
              << std::endl;
    
    // Info #5: You can also have booleans members in order to check the 
    // provided path, for example, 'has_root_name()', 'has_root_directory()',
    // 'has_root_path()', 'has_relative_path()', 'has_filename()', 'has_stem()',
    // 'has_stem()' and 'has_extension()'.
    std::cout << "We have the next flags:" << std::boolalpha << std::endl
              << "\tHas root?: " << desired_path.has_root_name() << std::endl
              << "\tHas root dir?: " << desired_path.has_root_directory()
              << std::endl << "\tHas root path?: " 
              << desired_path.has_root_path() << std::endl << "\tHas rel path?: "
              << desired_path.has_relative_path() << std::endl 
              << "\tHas parent path?: " << desired_path.has_parent_path()
              << std::endl << "\tHas filename?: " << desired_path.has_filename()
              << std::endl << "\tHas stem?: " << desired_path.has_stem()
              << std::endl << "\tHas extension?: " << desired_path.has_extension()
              << std::endl;

    // Info #6: You can check whether a path is relative or absolute.
    auto another_path = my_machine::path("hola/que_tal");
    std::cout << "Testing absolute paths: " << std::endl << std::boolalpha
              << "\t/home/dan1620... : " << desired_path.is_absolute()
              << "\n\t/hola/que_tal... : " << another_path.is_absolute()
              << std::endl;

    // Info #7: You can also use modifiers with the paths provided, for
    // example, to change  the extension or change the filename.
    std::cout << "Modifying the path: " << std::endl << "\tCurrent path:"
              << desired_path << std::endl;
    desired_path.replace_extension(".bin");
    std::cout << "\tMod. extension: " << desired_path << std::endl;
    desired_path.replace_filename("bye");
    std::cout << "\tMod. filename: " << desired_path << std::endl;

    // Info #8: If the code aims to work with different filesystems, you may
    // need to shift the directory separator. If you are not sure about it,
    // you can try with a default and then modify it with 'make_preferred'.
    auto different_path = my_machine::path{"\\home\\dan\\Documents"};
    different_path.make_preferred();

    
    return 0;
} // main()