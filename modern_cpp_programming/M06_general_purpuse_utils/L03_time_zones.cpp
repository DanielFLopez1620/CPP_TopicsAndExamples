// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include<iostream>

/**
 * Chrono library measures the unix time, using UTC as the dault time zone. 
 * However, this doesn't mean we cannot use local time or other time zones, for
 * this we will use C++20.
 * 
 * Some of the command to kee in mind are:
 * 
 * - std::chrono::current_zone(): Retrieve local time for time zone database.
 * - std::chrono::locate_zone(): Retrive a particular time zone.
 * - std::chrono::zoned_time(): Time point in a particular time zone.
 * 
 * 
 * NOTE: Check https://howardhinnant.github.io/date/tz.html#Installation
 */

#include<chrono>

int main(int argc, char *argv[])
{
    std::cout << "Lesson 3: Time zones with chrono:\n" << std::endl;

    // Info #1: Obtaining current local time
    auto cur_loc_time = std::chrono::zoned_time{ std::chrono::current_zone(), 
        std::chrono::system_clock::now() };
    std::cout << cur_loc_time << std::endl;

    return 0;
}