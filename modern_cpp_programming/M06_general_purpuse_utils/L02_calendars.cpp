// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Time management is a common operation, and after C++11 you have the chrono
 * durations you watched on the previous lesson. Then you can also use clocks,
 * time points and durations, however there is more like times and dates which
 * wwas extended in C++20 to add support with time zones, times of day and more
 * types of clocks.
 */

#include <chrono>

using namespace std::chrono_literals;

namespace std::chrono 
{
    std::ostream& operator<<(std::ostream& os, const year& y) 
    {
        return os << int(y);
    }

    std::ostream& operator<<(std::ostream& os, const month& m) 
    {
        return os << unsigned(m);
    }

    std::ostream& operator<<(std::ostream& os, const day& d) 
    {
        return os << unsigned(d);
    }

    std::ostream& operator<<(std::ostream& os, const year_month_day& ymd) 
    {
        return os << ymd.year() << '/' << ymd.month() << '/' << ymd.day();
    }
}

int main(int argc, char* argv[])
{
    // Info #1: You can use Gregorian representation for different formats, by
    // here you can consider using two forms of creation:
    constexpr auto date_ymd_1 = std::chrono::year_month_day(2024y,
        std::chrono::August, 7d);
    const std::chrono::year_month_day date_ymd_2 = 2024y / 8 / 7;
    std::cout << date_ymd_1 << std::endl << date_ymd_2 << std::endl;

    // Info #2: You can define the date in the format you want, like DMY, YMD
    // or MDY, and the chrono library will unified it:


    return 0;
}


