// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>

/* INITIALIZER LIST: Is what makes possible to use initialization of
 * standard containers, and acts like a lightwieght proxy over an array.
 * 
 * First, it resolves the types, then creates an array, after that the
 * element is wrapped and finally it is passed to the constructor as an arg.
 */

// -------CLASSES:
class basic
{
    char let_;
    char flag_;
public:
    basic() : let_('v'), flag_(false) {}
    basic(char let, char flag = 'f'): let_(let), flag_(flag) {}
    basic(std::initializer_list<char> ini){}
};

// --------FUNCTION PROTOTYPES:
void showcase(float a, float b);
void showcase(std::initializer_list<float> const nums);

// --------MAIN:
int main()
{
    basic('a','b'); // Applays the initializer_list for object
    showcase({1.1,3.14,2.79}); // Applay the initializer_list for function
    
    // TIPS:
    // * Remember to be careful, try to not use vector declarations for this.
    // * Brace-initialization does not allow narrowing conversion.
    //   Like: 'int num{1.2};'
    //   Fix it with: 'int num{ static_cast<int>(1.2)};'
    return 0;
}

// ---------FUNCTIONS DECLARATIONS:
void showcase(float a, float b)
{
    std::cout << a << " & " << b << std::endl;
    return;
}
void showcase(std::initializer_list<float> const nums)
{
    for (auto const & n: nums)
        std::cout << n << std::endl;
    return;
}