// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * In the previous lesson we worked with unstructured (raw) data related with
 * writing and reading operations. However, as you may know, most of the time
 * we work with structured data that should be persisted in files. Also, the
 * previous lesson only works with POD data, then for new objects we must
 * explicitly decide what to write or read, and how to do it. 
 * 
 * For this you can still use "ofstream" (output file stream) and "ifstream"
 * (input file stream) present in the <fstream> header to write/read files, but
 * as will check later, you will have to know the structure of the elements
 * present in the file, in this cases with a class (and its attributes) or a
 * struct, where you should consider the size of each reading and reinterpret
 * the cast in order to make it compatible with the reading/writting operation.
 * 
 * This process is called serialization and deserialization, and you should not
 * do it with pointers as they change in processes even some moments later,
 * then they become meaningless. But you should write data referred by a
 * pointer and read data into an object referred by a pointer. Also, you should
 * consider versioning the data in the process of serialization/deserialization
 * if it is open to change over time.
 * 
 * Also, down below you will discover how to override operators << >> to write
 * the content to files, which allow a more generic code for interacting with
 * streams.
 * 
 * NOTE: Remember to read until the file ends or when you receive a exception,
 * always consider this exception management to avoid corruption or reading
 * external directions of your objective. The end of the file is marked with
 * the eofbit of the stream.
 */

// ------------------------------ REQUIRED LIBRARIES --------------------------
#include <vector>   // For dynamic-memory arrays
#include <fstream>  // For file streams management

// ---------------------------- STRUCTURE DEFINITIONS ------------------------

// POD type structure which is inteded to be save in a file
struct pod_msg_to_file
{
    int num;
    char priority;
    char content[2];
};

// -------------------------- CLASS DEFINITIONS -----------------------------

/**
 * Class non-pod oriented to test writing and reading in files.
 */
class msg_to_file
{
    int num;         // Number of message
    char priority;   // Priority letter
    std::string msg; // Content

public:
    /**
     * User defined construtor that initialize the attributes with a default
     * value, if there aren't arguments passed during the call.
     * 
     * @param num Number of message
     * @param priority Letter that indicates priority
     * @param msg String with the content of the message
     */
    msg_to_file(int const num = 0, char const priority = '0',
        std::string const & msg = {}) : num(num), priority(priority), msg(msg)
    {}

    // Default copy constructor
    msg_to_file(msg_to_file const &) = default;
    
    // Default copy constructor
    msg_to_file& operator=(msg_to_file const &) = default;
    
    /**
     * Equality operator that checks each attribute in order to validate the
     * comparation.
     * 
     * @param rhv Right hand element to compare.
     * 
     * @return True if all the attributes are equal, False otherwise.
     */
    bool operator==(msg_to_file const & rhv) const
    {
        return num == rhv.num && priority == rhv.priority && msg == rhv.msg;
    } // operator==

    /**
     * Inequality operator that checks each attribute in order to validate the
     * comparation.
     * 
     * @param rhv Right hand element to compare.
     * 
     * @return True if the attributes (at least one) is different, False 
     *         otherwise.
     */
    bool operator!=(msg_to_file const & rhv) const
    {
        return !(*this == rhv);
    } // operator!=

    /**
     * Write method for file out streams to write the content as the class
     * attributes aren't pod types.
     * 
     * @param out_file Output file stream considered.
     * 
     * @return True if the operation ends succesfully, false otherwise.
     */
    bool write_nonpod(std::ofstream& out_file) const
    {
        out_file.write(reinterpret_cast<const char*>(&num), sizeof(num));
        out_file.write(&priority, sizeof(priority));
        auto size = static_cast<int>(msg.size());
        out_file.write(reinterpret_cast<char*>(&size), sizeof(size));
        out_file.write(msg.data(), msg.size());
        return !out_file.fail();
    } // write_nonpod

