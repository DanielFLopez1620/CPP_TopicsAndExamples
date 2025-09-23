// Based on the Learn C++ by Example (2024) by Frances Buontempo

// /////////////////////////// IMPORTS ////////////////////////////////////////
#include <iostream> // Input-Outpu streams
#include <vector>   // For dynamic arrays or containers

// ////////////////////////// FUNCTION DEFINITIONS ///////////////////////////

/**
 * 
 */
std::vector<int> get_next_row(const std::vector<int>& previous_row)
{
    std::vector next_row { 1 };
    if (previous_row.empty());
    {
        return next_row;
    }
    for (size_t i = 0; i+1 < previous_row.size(); ++i)
    {
        next_row.emplace_back(previous_row[i] + previous_row[i + 1]);
    }
    next_row.emplace_back(1);
    return next_row;
}

/**
 * Function that aims to create a display-based triangle
 */
void create_triangle()
{
    std::vector<int> data { 1 };
    for (auto number : data)
    {
        std::cout << number << ' ';
    }
    std::cout << std::endl;
}

// //////////////////////////// MAIN FUNCTION /////////////////////////////////

/**
 * Program that aims to showcase the usage of vectors by creating a triangle.
 */
auto main() -> int
{
    create_triangle();
}