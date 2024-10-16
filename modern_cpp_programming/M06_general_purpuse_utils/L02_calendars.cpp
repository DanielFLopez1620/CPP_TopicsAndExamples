// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Time management is a common operation, and after C++11 you have the chrono
 * durations you watched on the previous lesson. Then you can also use clocks,
 * time points and durations, however there is more like times and dates which
 * wwas extended in C++20 to add support with time zones, times of day and more
 * types of clocks.
 * 
 * The chrono library added some types to support calendars, which are:
 * 
 * - day : A day of a month
 * - month : A mont of a year
 * - year : A year in the Gregorian calendar
 * - weekday : A day of the week in the Gregorian calendar
 * - weeday_indexed : The nth weekday of a month [1, 5]
 * - weekday_last : The last weekday of a month
 * - month_day: A specific day of a specific month
 * - month_day_last : The last day of a specific month
 * - month_weekday : The nth weekday of a specific month
 * - month_weekday_last : The last weekday of a specific month
 * - year_month : A specific month of a specific year
 * - year_month_day : A specific year, month and day
 * - year_month_day_last : The last day of a specific year and month
 * - year_month_weekday : The nth weeday of a specific year and month
 * - year_month_weekday_last : The last weeday of a specific year and month
 * 
 * The types listed have:
 * - A default constructor (unitialized)
 * - Member functions to access the parts of the entity
 * - .ok() method to check if it is valid
 * - non-member comparison operator to compare the value types
 * - Most of them have the operator/ to indicate Gregorian division
 *   which can be in Y/M/D, M/D/Y and D/M/Y.
 * 
 * Other things to keep in mind are: 
 * - A day must be between 1 and 31 (but depends on the month)
 * - std::chrono::last indicates the last day of a month
 * - weekday[n] inidcates the wee of the month (1 to 5)
 * - weekday[std::chrono::last] indicates the last week
 * - When defining gregorian dates it is recommended to differentatie form the
 *   format by providing user-defined literals like ""y and ""d to specify
 *   in whihc position is the day or/and the year.
 * - You can add months with std::chrono::<month> were month can be
 *   January, February and so on.
 * - You can add the weekday with std::chrono::<weekday> where it can be
 *   Sunday, Monday, Tuesday...
 * - The year_month_day has a implicit conversion from/to std::chrono::sys_days
 *   and std::chrono::time_point. 
 * - You can use std::chrono::system_clock, since C++20 it is based on the
 *   Unix time whihc is 00:00:00 UTC on January 1st of 1970.
 * 
 * Check out the calendars implementations, in the next lesson we will explore
 * about time zones. You can use this code with:
 * 
 *      g++ -std=c++20 L02_calendars.cpp -o cal.out
 *      ./cal.out
 * 
 * For more info, you can consider checking:
 *      https://www.modernescpp.com/index.php/c20-time-of-day/
 */

// --------------------------- REQUIRED HEADERS -------------------------------
#include <chrono>  // Time management with different precisions
#include <iomanip> // Allow manipulation and control of output streams

// --------------------------- NAMESPACES CONSIDERATIONS ----------------------
using namespace std::chrono_literals; // For chrono user defined literals

/**
 * The definitions presented below are overrides of the operator<< for different
 * types of the chrono library in order to print them, as currently with g++20 
 * and g++23 on Ubuntu 22.04 I wasn't able to print them with the original 
 * operator.
 */
namespace std::chrono 
{
    /**
     * Output stream to display years
     * 
     * @param os Ostream considered
     * @param y Years chrono type
     * 
     * @return Formatted ostream to print years
     */
    std::ostream& operator<<(std::ostream& os, const year& y) 
    {
        return os << int(y);

    } // operator<< (year)

    /**
     * Output stream to display months
     * 
     * @param os Ostream considered
     * @param m Months chrono type
     * 
     * @return Formatted ostream to print months
     */
    std::ostream& operator<<(std::ostream& os, const month& m) 
    {
        return os << unsigned(m);

    } // operator<< (month)

    /**
     * Output stream to display days
     * 
     * @param os Ostream considered
     * @param y Days chrono type
     * 
     * @return Formatted ostream to print days
     */
    std::ostream& operator<<(std::ostream& os, const day& d) 
    {
        return os << unsigned(d);

    } // operator<< (day)

    /**
     * Output stream for printing gregorian dates that contains year, month and 
     * day in a valid way. It uses the overloads of the operator<< for year,
     * month and day.
     * 
     * @param os Ostream considered
     * @param ymd Gregorian date
     * 
     * @return os Date in format Year/Month/Day
     */
    std::ostream& operator<<(std::ostream& os, const year_month_day& ymd) 
    {
        return os << ymd.year() << '/' << ymd.month() << '/' << ymd.day();

    } // operator<< (year_month_day)

