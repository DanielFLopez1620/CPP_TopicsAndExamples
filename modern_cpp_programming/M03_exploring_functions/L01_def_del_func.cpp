// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// BASED TOO ON GEEKSFORGEEKS Website:
// https://www.geeksforgeeks.org/explicitly-defaulted-deleted-functions-c-11/
// Code was tested with g++ in C++11

#include <iostream>

/**
 * When you have class you must implement special members like constructors,
 * destructors and assignment operators that have default, compiler and user
 * implementations, in this last implementation, you should think how to 
 * prevent bugs, optimize memory, avoid copying and others. And C++11 came
 * with some feature to do it. Before moving, keep an eye on this:
 * 
 * - Special members are the default constructor, destructur, copy constructor,
 *   move constructor, copy assignment operator, move assignment operator.
 * - When we say copy, we refer to using the copy constructor and assignment to
 *   make possible a copy.
 * - When we say move, we refer to using move constructor and move assignment
 *   so it is possible to move and object.
 * - Using the special member cases provided below, you can prevent certain
 *   usages and make sure that the compiler doesn't create more implementations
 *   for those special members.
 * 
 * Finally, you may need to know that there are some cases you still need to
 * provide an empty implementation in order to prevent copies or operations that
 * you do not want, but prefer to use the commands and helps presented in this
 * module.
 * 
 * NOTE: When ready, you can run this code with:
 * 
 *      g++ -std=c++11 /L01_def_del_func.cpp -o def_f.out
 *      ./def_f.out
 * 
 * 
 * Now, let's mention some handler option to functions:
*/


class MySetOfFuncs
{
public:
    // Info #1: This is a user-based constructor, the ones you made by 
    // yourself in your code.
    MySetOfFuncs (std::string name)
    {
        std::cout << "Method made by: " << name << std::endl;
    }
    
    // Info #2: When you have a user-defined constructor, the default 
    // constructor isn't considered. So we add a constructor with an option
    // '=default' where we specify it. Keep in mind it doesn't work with non-
    // special members or special members with arguments.
    // Having a default constructor allow you to have a trivial type and it can
    // be used with dcopy constructors and destructors.
    // The usage is shown below: 
    MySetOfFuncs() = default;

    // Info #3: Delete back then was only used to deallocate memory, but after
    // C++11 it also allows to disable the usage of a member function by
    // adding '=delete'. This allows a cleaner way to prevent special members
    // we do not want and prevents unintened type promotions.
    // Here we show the usage to prevent a copy constructor and prevent doubles.
    MySetOfFuncs(const MySetOfFuncs &) = delete;
    MySetOfFuncs(double) = delete;

    // Info #4: Another definition to prevent copies (or better called a non-
    // copyable type), are:
    MySetOfFuncs& operator=(MySetOfFuncs const&) = delete;
};

// Info #5: You can create a non-copyable object that is still movable by 
// declaring the 'copy-operations' as deleted, then implementing the 'move
// operations'. 
struct example_type{};
class NonCopyButMovable
{
    example_type* ex;
public: 
    // User defined constructor and destructor
    NonCopyButMovable(example_type* ex_p = nullptr) : ex(ex_p) {}
    ~NonCopyButMovable() {delete ex; }

    // Making sure of non-copyable
    NonCopyButMovable(NonCopyButMovable const&) = delete;
    NonCopyButMovable& operator=(NonCopyButMovable const&) = delete;

    // Making sure it is movable
    NonCopyButMovable(NonCopyButMovable&& other):ex(std::move(other.ex))
    {
        other.ex = nullptr;   
    }
    NonCopyButMovable& operator=(NonCopyButMovable&& other)
    {
        if(this != std::addressof(other))
        {
            delete ex;
            ex = std::move(other.ex);
            other.ex = nullptr;
        }
        return *this;
    }

};

// Info #6: You can use templates and then use '=delete' to prevent certain
// types, prevent promotions or ensure you use specific types
template <typename T>
void command(T val) = delete;
void command(short val)  // Can only be called with short values
{
    std::cout << std::endl << "This command works only for shorts" << std::endl;
}
 

// In the main we will test our implementations:
int main(int argc, char** argv)
{
    std::cout << "Check the code to understand the constructor that call"
              << " the results shown below, so you can learn about defaulted"
              << " and deleted functions" << std::endl << std::endl;
    
    // Info #7: Calling the constructors implementations.
    MySetOfFuncs a;             // Default
    MySetOfFuncs name1("Dan");  // Parameterized constructor
    MySetOfFuncs name2("DD");   // Parameterized constructor
    // name1 = name2            // Error, copy isn't possible
    // MySetOfFuncs dou1(1620)  // Error, double type param is disabled

    command((short) 4);
    return 0;
}