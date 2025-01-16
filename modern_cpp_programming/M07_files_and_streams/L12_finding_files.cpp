// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * We have already iterated throught directory in the previous lesson, so let's
 * get further, as you can list the files iteratively, then you can search for
 * a certain file, or even files with a certain extension.
 * 
 * We will use the same directory structure, so make sure you have run the
 * previous lesson code and the structure that appears should be:
 * 
 * | example
 * | - more_info
 * | | - info_1.txt
 * | | - info_2.txt
 * | - resume.txt
 * 
 * To search for a file that match a particular criteria, we need to follow the
 * next steps:
 * 
 * 1. Iterate thought all the entrys of a directory and its subdirectories with
 *    'recursive_directory_iterator'.
 * 2. Consider a certain regular file.
 * 3. Use a function object (for example a lambda expression) to filter the
 *    match criteria.
 * 4. Add the selected entries to a range (vector)
 * 
 * Check the function created based on the previous lesson to search
 * iteratively, and review the find files function too.
 * 
 */

#include <filesystem>
#include <vector>
#include <functional>
#include <regex>

namespace my_machine = std::filesystem;

std::vector<my_machine::path> search_file(
    my_machine::path const & dir,
    std::function<bool(my_machine::path const&)> filter);

int main(int argc, char* argv[])
{
    return 0;
}

std::vector<my_machine::path> search_file(
    my_machine::path const & dir,
    std::function<bool(my_machine::path const&)> filter)
{
    auto result = std::vector<my_machine::path>{};
    if(my_machine::exists(dir))
    {
        for (auto const & entry : 
            my_machine::recursive_directory_iterator(
                dir, 
                my_machine::directory_options::follow_directory_symlink
            ))
        {
            if(my_machine::is_regular_file(entry) && 
                filter(entry))
            {
                result.push_back(entry);
            }
        }
    }

    return result;
}
