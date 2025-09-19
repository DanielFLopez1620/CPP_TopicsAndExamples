// Based on the Learn C++ by Example (2024) by Frances Buontempo

// /////////////////////////// IMPORTS ////////////////////////////////////////
#include <iostream> // Input-Outpu streams
#include <vector>   // For dynamic arrays or containers

void create_triangle()
{
    std::vector<int> data { 1 };
    for (auto number : data)
    {
        std::cout << number << ' ';
    }
    std::cout << std::endl;
}

auto main() -> int
{
    create_triangle();
}