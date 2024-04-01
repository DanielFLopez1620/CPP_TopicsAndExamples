// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// BASED TOO ON GEEKSFORGEEKS Website:
// https://www.geeksforgeeks.org/lambda-expression-in-c/
// Code was tested with g++ in C++17

#include <iostream>

/**
 * There are many ways to use a lambda, and it also includes a class and a
 * struct usage. Here we are going to illustrate some of them.
*/

#include <vector>
#include <algorithm>

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

int main(int argc, char** argv)
{
    auto nums = std::vector<int>{0, 19, 17, 12, 3};
    int max { 20 };
    int min { 16 };
    auto is_inrage = std::count_if(std::begin(nums), std::end(nums), 
        range_checker(min, max));
    return 0;
}