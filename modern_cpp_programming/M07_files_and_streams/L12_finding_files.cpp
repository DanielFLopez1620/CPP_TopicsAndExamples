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
 * To search for files or dirs we want, we require to iterate over the through
 * the entries, then we can use the 'recursive_directory_iterator' in order to
 * explore one path and search for a pattern (it can be validated using a 
 * function), when doing this you should consider following the symlinks with
 * the option 'follow_directory_symlink' in the 'filesystem::directory_option'.
 * 
 * When ready, compile and run the code with:
 * 
 *      g++ -std=c++17 L11_enum_content.cpp -o enum_content.out
 *      ./enum_content.out
 *      g++ -std=c++17 L12_finding_files.cpp -o search.out
 *      ./search.out
 */


// -------------------------- REQUIRED LIBRARIES ------------------------------
#include <filesystem> // For using the machine's filesystem
#include <vector>     // For dynamic arrays usage
#include <functional> // Related with functions implementations

// -------------------------- NAMESPACES CONSIDERED --------------------------
namespace my_machine = std::filesystem;

// --------------------------- FUNCTION PROTOTYPES ----------------------------
std::vector<my_machine::path> search_file(
    my_machine::path const & dir,
    std::function<bool(my_machine::path const&)> filter);

// --------------------------------- MAIN IMPLEMENTATION ----------------------
int main(int argc, char* argv[])
{
    // Info #1: You can search for files that start or contains certain pattern
    // by using a lambda with a str member function to find it.
    std::cout << "Searching for files that start with 'info': " << std::endl;
    auto founds = search_file(my_machine::current_path() / "example",
        [](my_machine::path const & entry)
        {
            // Convert to wstring
            auto filename = entry.wstring();

            // Compare the find position and validate it isn't outside the size
            return filename.find(L"info") != std::wstring::npos;
        });
    for (auto const & element : founds)
    {
        std::cout << "\t" << element << std::endl;
    }

    // Info #2: You can also search according extensions, by using the
    // 'extension' member.
    std::cout << "Searching for files that  have .txt ext': " << std::endl;
    founds = search_file(my_machine::current_path() / "example",
        [](my_machine::path const & entry)
        {
            return entry.extension() == L".txt";
        });
    for (auto const & element : founds)
    {
        std::cout << "\t" << element << std::endl;
    }

    return 0;

} // main()

// ------------------------------- FUNCTION DEFINITIONS -----------------------

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

} // search_file()
