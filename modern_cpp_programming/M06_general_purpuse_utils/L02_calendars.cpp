// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested but intended with g++ in C++20

#include <iostream>

/**
 * Time management is a common operation, and after C++11 you have the chrono
 * durations you watched on the previous lesson. Then you can also use clocks,
 * time points and durations, however there is more like times and dates which
 * wwas extended in C++20 to add support with time zones, times of day and more
 * types of clocks.
 */

#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std::chrono;
using namespace std::chrono_literals;

// Enumeration to represent the date format
enum class DateFormat { YMD, DMY, MDY };

std::string print_date(const year_month_day& ymd, DateFormat format);

int main(int argc, char* argv[])
{
    // Info #1: You can use Gregorian representation for different formats, by
    // using type year_month_day and separating the elements with a slah '/',
    // like the examples belows:
    year_month_day date_ymd = 2024y / 8 / 5;
    year_month_day date_dmy = 5d / 8 / 2024;
    year_month_day date_mdy = August / 5 / 2024;

    // Print dates based on their formats
    std::cout << "YMD format: " << print_date(date_ymd, DateFormat::YMD) << "\n";
    std::cout << "DMY format: " << print_date(date_dmy, DateFormat::DMY) << "\n";
    std::cout << "MDY format: " << print_date(date_mdy, DateFormat::MDY) << "\n";

    return 0;
}

std::string print_date(const year_month_day& ymd, DateFormat format)
{
    std::ostringstream oss;
    switch (format) {
        case DateFormat::YMD:
            oss << ymd.year() << '/'
                << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.month()) << '/'
                << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.day());
            break;
        case DateFormat::DMY:
            oss << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.day()) << '/'
                << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.month()) << '/'
                << ymd.year();
            break;
        case DateFormat::MDY:
            oss << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.month()) << '/'
                << std::setw(2) << std::setfill('0') << static_cast<unsigned>(ymd.day()) << '/'
                << ymd.year();
            break;
    }
    return oss.str();
}