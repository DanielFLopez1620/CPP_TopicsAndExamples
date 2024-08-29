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
 * The system maintains a copy of the IANA Time zone database, which is 
 * read-only for the user with functions like std::chrono::tzdb() or
 * std::chrono::get_tzdb_list(). When you retrieve info of a time zone, you
 * retrive a "time_zone" object, a full list of tz database time zones can
 * be found here:
 *      https://en.wikipedia.org/wiki/List_of_tz_database_time_zones.
 * 
 * In the case of std::chrono::zoned_time it can be created from a sys_time, a
 * local_time or another zoned_time (which means a time zone conversion).
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

// ------------------------ REQUIRED STANDARD LIBRARIES -----------------------

#include "date/tz.h"  // Custom date library by Howard Hinnat
#include <chrono>     // Time library for different precisions
#include <locale>     // Localization of time formats

// ----------------------- NAMESPACE CONSIDERATIONS----------------------------
using namespace std::chrono_literals;  // For user-defined chrono literals

// ----------------------- MAIN IMPLEMENTATION --------------------------------
int main(int argc, char *argv[])
{
    std::cout << "Lesson 3: Times zones with Howard Hinnats Date Library:\n"
              << std::endl;

    // Info #1: Obtaining current local time
    auto now = std::chrono::system_clock::now();
    auto cur_loc_time = date::make_zoned(date::current_zone(), now);
    std::cout << "Obtaining time in the current time zone:" << std::endl
              << "\tLocal time:" << cur_loc_time << std::endl;

    // Info #2: Obtaining current local time in another time zone
    auto now_it = date::make_zoned(date::locate_zone("Europe/Rome"), now);
    std::cout << "Obtaining time in another time zone: " << std::endl
              << "\tTime in Rome, Italy: " << now_it << std::endl;

    // Info #3: Formatting output according a time zone
    // For this make sure you have installed:
    //      sudo locale-gen de_DE.UTF-8
    //      sudo update-locale
    auto now_rom = date::make_zoned(date::current_zone(), now);
    std::cout << "Formatting according a region: " << std::endl
              << "\tTime now in German format: "
              << date::format(std::locale{"de_DE.UTF-8"}, "%c", now_rom) 
              << std::endl;

    // Info #4: You can create time points and convert them among time zones:
    auto current = std::chrono::system_clock::now();
    auto local_cur = date::make_zoned(date::current_zone(), current);
    auto ny_cur = date::make_zoned(date::locate_zone("America/New_York"), 
        current);
    auto rome_cur = date::make_zoned(date::locate_zone("Europe/Rome"), 
        ny_cur.get_sys_time());
    std::cout << "Changing form time zones:" << std::endl
              << "\tLocal time: " << local_cur << std::endl
              << "\tNew York Time: " << ny_cur << std::endl
              << "\tRome time: " << rome_cur << std::endl;

    return 0;

} // main()