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

    std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_weekday& ymdw) 
    {

        os << int(ymdw.year()) << '/';
        os << unsigned(ymdw.month()) << '/';

        auto week_num = unsigned(ymdw.index());
        auto day_num = unsigned(ymdw.weekday().iso_encoding());

        // auto calendar_day = year_month_day { ymdw.year(), ymdw.month(), day{1}};
        // auto real_date_days = calendar_day + day{day_num} + (week_num * day{7});
        // os << unsigned(real_date_days.day());

        switch (day_num)
        {
        case 0:
            os << "[Sunday ";
            break;
        case 1:
            os << "[Monday ";
            break;
        case 2:
            os << "[Tuesday ";
            break;
        case 3:
            os << "[Wednesday ";
            break;
        case 4:
            os << "[Thurday ";
            break;
        case 5:
            os << "[Friday ";
            break;
        case 6:
            os << "[Saturday ";
            break;
        default:
            os << " Error day ";
            break;
        };
        os << " week " << week_num << " ]";

        return os;
    }

}


int main(int argc, char* argv[])
{
    // Info #1: You can use Gregorian representation for different formats, by
    // here you can consider using two forms of creation (you can use 
    // namespaces to avoid long definitons, here they are used to tell you
    // more about them in a proper way):
    constexpr auto date_ymd_1 = 
        std::chrono::year_month_day(2024y, std::chrono::August, 7d);
    const std::chrono::year_month_day date_ymd_2 = 2024y / 8 / 7;
    std::cout << "Date definition with year_month_day type: " << std::endl
              << "\tLong definition: "<< date_ymd_1 << std::endl 
              << "\tShort denition: " << date_ymd_2 << std::endl;

    // Info #2: You can define the date in the format you want, like DMY, YMD
    // or MDY, and the chrono library will unified it:
    std::chrono::year_month_day date_dmy = 8d / 8 / 2024;
    std::chrono::year_month_day date_mdy = std::chrono::August / 8 / 2024;
    std::chrono::year_month_day date_ymd = 2024y / 8 / 8;
    std::cout << "Definitions of YMD, DMY and MDY with uniformity: "
              << std::endl << "\tYMD format result: " << date_ymd
              << std::endl << "\tMDY format result: " << date_mdy
              << std::endl << "\tDMY format result: " << date_dmy
              << std::endl;

    // Info #3: Other possible definitons are related with 
    // std::chrono::year_month_weekday in case you do not know the exact day
    // but you have a specific day name in a certain week.
    std::chrono::year_month_weekday tentative_date =
        2024y / std::chrono::August / std::chrono::Wednesday[3];
    std::cout << tentative_date << std::endl;

    return 0;
}


