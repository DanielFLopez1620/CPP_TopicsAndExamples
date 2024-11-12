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
 * OUTPUT STREAM (Write):
 * 
 * To write data into a file you need to instantiate an std::ofstream where you
 * need to pass the name of the file and the open mode. In this case, we are
 * going to use the std::ios::binary to indicate that we are working in the
 * binary mode, which discards the previous content when opening it.
 * 
 * If you want to use a file (open it) with th existing content, you should
 * consider using the flag 'std::ios::app' (which traslates to 
 * std::ios::app | std::ios::binary), this operations call the open() method
 * internally. 
 * 
 * Remember to check that the file is open (and ready) before you start
 * using the stream. For that you can use the class member 'is_open()'. After
 * this check, you should be able to use 'write()' class member to modify and
 * write content to the file. 'write()' only accepts pointers to string, so if
 * you do not use a string, then you need to use a 'reinterpret_cast'. Also,
 * when writing a file, you should check and prevent errors, then a exception
 * you should know is 'std::ios_base::failure'.
 * 
 * INPUT STREAM (Read):
 * 
 * To read data you will also need a stream, but in this case a 'std::ifstream'
 * and you muss open the file and check it is open like in a writting
 * operation. 
 * 
 * A highlight to mention here is that you can also open the file (with the
 * class member open()) with the option std::ios::binary.
 * 
 * One of the most important thing to consider when using a file with content
 * is to determinate the size of the file and how is the data structured. In 
 * the case presented below, we already know the type (check below to see
 * the std::vector implementation), but we need the size, for that reason
 * we use pointers with the method 'seekg()', which allow us to move through
 * the text; and 'tellg()' that tells our current position that can be
 * understood as bit size we have to interpretate to determinate the size of
 * the file.
 * 
 * After this you should be able to read the file (with the class member 
 * 'read()' ), which will create a string pointer to the content. As the 
 * stream works with characters you should use 'reinterpret_cast' in case
 * you need to convert the data to a different format you may need.
 * 
 * An additional comment, is that yoou can open the file and move directly to
 * the end by using 'std::ios:ate' as an argument when opening the file. Also,
 * you can check the number of characters succesfully read by using the
 * 'gcount()' method.
 * 
 * Now go and check the code, you can compile and run it with:
 * 
 *      g++ -std=c++17 L01_rm_raw_binary -o read_write_bin.out
 *      ./read_write_bin.out
 * 
 * Before finishing, you should consider that there is more than one way of
 * reading a file. Some of them will be explored throuhgout the module, but
 * it will depend on your preferences and your application.
 * 
 * 
 * NOTE: For better understanding on file stream, check the image:
 * https://static.packt-cdn.com/products/9781800208988/graphics/Images/B15880_07_01.png
 */

// -------------------- REQUIRED LIBRARIES ------------------------------------

#include <fstream>    // File stream library
#include <vector>     // For dynamic arrays
#include <functional> // Related with functions and args

// ---------------------- FUNCTION PROTOTYPES --------------------------------

bool custom_write_data(char const * const filename,
    char const * const data, size_t const size);
size_t custom_read_data (char const * filename,
    std::function<char*(size_t const)> allocator);

// ------------------------ MAIN IMPLEMENTATION -------------------------------
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

    // Info #13: You can open the file to directly initialize a std::vector
    // using 'std::istreambuf_iterator' iterators (which can be used with
    // std::string too).
    std::vector<unsigned char> chr_input;
    std::ifstream in_file2("my_bin.bin", std::ios::binary);
    if(in_file2.is_open())
    {
        chr_input = std::vector<unsigned char>(
            std::istreambuf_iterator<char>(in_file2),
            std::istreambuf_iterator<char>());
        std::cout << "Opening file content additional way 2: Direct init:" 
                  << std::endl;   
        in_file2.close();
    }
    std::cout << "\tDisplaying content: ";
    for (auto let : chr_input)
    {
        std::cout << static_cast<int>(let);
    }
    std::cout << std::endl;

    // Info #14: Another form is by using the std::vector for assignation
    // from std::istreambuf_iterator.
    std::vector<unsigned char> chr_content;
    std::ifstream in_file3("my_bin.bin");
    if(in_file3.is_open())
    {
        std::cout << "Opening file content additional way 2: Assign:" 
                  << std::endl;
        in_file3.seekg(0, std::ios_base::end);
        auto len3 = in_file3.tellg();
        in_file3.seekg(0, std::ios_base::beg);
        chr_content.reserve(static_cast<size_t>(len3));
        chr_content.assign(
            std::istreambuf_iterator<char>(in_file3),
            std::istreambuf_iterator<char>());
        in_file3.close();
    }
    std::cout << "\tDisplaying content: ";
    for (auto let : chr_content)
    {
        std::cout << static_cast<int>(let);
    }
    std::cout << std::endl;

    // Info #15: Another option is to copy the content of the file stream by
    // using std::istreambuf_iterator iterators and std::back_inserter to
    // write to the end of the vector.
    std::vector<unsigned char> chr_cop;
    std::ifstream in_file4("my_bin.bin", std::ios::binary);
    if(in_file4.is_open())
    {
        std::cout << "Opening file content addional way 3: Copying:"
                  << std::endl;
        in_file4.seekg(0, std::ios_base::end);
        auto len4 = in_file4.tellg();
        in_file4.seekg(0, std::ios_base::beg);
        chr_cop.reserve(static_cast<size_t>(len4));
        std::copy(std::istreambuf_iterator<char>(in_file4),
            std::istreambuf_iterator<char>(),
            std::back_inserter(chr_cop));
        in_file4.close();
    }
    std::cout << "\tDisplaying content: ";
    for (auto let : chr_cop)
    {
        std::cout << static_cast<int>(let);
    }
    std::cout << std::endl << "Do not forget the next notes:" << std::endl
              << "\tThe first open/read option is the fastest one" << std::endl
              << "\tCheck the function implementations for r/w" << std::endl;
    
    return 0;

} // main()

// ---------------------------- FUNCTION DEFINITIONS --------------------------

/**
 * Write the data provided to the specified file in binary mode
 * 
 * @param filename Output file
 * @param data Data to write
 * @param size Size of the data considered
 * 
 * @return True if the writting was succesful, False otherwise.
 */
bool custom_write_data(char const * const filename,
    char const * const data, size_t const size)
{
    auto success = false;
    std::ofstream out_file(filename, std::ios::binary);
    if(out_file.is_open())
    {
        try
        {
            out_file.write(data, size);
            success = true;
        }
        catch(const std::ios_base::failure &e)
        {
            std::cerr << e.what() << std::endl;
        }
        out_file.close();
    }
    return success;
} // custom_write_data()

/**
 * Read the content of the given file and return it.
 * 
 * @param filename Input file
 * @param allocator Function for allocation process
 * 
 * @return Read bytes.
 */
size_t custom_read_data (char const * filename,
    std::function<char*(size_t const)> allocator)
{
    size_t readbytes = 0;
    std::ifstream in_file(filename, std::ios::ate | std::ios::binary);
    if(in_file.is_open())
    {
        auto length = static_cast<size_t>(in_file.tellg());
        in_file.seekg(0, std::ios_base::beg);
        auto buffer = allocator(length);
        try
        {
            in_file.read(buffer, length);
            readbytes = static_cast<size_t>(in_file.gcount());
        }
        catch(std::ios_base::failure &e)
        {
            std::cerr << e.what() << std::endl;
        }
        in_file.close();        
    }
    return readbytes;
} // custom_read_data()