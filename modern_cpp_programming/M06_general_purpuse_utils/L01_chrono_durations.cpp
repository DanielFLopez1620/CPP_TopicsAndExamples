// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

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
              << std::endl << "\t" 
              
    // Info #3: You can proceed to make conversion from lower precision
    // duration to a higher precision duration using .count() method.

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