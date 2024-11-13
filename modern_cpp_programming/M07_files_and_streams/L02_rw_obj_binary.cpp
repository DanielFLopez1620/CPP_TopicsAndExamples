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
    return 0;
}