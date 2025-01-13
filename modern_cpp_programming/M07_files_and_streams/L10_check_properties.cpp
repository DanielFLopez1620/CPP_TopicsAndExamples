// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * As you may suppose, if the 'filesystem' library allow us to work with
 * the files and dirs present in our machine, it should know the permissions.
 * It is right, filesystem at first will be only capable of using files or
 * dirs available according to the permissions of the execution. However, you
 * can check the existance and propierties of these elements, including
 * permissions.
 * 
 * Most of the functions are easy to understand, they are presented below in
 * the main. However, keep in mind the next points:
 * 
 * - You can check if a file exists with 'exists()' and a path, or a
 *   'std::filesystem::file_status' retrieved previosly using 'status()'.
 * - The 'equivalent()' function checks that two filesystem objects have
 *   the smae status result.
 * - 'file_
 *      size' only works with files and symbolic links that target to files,
 *   otherwise it will return a -1 if an error occurred.
 * - 'last_write_time()' has two overloads, one to get and other to set the
 *   last time of modification, which is of type 
 *   'std::filesystem::file_time_type'.
 * - 'status()' determines the type and permissions of a filesystem object, but
 *   in the case of a symbolic link, it will return the target files
 *   properties. So to retrieve the status of a symbolic link you have to use
 *   'symlink_status()'.
 * - Permissions are defined as an enumeration, to set or remove perms you have
 *   to use 'add_perms' and 'remove_perms':
 * 
 *          my_machine::permissions(
 *              <path>,
 *              my_machine::perms::add_perms |
 *              my_machine::perms::owner_all |
 *              my_machine::perms::group_all,
 *              err
 *          )
 * When ready, you can compile and run this code with:
 * 
 *      g++ -std=c++17 
 *          modern_cpp_programming/M07_files_and_streams/L10_check_properties.cpp
 *          -o check_file.out
 *      ./check_file.out
 */

// ------------------------------- REQUIRED LIBRARIES -------------------------
#include <filesystem>  // Filesystem library
#include <chrono>      // Time management with different precisions
#include <iomanip>     // Input/Output Manipulators

// ----------------------------- NAMESPACES TO CONSIDER ----------------------- 
namespace my_machine = std::filesystem;

// ---------------------------- TEMPLATES USED -------------------------------
template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(
        tp - TP::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

// ---------------------------- MAIN IMPLEMENTATION ---------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 10: Properties in filesystem...\n" << std::endl;
    
    auto file_path = my_machine::current_path() / "modern_cpp_programming"
        / "M07_files_and_streams" / "L08_working_with_files.cpp";
    auto err = std::error_code{};

    std::cout << "Checking file properties for L08_working_with_files.cpp"
              << std::endl;

    // Info #2: You can check a file exist, with 'exists()' member:
    auto flag = my_machine::exists(file_path, err);
    std::cout << "\tFile exists?: " << std::boolalpha << flag << std::endl;

    // Info #3: You can compare two filesystem obj and check if they are the
    // same with 'equivalent()' member-
    flag = my_machine::equivalent(file_path, my_machine::current_path() 
        / "modern_cpp_filesystem");
    std::cout << "\tIs the same path as dir 'modern_cpp_programming?: "
              << std::boolalpha << flag << std::endl;

    // Info #4: You can check the size of a file with 'file_size()' member.
    auto size = my_machine::file_size(file_path, err);
    std::cout << "\tSize of the file: " << size << "bytes." << std::endl;

    // Info #5: You can check the number of hardlinks with 'hard_link_count()'
    // member, if you do not know what is a hard link, do not worry, in simple
    // words it is an additional name for an existing files.
    std::cout << "\tNumber of hardlinks: ";
    auto hardlinks = my_machine::hard_link_count(file_path, err);
    if(hardlinks != static_cast<uintmax_t>(-1))
    {
        std::cout << hardlinks << std::endl; 
    }
    else
    {
        std::cout << "Error... " << err << std::endl; 
    }

    // Info #6: You can also check the property for the last time a file was
    // modified (writing operation,, can include deletions).
    auto last_modified = my_machine::last_write_time(file_path, err);
    auto time = to_time_t(last_modified);
    auto localtime = std::localtime(&time);
    std::cout << "\tLast modification: " << std::put_time(localtime, "%c")
              << std::endl;

    // Info #7: As you may be wondering by this time, what about permissions? 
    // Well you can use the member 'perms' with its submemebrs to check which
    // are active for the owner, group or others. For this we use a lambda.
    auto ls_al_file = [](my_machine::perms perms)
    {
        using my_perm = my_machine::perms;
        auto ow_r = ((perms & my_perm::owner_read) != my_perm::none ?
            "r" : "-");
        auto ow_w = ((perms & my_perm::owner_write) != my_perm::none ?
            "w" : "-");
        auto ow_x = ((perms & my_perm::owner_exec) != my_perm::none ?
            "x" : "-");
        auto gr_r = ((perms & my_perm::group_read) != my_perm::none ?
            "r" : "-");
        auto gr_w = ((perms & my_perm::group_write) != my_perm::none ?
            "w" : "-");
        auto gr_x = ((perms & my_perm::group_exec) != my_perm::none ?
            "x" : "-");
        auto ot_r = ((perms & my_perm::others_read) != my_perm::none ?
            "r" : "-");
        auto ot_w = ((perms & my_perm::others_write) != my_perm::none ?
            "w" : "-");
        auto ot_x = ((perms & my_perm::others_exec) != my_perm::none ?
            "x" : "-");
        std::cout << "\tPermissions: " << ow_r << ow_w << ow_x << " | " 
                  << gr_r << gr_w << gr_x << " | " << ot_r << ot_w << ot_x
                  << std::endl;
    };
    auto status = my_machine::status(file_path, err);
    ls_al_file(status.permissions());

    // Info #8: You can also check if the provided path is a file, a dir or a
    // symlink with the booleans members functions presented below:
    std::cout << std::boolalpha << "\tRegular file?: "
              << my_machine::is_regular_file(file_path, err) << std::endl
              << "\tDirectory?: "
              << my_machine::is_directory(file_path, err) << std::endl
              << "\tSymlink?: "
              << my_machine::is_symlink(file_path, err) << std::endl;

    return 0;

} // main()