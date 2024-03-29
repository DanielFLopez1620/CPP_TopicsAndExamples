// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// BASED TOO ON GEEKSFORGEEKS Website:
// https://www.geeksforgeeks.org/lambda-expression-in-c/
// Code was tested with g++ in C++11

#include <iostream>

/**
 * Lambda expressions are used to create inline functions and provide a certain
 * way of using snippets that doesn't require a name. Its structure is:
 * 
 *      [ capture clause ] ( parameters ) -> return-type
 *      {
 *          defintion
 *      } 
*/

#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <memory>

int main()
{
    // Info #1: First type of lambda function, a expression for searching
    // negative numbers (anonymous).
    auto nums = std::vector<int>{0, -1, -2, 3, 4, -5, 6, -7};
    auto negatives = std::count_if(std::begin(nums), std::end(nums), 
        [](int const num) { return num < 0; });
    std::cout << "From numers array: " << nums << std::endl
              << "Negative nums are: " << negatives << std::endl << std::endl;
    
    // Info #2: Second type of lambda function, a expression for checking
    // approved notas (named lambda)
    auto notes = std::vector<float>{4.0, 1.0, 2.0, 3.5, 5.0, 4.2};
    auto is_approved = [](float const num){return num >= 3.5};
    return 0;
}