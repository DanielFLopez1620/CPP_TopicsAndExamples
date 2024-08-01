// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Chrono is a library related with time and dates, it know as a general 
 * purpuse library (one of the general purpose libraries that will be
 * covered for the module 6). You can include it by adding <chrono> header and
 * use the std::chrono namespace, so go to the code belows and let's explore
 * what it can offer. 
 * 
 */

#include <chrono>

template <typename Rep, typename Period>
std::ostream& operator<<(std::ostream& os, 
    const std::chrono::duration<Rep, Period>& d);


int main(int argc, char* argv[])
{
    
    // Info #1: You can use std::chrono::duration typedefs for defining 
    // different precisions of time units, also do not forget to check the
    // implementation of the operator<< for printing the durations.
    const std::chrono::hours third_of_day(8);
    const std::chrono::minutes third_of_hour(20);
    const std::chrono::seconds third_of_minute(20);
    const std::chrono::milliseconds third_of_second(333);
    const std::chrono::microseconds third_of_millisecond(333);
    std::cout << "Using different chrono durations:" << std::endl
              << "\tHours: " << third_of_day << std::endl
              << "\tMinutes: " << third_of_hour << std::endl
              << "\tSeconds: " << third_of_minute << std::endl
              << "\tMilliseconds: " << third_of_second << std::endl
              << "\tMicroseconds: " << third_of_millisecond << std::endl;

    // Info #2: After C++14 you can use the namespace std::crhono_literals
    // for a better implementation of the metrics by considering suffixes:
    using namespace std::chrono_literals;
    auto quarter_of_day = 6h;
    auto quarter_of_hour = 15min;
    auto quarter_of_minute = 15s;
    auto quarter_of_second = 250ms;
    auto quarter_of_millisecond = 250us;
    std::cout << "Using chrono literals, but let's just display a count "
              << std::endl << "\t" << quarter_of_day << " : " << quarter_of_hour
              << " : " << quarter_of_minute << " : " << quarter_of_second
              << " : " << quarter_of_millisecond << std::endl;

    // Info #3: You can proceed to make conversion from lower precision
    // duration to a higher precision duration by using a duration definition
    // cast, in other works, assigning a different duration a previously defined.
    std::chrono::hours set_hours(16);
    std::chrono::minutes set_hours_in_min(set_hours);
    std::cout << "Converting from lower precision to higher: " << std::endl
              << "\tTime in hours: " << set_hours << std::endl
              << "\tSame time in minutes: " << set_hours_in_min << std::endl;

    // Info #4: You can also make cast from higher precision to lower
    // precision, but for this case you will need to use 
    // std::chrono_duration_cast:
    auto just_seconds = 1620162s;
    auto just_seconds_in_h = std::chrono::duration_cast<std::chrono::hours>
        (just_seconds);
    std::cout << "Converting from higher precision to lower: " << std::endl
              << "\tTime in seconds: " << just_seconds << std::endl
              << "\tSame time in hours: " << just_seconds_in_h << std::endl;

    // Info #5: When making cast, you usually do approximations, then you can
    // use conversion functions like floor(), round() and ceil(), this was
    // implemented in C+++17.
    auto js_floor = std::chrono::floor<std::chrono::minutes>
        (just_seconds);
    auto js_ceil = std::chrono::ceil<std::chrono::minutes>
        (just_seconds);
    auto js_round = std::chrono::round<std::chrono::minutes>
        (just_seconds);
    std::cout << "Conversion considering approximations: " << std::endl
              << "\tSeconds: " << just_seconds << std::endl
              << "\tMinutes (Floor): " << js_floor << std::endl
              << "\tMinutes (Ceil): " << js_ceil << std::endl
              << "\tMinutes (Round): " << js_round << std::endl;
    
    // Info #6: You can also do arithmetic and comparison operations 
    auto sum_thirds = third_of_hour + third_of_minute + third_of_second;
    auto sum_of_quarters = quarter_of_minute + quarter_of_second 
        + quarter_of_millisecond;
    std::cout << "Making sums with different precisions: " << std::endl
              << "\tSum of third of hour, minute and second: " << sum_thirds
              << std::endl << "\tSum of quarter of minute, second and ms: "
              << sum_of_quarters << std::endl;
    
    return 0;
}

template <typename Rep, typename Period>
std::ostream& operator<<(std::ostream& os,
    const std::chrono::duration<Rep, Period>& d) 
{
    os << d.count();
    if (Period::den == 1 && Period::num == 3600) 
    {
        os << "h"; // hours
    } 
    else if (Period::den == 1 && Period::num == 60) 
    {
        os << "min"; // minutes
    } 
    else if (Period::den == 1) 
    {
        os << "s"; // seconds
    } 
    else if (Period::den == 1000) 
    {
        os << "ms"; // milliseconds
    } 
    else if (Period::den == 1000000) 
    {
        os << "us"; // microseconds
    } 
    else if (Period::den == 1000000000) 
    {
        os << "ns"; // nanoseconds
    } 
    else 
    {
        os << " [" << Period::num << "/" << Period::den << "]s";
    }
    return os;
}