    /**
     * Read method for file input streams, in order to enter the content
     * of the file (that is formatted properly for this class) without
     * errors.
     * 
     * @param in_file Input file stream
     * 
     * @return True if the reading was succesful, false otherwise.
     */
    bool read_nonpod(std::ifstream& in_file)
    {
        in_file.read(reinterpret_cast<char*>(&num), sizeof(num));
        in_file.read(&priority, sizeof(priority));
        auto size {0};
        in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
        msg.resize(size);
        in_file.read(reinterpret_cast<char*>(&msg.front()), size);
        return !in_file.fail();
    } // read_nonpod()

    // Friend member declaration
    // They can access private and protected data of the classes in which they
    // are declared friends.

    // Override of operator<< to write into a file
    friend std::ofstream& operator<<(std::ofstream& out_file, 
        msg_to_file const& msg);
    // Override of operator>> to read a file
    friend std::ifstream& operator>>(std::ifstream& in_file, 
        msg_to_file& msg);

}; // class msg_to_file

// ----------------------------- FUNCTION DEFINITIONS -------------------------

/**
 * Override to write the content (attributes) of the msg_to_file class to
 * a file.
 * 
 * @param out_file Output stream
 * @param msg Pointer to obj with the msg to insert in the file.
 * 
 * @return Output stream after sending the content.
 */
std::ofstream& operator<<(std::ofstream& out_file, msg_to_file const& msg)
{
    out_file.write(reinterpret_cast<const char*>(&msg.num), sizeof(msg.num));
    out_file.write(&msg.priority, sizeof(msg.priority));
    auto size = static_cast<int>(msg.msg.size());
    out_file.write(reinterpret_cast<char*>(&size), sizeof(size));
    out_file.write(msg.msg.data(), msg.msg.size());
    return out_file;
} // operator<<

/**
 * Override to read the content (attributes, if formatted was properly made) 
 * of the msg_to_file class to the current program.
 * 
 * @param in_file Input stream
 * @param msg Pointer to object where the content is goint to be read.
 * 
 * @return Input stream after reading the content.
 */
std::ifstream& operator>>(std::ifstream& in_file, msg_to_file& msg)
{
    in_file.read(reinterpret_cast<char*>(&msg.num), sizeof(msg.num));
    in_file.read(&msg.priority, sizeof(msg.priority));
    auto size { 0 };
    in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
    msg.msg.resize(size);
    in_file.read(reinterpret_cast<char*>(&msg.msg.front()), size);
    return in_file;
} // operator>>

/**
 * Adding operator of equality for custom pod struct that was previously
 * defined.
 * 
 * @param f1 First element to compare
 * @param f2 Second element to compare
 * 
 * @return True if all the pair elements are equal, false otherwise.
 */
bool operator==(pod_msg_to_file const & f1, pod_msg_to_file const & f2)
{
    return f1.num == f2.num &&
           f1.priority == f2.priority &&
           f1.content[0] == f2.content[0] &&
           f1.content[1] == f2.content[1];
} // operator==

// ------------------------------ MAIN IMPLEMENTATION -------------------------

int main(int argc, char* arv[])
{
    std::vector<pod_msg_to_file> pod_content {
        {16, '1', {'2', '0'}},
        {20, '2', {'1', '6'}}};

    // Info #1: To serailize/deserialize POD types that doesn't have pointers,
    // you can use ofstream::write() and ifstream::read() as it was shown in
    // the previuos lesson.
    std::ifstream out_file1("L02_example.bin", std::ios::binary);
    if(out_file1.is_open())
    {
        for(auto const & value : pod_content)
        {
            out_file1.write(reinterpret_cast<const char*>(&value), 
                sizeof(value));
        }
        out_file1.close();
    }
    std::vector<pod_msg_to_file> pod_review;
    std::ifstream in_file1("L02_example.bin", std::ios::binary);
    if(in_file1.is_open())
    {
        while(true)
        {
            pod_msg_to_file current;
            in_file1.read(reinterpret_cast<char*>(&current), sizeof(current));
            if(in_file1.fail() || in_file1.eof())
            {
                break;
            }
            pod_review.push_back(current);
        }
        in_file1.close();
    }

    // Info #2: However, when you have non-POD types, you must explicitly write
    // the value of the data members to a file. And in case of reading and
    // deserialize, you have to read from the file to the data members in the
    // same order. Check the write_nonpod and read_nonpod function implementations.

    return 0;
}
