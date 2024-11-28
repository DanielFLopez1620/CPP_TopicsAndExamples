// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * When writitng files you may encounter issues when you use time and settings
 * that depends on the region/nation you are. For this, the C++ I/O comes with
 * locales and facets for general-purpose mecahism for hadling international
 * features.
 * 
 * In this lesson, we are going to show them with std::cout. However, they
 * work with other I/O stream objects.
 * 
 * 
 */

#include <chrono>
#include <vector>

int main(int argc, char *argv[])
{
    auto now = std::chrono::system_clock::now();
    auto system_time = std::chrono::system_clock::to_time_t(now);
    auto local_time = std::localtime(&system_time);
    std::vector<std::string> name_collection
        {"Dan", "Daniel", "Dæniel", "Daçiel", "Däniel"};
    auto sort_and_display = [](std::vector<std::string> collection, 
        std::locale const & location)
    {
        std::sort(collection.begin(), collection.end(), location);
        std::cout << "Displaying sorted collection: ";
        for(auto const & name : collection)
        {
            std::cout << name << " ,";
        }
        std::cout << std::endl;
    };

    return 0;
}