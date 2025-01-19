// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * We explored a little of <filesystem> header related with paths. However, it
 * isn't it only focus as you can copy, move and delete files or directories,
 * no matter if it is Windows or POXIS filesystem.
 * 
 * The filesystem functions, members and methods allow to interact with files
 * and dirs, also the functions can be classified in two groups:
 * 
 * - Overloads that take a reference to a 'std::error_code' which allow for
 *   handling errors without exceptions (noexcept).
 * - Overloads that do not handle 'std::error_code' and throws 
 *   'std::filesystem::filesystem_error' or 'std::bad_alloc'.
 * 
 * Check which functions return a boolean as it can be helpful to notice if an
 * action was completed or not (in cases where no error/exception is thrown).
 * Also, you should note the difference between the functions that are for
 * dirs and the ones for files as the management can be different and can
 * result in errors if they are done wrong. (Do not forget to implement the
 * proper try-catch if using these)
 * 
 * When making copies, review which 'copy_option' is better for you
 * as they are:
 * 
 * - 0 = none (Follow symbolic link)
 * - 1 = skip_existing
 * - 2 = overwrite_existing
 * - 4 = update_existing
 * - 8 = recursive (copy subdirectories and their contents)
 * - 16 = copy_symlinks (make the copy as symlink)
 * - 32 = skip_symlinks (Ignore symbolic links)
 * - 64 = directories_only
 * - 128 = create_symlinks (Make symlinks instead of copying files)
 * - 265 = create_hard_links (Hard links instaed of copies and symlinks)
 * 
 * Finally, check below for operations like copying, moving, renaming and deleting file
 * and directories.
 * 
 * When ready you can compile this with:
 * 
 *      g++ -std=c++17 L08_working_with_files.cpp -o file_systems.out
 *      ./file_systems.out
 * 
 * NOTE: Where you compile the code, must have the /08_temp/08_text elements,
 * by default we are considering the path to the repository in the localtion
 * of the Module 7.
 */

// ----------------------------- REQUIRED LIBRARIES ---------------------------
#include <filesystem>  // Management of the file system
#include <iomanip>     // Input/Output manipulators

// -------------------------- NAMESPACES CONSIDERED ---------------------------
namespace my_machine = std::filesystem;

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    // Info #1: You can access to your current location and part from them to
    // explore the filesystem with the operator /:
    auto err = std::error_code{};
    auto current_path = my_machine::current_path();
    auto desired_path = current_path / "08_temp";
    auto txtfile_path = desired_path / "08_text.txt";

    // Info #2: To create directories, you can consider the given path. The
    // path must include a directory in its last space to create. For this you
    // can use create_directory().
    auto suc_create = my_machine::create_directory(desired_path, err);
    std::cout << "Simple directory 08_temp was created: " << std::boolalpha
              << suc_create << std::endl;
    auto temp_path = desired_path / "tmp16" / "tmp20"; 
    suc_create = my_machine::create_directories(temp_path, err);
    std::cout << "Temporal directores were created: " << std::boolalpha
              << suc_create << std::endl;

    // Info #3: You can move files with rename(), it is curius that to
    // rename files in Linux you have to move it (even if it is just a name
    // change) and here is the oppositive. You can rename it if the same path
    // with different dir names is provided.
    auto mov_path = desired_path / "tmp20";
    my_machine::rename(temp_path, mov_path, err);
    if (err) 
    {
        std::cout << "Error while moving tmp20: " << err.message() << std::endl;
    }
    else
    {
        std::cout << "Moved tmp20 succesfully..." << std::endl;
    }

    // Info #4: You can also copy files and directories in a recursive way by
    // using copy() with 'copy_options::recursive':
    my_machine::copy(desired_path, current_path / "another_tmp",
        my_machine::copy_options::recursive, err);
    if (err)
    {
        std::cout << "Couldn't copy directories: " << err.message() << std::endl;
    }
    else
    {
        std::cout << "Copy directories... to current path..." << std::endl;
    }

    // Info #5: You can even create symbolic links to the directories with
    // create_directory_symlink()
    auto link_path = current_path / "symlink_to_tmp";
    my_machine::create_directory_symlink(temp_path, link_path, err);
    if(err)
    {
        std::cout << "Symlink wasn't created: " << err.message() << std::endl;
    }
    else
    {
        std::cout << "Symlink created successfully..." << std::endl;
    }

    // Info #6: For deleting, similar to the case of rm, you can erase a empty
    // folder with 'remove()', but for the case of a folder and you want to delete
    // it recursively, you have to use 'remove_all()'.
    auto del_path = desired_path /"tmp16";
    suc_create = my_machine::remove_all(del_path, err) != 
        static_cast<std::uintmax_t>(-1);
    if(!suc_create)
    {
        std::cout << "Couldn't delete temporal path...: " << err.message() 
                  << std::endl;
    }
    else
    {
        std::cout << "Temportal path dirs were deleted!" << std::endl; 
    }

    // Info #7: You can also perform operation with files, for example, copy 
    // perations with 'copy()' or 'copy_file()'.
    suc_create = my_machine::copy_file(txtfile_path, 
        current_path / "08_copied_file.txt", err);
    if(suc_create)
    {
        std::cout << "Copied file 08_sample.txt to current destination" 
                  << std::endl;
    }
    else
    {
        std::cout << "Copy of file 08_sample.txt failed..." << std::endl;
    }

    // Info #8: Similar to what happens with dirs, you can rename and mvoe 
    // files with 'rename()'.
    auto moved_file_path = current_path / "08.log";
    my_machine::rename(txtfile_path, moved_file_path, err);
    if (err)
    {
        std::cout << "Couldn't move/rename the file 08_sample.txt: "
                  << err.message() << std::endl;    
    }
    else
    {
        std::cout << "File 08_sample.txt moved and renamed..." << std::endl;
    }

    // Info #9: You can also create symboloic links for files with 
    // 'create_symlink()':
    auto link_file_path = desired_path / "text_link.txt";
    my_machine::create_symlink(moved_file_path, link_file_path, err);
    if(err)
    {
        std::cout << "Couln't create symlink for file: " << err.message()
                  << std::endl;
    }
    else
    {
        std::cout << "Symlink fro fiel created" << std::endl;
    }

    // Info #10: Finally, you can also remove files.
    suc_create = my_machine::remove(mov_path, err);
    if (!suc_create)
    {
        std::cout << "File wasn't removed, error: " << err.message()
                  << std::endl;
    }
    else
    {
        std::cout << "File removed succesfully..." << std::endl;
    }

    return 0;
} // main()