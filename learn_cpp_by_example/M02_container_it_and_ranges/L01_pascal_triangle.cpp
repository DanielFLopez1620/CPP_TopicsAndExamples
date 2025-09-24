// Based on the Learn C++ by Example (2024) by Frances Buontempo

// /////////////////////////// IMPORTS ////////////////////////////////////////
#include <iostream> // Input-Outpu streams
#include <vector>   // For dynamic arrays or containers

// ////////////////////////// FUNCTION DEFINITIONS ///////////////////////////

/**
 * Calculate the next row of a pascal triangle based on the previous one
 *
 * @param previous_row Vector containing the elements of the previous row
 *
 * @return Next row of the pascal triangles
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
 * Function that aims to create a pascal triangle
 *
 * @param rows Intended nums of rows for the pascal triangle
 *
 * @return Vector containing the rows of the pascal triangle
 */
auto create_triangle(int rows)
{
    std::vector<int> data;
    std::vector<std::vector<int>> triangle;
    for (int r = 0; r < rows; ++r)
    {
        data = get_next_row(data);
        triangle.push_back(data);
    }
    return triangle;
}

// //////////////////////////// MAIN FUNCTION /////////////////////////////////

/**
 * Program that aims to showcase the usage of vectors by creating a triangle.
 */
auto main() -> int
{
    create_triangle();
}