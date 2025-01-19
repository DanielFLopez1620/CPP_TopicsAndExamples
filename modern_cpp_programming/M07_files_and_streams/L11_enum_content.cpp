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
 * 
 * You will check tree forms of enumeration of a dir (non-iterative, iterative
 * and structured iterative). However, keep in mind the next before checking
 * the code:
 * 
 * - The order of the iterations is unspecified.
 * - Each entry is visited only once.
 * - '.' and '..' are skipped.
 * - A default-constructed iterator is the end iterator.
 * - Two end iterators are always equal.
 * - When iterated past the last directory entries, it becomes the end iterator.
 * - If something is created after the iterator was created, it is not
 *   specified what will happen.
 * - begin() and end() are applicable for both directory iterators presented.
 * - The iterators present overloaded constructors for:
 *   - none : No specification
 *   - follow_directory_symlink : Iteration that follows symbolic links.
 *   - skip_permission_denied: Omit entries that may send access denied error.
 * - Do not forget the difference between symlink_status()' and 'status()'.
 * - 'visit_directory_rec()' is non-recursive and uses 
 *   'recursive_diretory_iterator', while 'visit_directory()' is recursive and
 *   uses 'directory_iterator'
 * 
 * When you are ready, you can run:
 * 
 *      g++ -std=c++17 L11_enum_content.cpp -o enum_content.out
 *      ./enum_content.out
 * 
 */

// --------------------------- REQUIRED LIBRARIES -----------------------------
#include <filesystem>  // For managing the machine's filesystem
#include <fstream>     // File stream (output/input)

// -------------------------- NAMESPACES CONSIDERED ---------------------------
namespace my_machine = std::filesystem;

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 11: Enumerating the content of a dir\n" << std::endl;

    // Path considered for exersize
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
    std::cout << "Non-recursive iteration of a dir: " << std::endl;
    if (my_machine::exists(base_path) && my_machine::is_directory(base_path))
    {
        for (auto const & entry : my_machine::directory_iterator(base_path))
        {
            auto filename = entry.path().filename();
            if(my_machine::is_directory(entry.status()))
            {
                std::cout << "\t[dir]: " << filename << std::endl;
            }
            else if(my_machine::is_symlink(entry.status()))
            {
                std::cout << "\t[sym]: " << filename << std::endl;
            }
            else if(my_machine::is_regular_file(entry.status()))
            {
                std::cout << "\t[file]: " <<  filename << std::endl;
            }
            else
            {
                std::cout << "\t[?]: " << filename << std::endl;
            }
        }
    }

    // Info #3: Howevere, you can go iteratively in the subdirectories of a
    // directory and then iterate over them while making the list with
    // 'recursive_directory_iterator()'.
    std::cout << "Recursive iteration of a dir: " << std::endl;
    if(my_machine::exists(base_path) && my_machine::is_directory(base_path))
    {
        for(auto const & entry : 
            my_machine::recursive_directory_iterator(base_path))
        {
            auto filename = entry.path().filename();
            if(my_machine::is_directory(entry.status()))
            {
                std::cout << "\t[dir]: " << filename << std::endl;
            }
            else if(my_machine::is_symlink(entry.status()))
            {
                std::cout << "\t[sym]: " << filename << std::endl;
            }
            else if(my_machine::is_regular_file(entry.status()))
            {
                std::cout << "\t[file]: " <<  filename << std::endl;
            }
            else
            {
                std::cout << "\t[?]: " << filename << std::endl;
            }
        }
    }

    // Info #4: Structured iteration over the content of a directory with
    // 'directory_iterator' and recursive iteration for subdirectories:
    std::cout << "Structured enumeration of a dir: " << std::endl;
    auto level = 0;
    bool const recursive = false;
    if (my_machine::exists(base_path) && my_machine::is_directory(base_path))
    {
        auto lead = std::string(level * 3, ' ');
        for (auto const & entry : my_machine::directory_iterator(base_path))
        {
            auto filename = entry.path().filename();
            if (my_machine::is_directory(entry.status()))
            {
                std::cout << "\t[dir]: " << filename << std::endl;
                for (auto const & subentry : 
                    my_machine::directory_iterator(base_path / filename))
                {
                    auto filename = subentry.path().filename();
                    if(my_machine::is_directory(subentry.status()))
                    {
                        std::cout << "\t\t[dir]: " << filename << std::endl;
                    }
                    else if(my_machine::is_symlink(subentry.status()))
                    {
                        std::cout << "\t\t[sym]: " << filename << std::endl;
                    }
                    else if(my_machine::is_regular_file(subentry.status()))
                    {
                        std::cout << "\t\t[file]: " <<  filename << std::endl;
                    }
                    else
                    {
                        std::cout << "\t\t[?]: " << filename << std::endl;
                    }
                }
            }
            else if(my_machine::is_symlink(entry.status()))
            {
                std::cout << "\t[sym]: " << filename << std::endl;
            }
            else if(my_machine::is_regular_file(entry.status()))
            {
                std::cout << "\t[file]: " <<  filename << std::endl;
            }
            else
            {
                std::cout << "\t[?]: " << filename << std::endl;
            }
        }
    }

    return 0;

} // main()