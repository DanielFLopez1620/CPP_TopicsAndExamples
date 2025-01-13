// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * One feature pending to explore is to list the content of a directory, whcih
 * can be also uselful to navigate through a filesystem. There are two options
 * for this: 'directory_iterator' and 'recursive_directory_iterator', where the
 * last one can navigate the same dir and additionally its subdirectories.
 * 
 * Consider the next structure:
 * 
 * | example
 * | - more_info
 * | | - info_1.txt
 * | | - info_2.txt
 * | - resume.txt
 */

#include <filesystem>
#include <fstream>

namespace my_machine = std::filesystem;

int main(int argc, char* argv[])
{
    auto base_path = my_machine::current_path();
    base_path /= "example";

    // Info #1: We need a tree of directories to work, so let's create one
    // by using the create_directory and ofstream to a file.
    try
    {
        std::cout << "Generating filesystem structure to work:" << std::endl;

        if(!my_machine::exists(base_path))
        {
            my_machine::create_directory(base_path);
            std::cout << "\tCreated directory: " << base_path << std::endl;
        }

        auto nested_dir = base_path / "more_info";
        if(!my_machine::exists(nested_dir))
        {
            my_machine::create_directory(nested_dir);
            std::cout << "\tCreated directory: " << nested_dir << std::endl;
        }

        auto info_1 = nested_dir / "info_1.txt";
        std::ofstream(info_1) << "This is the first information." << std::endl;
        std::cout << "\tCreated file: " << info_1 << std::endl;

        auto info_2 = nested_dir / "info_2.txt";
        std::ofstream(info_2) << "This is the second information." << std::endl;
        std::cout << "\tCreated file: " << info_2 << std::endl;

        auto resume = base_path / "resume.txt";
        std::ofstream(resume) << "\tThis is the resume:" << std::endl
                              << "\n\tInfo_1\n\tInfo_2" << std::endl;
        std::cout << "\tCreated file: " << info_1 << std::endl;

    }
    catch(const std::filesystem::filesystem_error e)
    {
        std::cerr << "An error ocurred: " << e.what() << '\n';
    }

    // Info #2: We can iterate the content of a directory (no recursively),
    // by using 'directory_iterator'.
    if (my_machine::exists(base_path) && my_machine::is_directory(base_path))
    {
        for (auto const & entry : my_machine::directory_iterator(base_path))
        {
            auto filename = entry.path().filename();
            if(my_machine::is_directory(entry.status()))
            {
                std::cout << "[dir]: " << filename << std::endl;
            }
            else if(my_machine::is_symlink(entry.status()))
            {
                std::cout << "[sym]: " << filename << std::endl;
            }
            else if(my_machine::is_regular_file(entry.status()))
            {
                std::cout << "[file]: " <<  filename << std::endl;
            }
            else
            {
                std::cout << "[?]: " << filename << std::endl;
            }
        }
    }

    // Info #3: Howevere, you can go iteratively in the subdirectories of a
    // directory and then iterate over them while making the list with
    // 'recursive_directory_iterator()'.
    if(my_machine::exists(base_path) && my_machine::is_directory(base_path))
    {
        for(auto const & entry : 
            my_machine::recursive_directory_iterator(base_path))
        {
            auto filename = entry.path().filename();
            if(my_machine::is_directory(entry.status()))
            {
                std::cout << "[dir]: " << filename << std::endl;
            }
            else if(my_machine::is_symlink(entry.status()))
            {
                std::cout << "[sym]: " << filename << std::endl;
            }
            else if(my_machine::is_regular_file(entry.status()))
            {
                std::cout << "[file]: " <<  filename << std::endl;
            }
            else
            {
                std::cout << "[?]: " << filename << std::endl;
            }
        }
    }

    return 0;
}