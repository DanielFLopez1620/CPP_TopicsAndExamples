// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * In the previous lesson we worked with unstructured (raw) data related with
 * writing and reading operations. However, as you may know, most of the time
 * we work with structured data that should be persisted in files. Also, the
 * previous lesson only works with POD data, then for new objects we must
 * explicitly decide what to write or read, and how to do it. 
 */

#include <vector>
#include <fstream>

bool write_nonpod(std::ofstream& out_file);
bool read_nonpod(std::ifstream& in_file);

class msg_to_file
{
    int num;
    char priority;
    std::string msg;

public:
    msg_to_file(int const num = 0, char const priority = '0',
        std::string const & msg = {}) : num(num), priority(priority), msg(msg)
    {}

    msg_to_file(msg_to_file const &) = default;
    
    msg_to_file& operator=(msg_to_file const &)  = default;
    
    bool operator==(msg_to_file const & rhv) const
    {
        return num == rhv.num && priority == rhv.priority && msg == rhv.msg;
    }

    bool operator!=(msg_to_file const & rhv) const
    {
        return !(*this == rhv);
    }

};

struct pod_msg_to_file
{
    int num;
    char priority;
    char content[2];
};

bool operator==(pod_msg_to_file const & f1, pod_msg_to_file const & f2)
{
    return f1.num == f2.num &&
           f1.priority == f2.priority &&
           f1.content[0] == f2.content[0] &&
           f1.content[1] == f2.content[1];
}

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

bool write_nonpod(std::ofstream& out_file) const
{
    out_file.write(reinterpret_cast<const char*>(&num), sizeof(num));
    out_file.write(&priority, sizeof(priority));
    auto size = static_cast<int>(msg.size());
    out_file.write(reinterpret_cast<char*>(&size), sizeof(size));
    out_file.write(msg.data(), msg.size());
    return !out_file.fail();

}

bool read_nonpod(std::ifstream& in_file)
{
    in_file.read(reinterpret_cast<char*>(&i), sizeof(i));
    in_file.read(&priority, sizeof(priority));
    auto size {0};
    in_file.read(reinterpret_cast<char*>(&size), sizeof(size));
    msg.resize(size);
    in_file.read(interpret_cast<char*>(&msg.front()), size);
    return !in_file.fail();
}