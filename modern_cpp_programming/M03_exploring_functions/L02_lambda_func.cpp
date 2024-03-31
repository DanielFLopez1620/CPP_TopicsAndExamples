// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// BASED TOO ON GEEKSFORGEEKS Website:
// https://www.geeksforgeeks.org/lambda-expression-in-c/
// Code was tested with g++ in C++14

#include <iostream>

/**
 * Lambda expressions are used to create inline functions and provide a certain
 * way of using snippets that doesn't require a name. Its structure is:
 * 
 *      [ capture clause ] ( parameters ) -> return-type
 *      {
 *          defintion
 *      } 
 * 
 * Another way to consider a lambda expression is:
 * 
 *      [capture-list](params) mutable constexpr excpetion attr -> return
 *      {
 *          body
 *      }
 * 
 * So, the simpliest lambda is []{}
 * 
 * Here is important to say that lamdbas are actually a class, so when we
 * create one lambda, we instance a new object which is called 'lambda
 * clousure'.
 * 
 * Lambda expressions, similar to functions, can capture variables by copy
 * (value) or by reference, but it cannot be captured multiple times. Also, 
 * they can capture variables available to its content, so elements with
 * static storage aren't recommended with lambdas. More info on captures is
 * considered below:
 * 
 * - [](){}        -> Doesn't capture anything.
 * - [&](){}       -> Capture everything by reference
 * - [=](){}       -> Capture everything by copy
 * - [&x](){}      -> Captures x by reference
 * - [x](){}       -> Captures x by copy
 * - [&x...](){}   -> Captures pack extension x by reference.
 * - [x...](){}    -> Captures pack extension x by copy
 * - [&, x](){}    -> Captures everything by reference, except x (copy)
 * - [=, &x](){}   -> Captures everythin by copy, except x (reference)
 * - [&x=expr](){} -> Reference to x, initialized from expr
 * - [x, x](){}    -> ERROR, multiple captures aren't possible.
 * - [&this](){}   -> ERROR, pointer is always considered as copy
 * 
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
    std::string nums_str {""};
    for(const auto& num : nums)
    {
        nums_str += std::to_string(num) + " ,";
    }
    std::cout << "From numers array: " << nums_str << std::endl
              << "How many negatives?: " << negatives << std::endl << std::endl;
    
    // Info #2: Second type of lambda function, a expression for checking
    // approved notas (named lambda)
    auto notes = std::vector<float>{4.0, 1.0, 2.0, 3.5, 5.0, 4.2};
    auto is_approved = [](float const num){ return num >= 3.5; };
    auto aproveds = std::count_if(std::begin(notes), std::end(notes), 
        is_approved);
    std::string notes_str {""};
    for(const auto& note : notes)
    {
        notes_str += std::to_string(note) + " ,";
    }
    std::cout << "From notes array: " << notes_str << std::endl
              << "How many approved?: " << aproveds << std::endl << std::endl;

    // Info #3: You can also create your own generic lambdas (after C++14) by
    // using auto in the arguments specification.
    auto more_notes = std::vector<float>{5 , 4.8, 1, 1.0, 2, 3.5, 4.2, 4};
    auto exceptionals = std::count_if(std::begin(more_notes), 
        std::end(more_notes), [](auto const n){ return n > 4; });
    std::string m_notes_str {""};
    for(const auto& note : more_notes)
    {
        m_notes_str += std::to_string(note) + " ,";
    }
    std::cout << "From notes array: " << m_notes_str << std::endl
            << "How many pretty good?: " << aproveds << std::endl << std::endl;

    // Info #4: You can use lambdas to generate moves, consider the next case
    // by combining it with std::move. 
    auto ptr = std::make_unique<int>(1620);
    std::cout << "Consider original value: " << *ptr << std::endl;
    auto l = [ptr = std::move(ptr)]() mutable 
        { auto& lptr = ptr; return ++*lptr; };
    l();
    std::cout << "Increment using pointer and lambda: " << *ptr << std::endl;

    return 0;
}