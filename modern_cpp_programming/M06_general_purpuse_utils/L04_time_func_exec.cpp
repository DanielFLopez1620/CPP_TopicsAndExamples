// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * We can use chrono for more than using dates, times zones and caledars, as
 * we can also use the clock and the library to measure the execution of
 * a function.
 * 
 * This can be done with the following steps:
 * 
 *      1. Retrieve the current momen of time using a standard clock
 *      2. Call the function you want to measure
 *      3. Retrevie the time again, just after the function execution
 *      4. Calculate the differente to obtain the exectuion time
 *      5. Convert it to ms or ns to see the resolution of execution
 * 
 * But you can even go further and create a reusable component:
 *      
 *      1. Create a class template with the resolution and clock of interest
 *      2. Create a static variadic function template that takes a function
 *         and its arguments.
 *      3. Implement the pattern shown previously, invoking the function with
 *         the corresponding args.
 *      4. Return a duration to check the time execution.
 * 
 * Both examples are shown in this code.
 * 
 * But before moving on, let's clarify somethings:
 * 
 * - Clock, it has a beginning time called epoch and it has a tick rate that
 *   defines the increment between two time points.
 * - The current time is a time point, which is returned by the stati member
 *   "now()"
 * - The first epoch is created by the default constructor of a time point for
 *   a particular clock
 * - The minimum time that can be represented by a time clock can be obtained
 *   with the static member "min()" and the maximum time with "max()".
 * 
 * Also, you may have to differentiate between clock types:
 * 
 * - system_clock:  Uses the urrent system real-time clock.
 * - high_resolution_clock: Uses the shortest possisble tick period of the
 *   current system.
 * - steady_clock: A clock that is never adjusted, the differences of totime
 *   points is always positive.
 * - utc_clock: C++20 coordinated with the Universal Time
 * - tai_clock: C++20 for the International Atomic Clock
 * - gps_clock: C++20 for GPS time
 * - file_clock: C++20 oriented for expressing file times.
 * 
 * When ready, check the code, and compile it with:
 * 
 *      g++ -std=c++20 L04_time_func_exec -o func_time.out
 *      ./func_time.out
 */

// --------------------------- REQUIRED LIBRARY ------------------------------ 
#include <chrono>  // For time management with different time precisions

// ------------------------- FUNCTION PROTOTYPES ------------------------------
void do_something(int);

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    // Info #1: You can use the high resolution clock to obtain the times just
    // before and just after the time execution to calculate the difference,
    // then obtaining the time execution.
    auto start = std::chrono::high_resolution_clock::now();
    do_something(100000);
    auto diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Execution (ms):"
              << std::chrono::duration<double, std::milli>(diff).count() 
              << std::endl;
    return 0;
}

// ---------------------- FUNCTION DEFINITIONS --------------------------------

/**
 * Generic implementation of a template that receives a function and set a 
 * clock, to achieve a measure of time.
 * 
 * @param func Pointer to function of interest
 * @param args Variadic arguments for the function
 */
template <typename Time = std::chrono::nanoseconds,
          typename Clock = std::chrono::high_resolution_clock>
struct perf_timer
{
    template <typename F, typename... Args>
    static Time duration(F && func, Args... args) 
    {
        auto start = Clock::now();
        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        auto end = Clock::now();
        return std::chrono::duration_cast<Time>(end - start);
    }
};

/**
 * Simple function oriented to do a generic action for a long time, to take
 * time in the processor, as we will use it to measure time exection.
 * 
 * @param count Integer count value, use a very big value
 */
void do_something(int count)
{
    int i = 0;
    while(i < count)
    {
        i++;
        // ++i;
    }
}