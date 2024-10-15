// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Sometimes you need to wokr with data stored in your disk, rather than
 * provided by an user, it can be databases, flat files (text or binary data),
 * among others.
 * 
 * Here we use the raw data (unstructured data) of the file and we consider
 * it in a buffer that can be an array, a std::vector or a std::array. For
 * this purpose we will use ofstream and ifstream classes that are available in
 * the std namespace of the <fstream> header.
 */

#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
    std::cout << "Lesson 1: Reading and writing raw data from/to binary files"
              << std::endl;

    // Info #1: Open a file stream for writing a binary file, 
    // with std::ofstream
    std::ofstream out_file("my_bin.bin", std::ios::binary);
    std::cout << "Opened filestream for my_bin.bin ...\n" << std::endl;

    // Info #2: Checking that the file is really opened with is_open() member
    if(out_file.is_open())
    {
        // Info #3: Wrting content
        std::cout << "Checked that filestream is opened ..." << std::endl;
        std::vector<unsigned char> content {1, 6, 2, 0};
        out_file.write(reinterpret_cast<char*>(content.data()), 
            content.size());

        // flush()?
    }
    return 0;
}