// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * It can be annoying to have to declared a specific argument for a template,
 * but after C++17 exists something called 'class template argument deduction'
 * which enables the compiler to deduce the missing template args.
 * 
 * You can run the code below with:
 * 
 *      g++ -std=c++20 L13_class_arg_deduct.cpp -o deduct.out
 *      ./deduct.out
*/

// ------------------------------ REQUIRED HEADERS ----------------------------

#include <vector>      // Defines vectors class (dynamic arrays)
#include <functional>  // For function objects oriented to operators, and more
#include <utility>     // Utilities like pairs, relation operators and swaps
#include <mutex>       // Lockables object to use in critical secitions
#include <typeinfo>    // Operators related with typeid and dynamic cast

// ---------------------------- CLASSES AND STRUCTS DEFINITIONS ---------------

/**
 * Structure that intends to implement a generic form to add an attribute and
 * then obtain its id.
 */
template <class T>
struct to_deduce_struct
{
    /**
     * User defined constructor that assign the argument given as a attribute,
     * then display the ID.
     * 
     * @param info Generic value
     */
    to_deduce_struct(T info) : info(info) 
    {
        std::cout << "Deduction completed... Construction done" << std::endl
                  << "Specialization type was: " << typeid(T).name()
                  << std::endl;
    }
private:
    T info;  // Generic attribute
}; // to_deduce_struct

// Define concatenation operator for output stream wiith pairs.
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
} // operator<<

// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 13: Class and templates argument deduction:\n" 
              << std::endl;

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

    // Info #3: The deduction also works for function-like cast expressions:
    std::mutex mx;
    auto lock = std::lock_guard(mx); //Deduction for mutex
    std::vector<int> v;
    std::fill_n(std::back_insert_iterator(v), 16, 20);

    return 0;
}  // main