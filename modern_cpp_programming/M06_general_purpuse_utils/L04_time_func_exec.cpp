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
 */

#include <chrono>

// ------------------------- FUNCTION PROTOTYPES ------------------------------
void do_something(int);

int main(int argc, char* argv[])
{
    // Info #1: You can use the high resolution clock to obtain the times just
    // before and just after the time execution to calculate the difference,
    // then obtaining the time execution.
    auto start = std::chrono::high_resolution_clock::now();
    do_something(100000);
    auto diff = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Execution (ms):"
              << std::chrono::duration<double, std::milli>(diff).count() << std::endl;
    return 0;
}

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

void do_something(int count)
{
    int i = 0;
    while(i < count)
    {
        i++;
        // ++i;
    }
}