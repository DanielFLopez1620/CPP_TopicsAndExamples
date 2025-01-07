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
 */

#include <filesystem>
#include <chrono>
#include <iomanip>

namespace my_machine = std::filesystem;

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(
        tp - TP::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

int main(int argc, char* argv[])
{
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
    std::cout << "\tSize of the file:" << size << std::endl;
    return 0;
}