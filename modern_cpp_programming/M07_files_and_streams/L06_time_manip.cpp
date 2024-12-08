// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * We have already checked on format and currency manipulators, what about
 * time? Yes, we can do something with it too. For this purpose we will
 * use the time representation in the form of std::tm (from C++11) that
 * contains calendar date and time info.
 * 
 * For this purpose you need to import <ctime> and <iomanip> headers, the
 * idea of manipulation present here follow some aspects of the previous
 * manipulators lesson, so keep in mind to check them too.
 * 
 *  
 */

#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

int main(int argc, char* argv[])
{
    std::cout << "Lesson 6: Time stream manipulators...\n" << std::endl; 
    
    // As a requirement, you need to consider the current time (or a
    // desired time) to display in the next steps, it can be standard
    // or local time.
    auto now = std::chrono::system_clock::now();
    auto st_tm = std::chrono::system_clock::to_time_t(now);
    auto lc_tm = std::localtime(&st_tm);

    // Info #1: After you use 'imbue' with the desired region. You can
    // use the member 'std::put_time', and add a flag to indicate the
    // desired format:
    // - %c : Long format display (Sun 08 Dec 2024 12:54:41 -05)
    // - %F : ISO 8601 %Y-%m-%d (2024-12-08)
    // - %T : ISO 8601 Time (12:54:41)
    // - %FT%T%z : UTC combined date and time format.
    // - %Y-W%V : Week format (2024-W49)
    // - %Y-W%V-%u : Date with week number format (2024-W49-7)
    // - %Y-%j : Ordinal date format (2024-344)
    std::cout.imbue(std::locale("de_DE.utf8"));
    std::cout << "Displaying time considering German Region: " << std::endl
              << "\tLong format: " << std::put_time(lc_tm, "%c") << std::endl 
              << "\tUTC combined: " << std::put_time(lc_tm, "%FT%T%z")
              << std::endl << "\tWeek format: " 
              << std::put_time(lc_tm, "%Y-W%V-%u") << std::endl;

    // Info #2: For reading time, you need a void "std::tm" object, and use
    // the get_time method, and consider one of the possible format of:
    // http://en.cppreference.com/w/cpp/io/manip/get_time
    auto read_time = std::tm {};
    std::istringstream inp_str("Sun 08 Dec 2016 12:20:20 JST");
    inp_str.imbue(std::locale("en_US.utf8"));
    inp_str >> std::get_time(&read_time, "%c");
    if (!inp_str.fail())
    {
        std::cout << "Reading time considering US Region:" << std::endl 
                  << "\tInput: " << std::quoted(inp_str.str()) << std::endl
                  << "\tReading: " << std::asctime(&read_time) << std::endl;
    }
    else
    {
        std::cout << "Time reading failed..." << std::endl;
    }
    
    
    return 0;
}