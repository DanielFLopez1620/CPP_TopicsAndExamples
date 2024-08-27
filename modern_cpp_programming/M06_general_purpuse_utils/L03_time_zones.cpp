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
 * - auto time = std::chrono::zoned_time{ std::chrono::current_zone(),
 *      std::chrono::system_clock::now() } : Obtain current local time
 * - auto time = std::chrono::zoned_time{ std::chrono::locate_zone(
 *      "Europe/Rome"), std::chrono::system_clock::now() } : Obtain Italy time
 * - date::format(std::locale{"ro_RO"}, "%c", time) : Format hour for Romania
 * - auto ny_time = std::chrono::zoned_time<std::chrono::milliseconds>{
 *      std::chrono::locate_zone("America/NewYork"), std::chrono::local_days{
 *      2024y / 7 / 27} + 12h + 30min + 45s} : Time point in a time zone
 * - auto la_itme = std::chrono::zoned_time<std::chrono::milliseconds>(
 *      std::chrono::locate_zone("America/Los_Angeles"), 
 *      ny_time) : Convert from time zones a time
 * 
 * 
 * However, this may not be available for your compiler on C++20, for that 
 * reason we will use the Howard Hinnant Date Library, which you can check on
 * the notes.
 * 
 * To make sure we have it available, we will have to follow the next steps:
 * 
 *      cd <path_to_workspace>/CPP_TOPICSANDEXAMPLES/
 *      cd modern_cpp_programming/M06_general_purpose_utils
 *      git clone https://github.com/HowardHinnant/date.git
 *      cd date
 *      mkdir build
 *      cd build
 *      cmake ..
 *      make
 *      sudo make install
 *      cmake -DBUILD_TZ_LIB=ON ..
 *      make
 *      sudo make install
 * 
 * To compile this code, you will need to run:
 * 
 *      g++ -std=c++20 -I/usr/local/include/ -L/usr/local/lib/ 
 *          L03_time_zones.cpp -o time_zones.out -ldate-tz -lcurl
     
 * 
 * NOTE: Check https://howardhinnant.github.io/date/tz.html#Installation
 */


#include "date/tz.h"
#include <chrono>
#include <locale>

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    std::cout << "Lesson 3: Time zones with chrono:\n" << std::endl;

    // Info #1: Obtaining current local time
    auto now = std::chrono::system_clock::now();
    auto cur_loc_time = date::make_zoned(date::current_zone(), now);
    std::cout << "Local time:" << cur_loc_time << std::endl;

    // Info #2: Obtaining current local time in another time zone
    auto now_it = date::make_zoned(date::locate_zone("Europe/Rome"), now);
    std::cout << "Time in Rome, Italy: " << now_it << std::endl;

    // Info #3: Formatting output according a time zone
    // For this make sure you have installed:
    //      sudo locale-gen de_DE.UTF-8
    //      sudo update-locale
    auto now_rom = date::make_zoned(date::current_zone(), now);
    std::cout << "Time now in German format: "
              << date::format(std::locale{"de_DE.UTF-8"}, "%c", now_rom) 
              << std::endl;


    return 0;
}