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
    auto link_path = desired_path / "text_link.txt";
    my_machine::create_symlink(moved_file_path, link_path, err);
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
}