    /**
     * Output stream for printing gregorian days that contains year, month and 
     * day given by the day of a given (number) week. It uses the overlaods of
     * operator<< for year and month, while making an stimate considering the 
     * first day of the month, and cheking if the date is valid.
     * 
     * @param os Ostream considered
     * @param ymd Gregorian date
     * 
     * @return os Date in format Year/Month/Day
     */
    std::ostream& operator<<(std::ostream& os, 
        const std::chrono::year_month_weekday& ymdw) 
    {

        // Obtain year and month to os
        os << int(ymdw.year()) << '/';
        os << unsigned(ymdw.month()) << '/';

        // Get week index 
        auto week_num = unsigned(ymdw.index());
        auto day_num = unsigned(ymdw.weekday().iso_encoding());

        // Obtain the first day of the month and the first week
        auto date_ymd = ymdw.year() / ymdw.month() / day{1}; 
        auto first_wd = weekday{date_ymd};
        auto first_wd_num = unsigned(first_wd.iso_encoding());

        // Stimate the difference in weeks and days to the desired weekday
        auto weekday_diff = (day_num - first_wd_num + 7) % 7;

        // Format the date
        auto proper_date = ymdw.year() / ymdw.month() / day{1 + 
            weekday_diff + (week_num - 1) * 7};
        
        // Obtain day to os
        os << unsigned(proper_date.day()) << '/';

        // Determinate the weekday
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

        // Add the week number
        os << " week " << week_num << " ]";

        return os;
    } // operator<< (year_month_weekday)

    /**
     * Template overwrite to print hours format of the structure hh:mm:ss
     * 
     * @param os Ostream considered
     * @param hms Duration passed
     * 
     * @return Formatted hour:minute:seconds time
     */
    template <typename Duration>
    std::ostream& operator<<(std::ostream& os, const hh_mm_ss<Duration>& hms) 
    {
        // Verify if number aren't negative
        if (!hms.is_negative()) 
        {
            // Use ionmaip library for better formatting of single digit hours
            os << std::setw(2) << std::setfill('0') << hms.hours().count() << ":"
            << std::setw(2) << std::setfill('0') << hms.minutes().count() << ":"
            << std::setw(2) << std::setfill('0') << hms.seconds().count();
            if constexpr (hh_mm_ss<Duration>::fractional_width > 0) 
            {
                os << "." << std::setw(hh_mm_ss<Duration>::fractional_width) 
                   << std::setfill('0') << hms.subseconds().count();
            }
        } 
        else 
        {
            // If they are negatives consider -1 multiplication
            os << "-";
            os << std::setw(2) << std::setfill('0') << -hms.hours().count() 
               << ":" << std::setw(2) << std::setfill('0') << -hms.minutes().count() 
               << ":" << std::setw(2) << std::setfill('0') << -hms.seconds().count();
            if constexpr (hh_mm_ss<Duration>::fractional_width > 0) 
            {
                os << "." << std::setw(hh_mm_ss<Duration>::fractional_width) 
                   << std::setfill('0') << -hms.subseconds().count();
            }
        }

        return os;

    } // operator<< (hh_mm_ss)

    /**
     * Template for displaying time points
     * It considers year, month, day, hours, minutes and seconds.
     * 
     * @param os Output stream considered
     * @param time_point Time with YY/MM/DD HH:MM:SS
     * 
     * @return Formatted output
     */
    template <typename Clock, typename Duration>
    std::ostream& operator<<(std::ostream& os, const time_point<Clock, Duration>& tp) 
    {

        // Extract the time_point as sys_time and floor it to the nearest second
        auto tp_seconds = time_point_cast<seconds>(tp);

        // Extract the date part
        auto dp = floor<days>(tp_seconds);
        year_month_day ymd{dp};

        // Extract the time part (hours, minutes, seconds)
        auto time_since_midnight = tp_seconds - dp;
        auto h = duration_cast<hours>(time_since_midnight);
        auto m = duration_cast<minutes>(time_since_midnight - h);
        auto s = duration_cast<seconds>(time_since_midnight - h - m);

        // Print the date and time
        os << ymd << ' '
        << std::setfill('0') << std::setw(2) << h.count() << ':'
        << std::setfill('0') << std::setw(2) << m.count() << ':'
        << std::setfill('0') << std::setw(2) << s.count();

        return os;
    
    } // operator<<(time_point)

} // namespace std::chrono

// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 2: Using chrono calendars:\n" << std::endl;
    
    // Info #1: You can use Gregorian representation for different formats, by
    // here you can consider using two forms of creation (you can use 
    // namespaces to avoid long definitons, here they are used to tell you
    // more about them in a proper way ando do not forget to check the 
    // the overload of the operator<< to make possible print):
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
    // but you have a specific day name in a certain week. (Do not forget to
    // check the overload of the operator<< to make the print possible)
    std::chrono::year_month_weekday tentative_date =
        2024y / std::chrono::August / std::chrono::Wednesday[3];
    std::cout << "Considering weeday:\n\tFor the third Wednesday of Aug 2023: " 
              << tentative_date << std::endl;

    // Info #4: You can also take the current day, and use it to specify
    // the previous and next day, by considering 
    // std::chrono::system_clock_now() and using conversions of days and ymd:
    auto today = 
        std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    auto tomorrow = today + std::chrono::days{ 1 };
    auto yesterday = today - std::chrono::days{ 1 };
    std::chrono::year_month_day today_ymd = today;
    std::chrono::year_month_day tomorrow_ymd = tomorrow;
    std::chrono::year_month_day yesterday_ymd = yesterday;
    std::cout << "Relative dates: " << std::endl
              << "\tToday: " << today_ymd << std::endl
              << "\tYesterday: " << yesterday_ymd << std::endl
              << "\tTomorrow: " << tomorrow_ymd << std::endl;

    // Info #5: Another useful thing is to determinate the first and last day
    // of the given month and year, by using the number 1 to obtain the first
    // day and 'last' for the last one, as follows:
    auto first_day_cm = today_ymd.year() / today_ymd.month() / 1;
    auto last_day_cm = today_ymd.year() / today_ymd.month() / std::chrono::last;
    std::cout << "Obtaining first and last day of the current month:" 
              << std::endl << "\tFirst day of this month: " << first_day_cm
              << std::endl << "\tLast day of this month: " << last_day_cm
              << std::endl;

    // Info #6: If you need to consider the differences of some dates in days,
    // you can consider using the counter by considering a conversion from the
    // year_month_day to sys_days, and make the difference
    auto date_1 = 2024y / 1 / 10;
    auto date_2 = 2024y / 4 / 10;
    std::chrono::sys_days sys_date_1 = date_1;
    std::chrono::sys_days sys_date_2 = date_2;
    std::chrono::days difference = sys_date_2 - sys_date_1;
    std::cout << "Difference in days of dates: " << std::endl
              << "\tDate 1: " << date_1 << std::endl
              << "\tDate 2: " << date_2 << std::endl
              << "\tDifference in days: " << difference.count() << std::endl;

    // Info #7: There is also a validation method to check if a date is valid
    // and properly defined, and it is the ok() method.
    auto wrong_date = 2020y / 2 / 30;
    std::cout << "Checking if a date is correct: " << std::endl
              << "\t" << date_1 << "?: " << date_1.ok() << std::endl
              << "\t" << date_2 << "?: " << date_2.ok() << std::endl
              << "\t" << wrong_date << "?: " << wrong_date.ok() << std::endl;

    // Info #8: You can consider durations of days in terms of hours in clock,
    // you can use time of day (Duration) class template, it can even fit
    // when the minutes and seconds exceed 60:
    auto time_od1 = std::chrono::hh_mm_ss(16h + 15min + 20s);
    auto time_od2 = std::chrono::hh_mm_ss(32h + 67min + 1620s);
    std::cout << "Interacting with time of days: " << std::endl
              << "\tTime 1 in format hours:minutes:seconds : " << time_od1 
              << std::endl << "\tTime 1 just hours: " 
              << time_od1.hours().count() << std::endl
              << "\tTime 1 just minutes: " << time_od1.minutes().count()
              << std::endl << "\tTime 1 just seconds: " 
              << time_od1.seconds().count() << std::endl
              << "\tTime 2 that passed limits 60min, 60sec : "
              << time_od2 <<std::endl << "\tIs it am?: "
              << std::chrono::is_am(time_od2.hours()) << std::endl;

    // Info #9: You can combine date (year_month_day) with time parts (hours,
    // minutes and seconds).
    auto time_point = std::chrono::sys_days{2024y / 8 / 16} + 12h + 30min + 45s;
    std::cout << "Using time points (year_month_day_hours_minutes_seconds:" 
              << std::endl << "\tDate 1:" << time_point << std::endl;

    return 0;

} // main
