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
 * 
 * You already know some elements like cin, cout for I/O operations.But there
 * are more like:
 * 
 * - cin/wcin: Input stream typically used for reading inputs from the keyboard,
 *   and its wide-character version for non-ASCII characters.
 * - cout/wcout: Output stream used to display information on the console, and
 *   its wide-character version.
 * - cerr/wcerr: Error stream, messages that aren't buffered and go immediately
 *   to the console, and its wide-character variant.
 * - clog/wclog: Logging stream, which means that it can accumulate messages
 *   and output them in bulk for better performance. Also with its wide-
 *   character version.
 * 
 * However, there are streams for files too, which can be implemented based on
 * the following class templates:
 * 
 * - basic_filebuf: Implements I/O operations for a raw file, similar to the C
 *   FILE stream.
 * - basic_ifstream: Oriented for high-level stream input operations.
 * - basic_ofstream: Oriented for high-level stream output operations.
 * - basic_fstream: Implements high-level stream input and output.
 * 
 * The implementations that we are going to use are ofstream and ifstream,
 * present on the <fstream> header under the std namespace.
 * 
 * To wirte data into a file you need to instantiate an std::ofstream where you
 * need to pass the name of the file and the open mode. In this case, we are
 * going to use the std::ios::binary to indicate that we are working in the
 * binary mode, which discards the previous content when opening it.
 * 
 * NOTE: For better understanding on file stream, check the image:
 * https://static.packt-cdn.com/products/9781800208988/graphics/Images/B15880_07_01.png
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
    std::cout << "Writing operations with files..." << std::endl
              << "\tOpened ofstream for my_bin.bin ..." << std::endl;

    // Info #2: Checking that the file is really opened with is_open() member
    if(out_file.is_open())
    {
        // Info #3: Wrting content
        std::cout << "\tChecked that filestream is opened ..." << std::endl;
        std::vector<unsigned char> content {1, 6, 2, 0};
        out_file.write(reinterpret_cast<char*>(content.data()), 
            content.size());
        std::cout << "\tOutput was written succesfully..." << std::endl;

        // Info #4: Flush can be used to ensure that the output is immediately
        // send to the destination. In this case, for the output file.
        // std::flush();

        // Info #5: Close the stream to the file, and also calls the flush, that
        // is why the previous line is commented.
        out_file.close();
    }

    // Info #6: For reading a file you will need a ifstream (input stream)
    // rather than a output stream. Which is like the next one:
    std::ifstream in_file("my_bin.bin", std::ios::binary);
    std::cout << "Reading operations with files..." << std::endl
              << "\tOpened ifstream for my_bin.bin" << std::endl;

    // Info #7: Even when reading a file, you must ensure that it was opened.
    if(in_file.is_open())
    {   
        // Info #8: When reading a file, you must know its lenght to avoid
        // surpasing it, which can lead to corruption or bad operations.
        in_file.seekg(0, std::ios_base::end);
        auto len = in_file.tellg();
        in_file.seekg(0, std::ios_base::beg);
        std::cout << "\tObtained lenght: " << len << std::endl;

        // Info #9: Allocate memory to read the content of the file, and 
        // as you suppose, you will need to understand the data type of the
        // binary or the structure of the raw info.
        std::vector<unsigned char> stored_info;
        stored_info.resize(static_cast<size_t>(len));
        std::cout << "\tReserved buffer for reading..." << std::endl;

        // Info #10: Read the content in the buffer you created
        in_file.read(reinterpret_cast<char*>(stored_info.data()), len);
        std::cout << "\tReading process was completed..." << std::endl;

        // Info #11: Check that the reading operation was achieved
        auto success = !in_file.fail() && len == in_file.gcount();
        std::cout << "\tChecking reading status: " << success << std::endl;

        // Info #12: Do not forget to close the stream
        in_file.close();
        std::cout << "\tClosed stream..." << std::endl;
    }

    
    return 0;
}