// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * It can be annoying to have to declared a specific argument for a template,
 * but after C++17 exists something called 'class template argument deduction'
 * which enables the compiler to deduce the missing template args.
*/

#include <vector>
#include <functional>
#include <utility>
#include <mutex>
#include <typeinfo>

template <class T>
struct to_deduce_struct
{
    to_deduce_struct(T info) : info(info) 
    {
        std::cout << "Deduction completed... Construction done" << std::endl
                  << "Specialization type was: " << typeid(T).name()
                  << std::endl;
    }
private:
    T info;
};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}


int main(int argc, char* argv[])
{
    // Info #1: Some cases where you can allow deduction are pairs, vectors
    // and less (which is a way to perform less-than comparison operations as
    // if the were ordinary functions), and many more.
    std::pair deduced_pair{16, '2'};
    std::vector deduced_vector{1, 6, 2, 0};
    std::less l;
    std::cout << "Deduction of standard objects from libraries: " 
              << "Pair deduction as <int, char>: " << deduced_pair << std::endl
              << "Deduced vector as <int>: (";
    for (const auto& num : deduced_vector)
    {
        std::cout << num << ", ";
    }
    std::cout << std::endl << "Less is deduced as less for <void>" << std::endl;


    // Info #2: The deduction can also works when you have a generic struct
    // by using templates. 
    std::cout << std::endl << "Deduction of custom types: " << std::endl;
    auto f = new to_deduce_struct(16.20);

    

    return 0;
}