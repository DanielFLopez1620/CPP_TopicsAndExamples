// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * C++ does not have a hierarchical type system, then it can't store multiple
 * types of a value in a single variable. Originally, it was used the void
 * pointer (void*) but it is not type safe, for that reason std::any appeared
 * in C++17.
 * 
 * For using std::any, you will have to include the <any> header.
 * 
 * But what is exactly a std::any? It is a type safe container that can hold 
 * any value that is copy constructible. But it is not possible to read 
 * directly the value, and you will need the 'std::any_cast()' to cast the 
 * stored value into a specified one, just be careful and do not proveke a
 * std::bad_any_cast exception.
 * 
 * If you need to, you can check the type, by using the function memeber
 * 'type()', if it is empty it returns a typeid(void) and also you can check if
 * it is empty by checking it with 'hast_value' member function.
 * 
 * As a final and important note, you can create arrays and vectors of multiple
 * types by using std::vector with std::any and it will even work with a for
 * each.
 * 
 * When ready, you can run the code with:
 * 
 *      g++ -std=c++20 L06_std_any.cpp -o anything.out
 *      ./anything.out
 */

// ---------------------------------- REQUIRED HEADERS ------------------------
#include <any>

// ---------------------------------- NAMESPACES REQUIRED --------------------
using namespace std::string_literals;  // String literals 's'

// ---------------------------------- FUNCTION PROTOTYPES ---------------------
void print_any(const std::any& anything);

// --------------------------------- MAIN IMPLEMENTATION ----------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 6: Store any value:\n " << std::endl;
    
    // Info #1: You can use any to store any standard type, but for printing
    // you will need to implement some trick, for now, just check the assigns:
    std::any value(1620);
    value = 16.20;
    value = "1620"s;

    // Info #2: For printing a std::any type, it is better to create a function
    // that implements different type recongnition, makes the conversion and
    // then print it:
    std::cout << "Using the same variable with different types: " << std::endl
              << "\tInteger: ";
    value = 1620;
    print_any(value);
    std::cout << std::endl << "\tFloat: ";
    value = 16.20;
    print_any(value);
    std::cout << std::endl << "\tString: ";
    value = "1620"s;
    print_any(value);
    std::cout << std::endl;

    // Info #3: You can read the value's types, and use them for conversions
    // like shown in the print_any() custom function or as shown below:
    std::any my_var = 16;
    std::cout << "Making conversions: " << std::endl;
    try
    {
        auto my_int = std::any_cast<int>(my_var);
        std::cout << "\tConversion from any to int: " << my_int << std::endl;
    }
    catch(std::bad_any_cast const & e)  
    {
        std::cerr << e.what() << std::endl;
    }

    // Info #4: Also you can detect the type and detect if a std::any is
    // valid for a certain type.
    std::any my_str = "str16"s;
    std::cout << "Checking type of a std::any stored value: ";
    print_any(my_str);
    std::cout << "\n\tIs int? " << ((my_str.type() == typeid(int)) ? 1 : 0 )
              << "\n\tIs flt? " << ((my_str.type() == typeid(double)) ? 1 : 0)
              << "\n\tIs str? " 
              << ((my_str.type() == typeid(std::string)) ? 1 : 0) << std::endl;

    // Info #4: If you need to check if a std::any stores a value, you should
    // use the has_value method.
    auto any_has_value = [](std::any const & anything)
    {
        std::cout << "The any selected ";
        if (anything.has_value())
        {
            std::cout << "has a value" << std::endl;
        }
        else
        {
            std::cout << "is empty" << std::endl;
        }
    };
    std::any test1;
    std::any test2(42);
    std::cout << "Checking if std::any stores a value: " << std::endl
              << "\tAny 1: ";
    any_has_value(test1);
    std::cout << "\tAny 2: ";
    any_has_value(test2);

    // Info #5: You can modify the values of a std::any with the member
    // the member functions emplace(), reset() or swap():
    std::any value_for_mod = 16;
    std::cout << "Modifying the value of a  std::any: " << std::endl
              << "\tOriginal value: ";
    print_any(value_for_mod); 
    value_for_mod.emplace<std::string>("Emplaced");
    std::cout << "\n\tAfter emplaced: ";
    print_any(value_for_mod);
    value_for_mod.swap(value);
    std::cout << "\n\tAfter swap with first any defined: ";
    print_any(value_for_mod);
    value_for_mod.reset();
    std::cout << "\n\tIs empty after reset?: "
              << value_for_mod.has_value() ? 1 : 0; 
    std::cout << std::endl;
    
    return 0;
} // main()

// ------------------------- FUNCTION DEFINTIONS ------------------------------

/**
 * Function that interprets the type of a std::any to check if it is a int,
 * double or string and covert it to a proper print, however, if it is not
 * the previous type just answer that it is a unsopported type.
 * 
 * @param anything Literaly anything as it is a std::any arg.
 */
void print_any(const std::any& anything)
{
    if (anything.type() == typeid(int))
    {
        std::cout << std::any_cast<int>(anything);
    }
    else if (anything.type() == typeid(double))
    {
        std::cout << std::any_cast<double>(anything);
    }
    else if(anything.type() == typeid(std::string))
    {
        std::cout << std::any_cast<std::string>(anything);
    }
    else
    {
        std::cout << "Unsupported type...";
    }
}