// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// BASED TOO ON GEEKSFORGEEKS Website:
// https://www.geeksforgeeks.org/lambda-expression-in-c/
// Code was tested with g++ in C++17

#include <iostream>

/**
 * There are many ways to use a lambda, and it also includes a class and a
 * struct usage. Here we are going to illustrate some of them.
 * 
 * Check each one, and when you are ready, you can execute the program with:
 * 
 *      g++ -std=c++17 L03_lambda_and_struct.cpp -o struct_lambda.out
 *      ./struct_lambda.out
*/

#include <vector>     // Library for using vectors (sequence containers
                      // representing arrays that can change).

#include <algorithm>  // Collection of functions for range of elements.

// Info #1: Create a lambda class for multiple implementations 
class range_checker
{
    int min_;
    int max_;
public:
    // User defined constructor, capture values by copy
    explicit range_checker(int const min, int const max) :
        min_(min), max_(max) {}
    
    // Defaulted implementations for constructors and destructors
    range_checker(const range_checker&) = default;
    range_checker(range_checker&&) = default;
    ~range_checker() = default;

    // Deleted implementations
    range_checker& operator=(const range_checker&) = delete;
    
    // Implementation of checking if it is inside certain range
    bool operator() (int const n) const
    {
        return min_ <= n && n <= max_;
     }
};

// Info #2: Using structs and capturing data members with copy:
struct presentation_type1
{
    std::string name;
    std::string profession;

    auto present()
    {
        return [i = name, j = profession] 
        { std::cout << "I am" << i << " / " << j << std::endl; };
    }
};

// Info #3: Using structs and capturing data members with copying the entire 
// object (implicit caputre of 'this' is deprecated in C++20 in this form)
struct presentation_type2
{
    std::string name;
    std::string profession;

    auto present()
    {
        return [=] 
        { 
            std::cout << "I am" << name << " / " << profession << std::endl; 
        };
    }
};

// Info #4: You can use this in the capturing group and it allows to invoke
// other methods.
struct presentation_type3
{
    std::string name;
    std::string profession;

    auto present()
    {
        return [this] 
        {
            std::cout << "I am" << name << " / " << profession << std::endl; 
        };
    }
};

int main(int argc, char** argv)
{
    // Info #5: Implementing the lambda range_checker function
    auto nums = std::vector<int>{0, 19, 17, 12, 3};
    int max { 20 };
    int min { 16 };
    auto is_inrage = std::count_if(std::begin(nums), std::end(nums), 
        range_checker(min, max));
    std::cout << "Nums vector: ";
    for(const int n : nums)
    {
        std::cout << n << ", ";
    }
    std::cout << std::endl << "How many between " << min << " and " << max
              << "? : " << is_inrage << std::endl << std::endl;

    // Info #6: Calling presentations and getting the displays of the lambdas.
    auto p1 = presentation_type1{ "Dan", "Eng."}.present();
    auto p2 = presentation_type2{ "DD", "Des."}.present();
    auto p3 = presentation_type3{ "Skovk", "Eng."}.present();
    return 0;
}