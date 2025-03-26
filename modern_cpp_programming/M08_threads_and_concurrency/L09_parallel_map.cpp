// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * You may remember 'maps' and 'folds' from module 3. The first one is oriented
 * to transform a range into a new range, and the second converts the range
 * into a single element.
 * 
 * But... what happens when we have long ranges? We can introduce concurrency,
 * threads and asynchronous task to speed up the execution.
 */

#include <thread>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <cassert>

const int THRESHOLD = 10000;

unsigned get_no_of_threads();

template <typename Time = std::chrono::microseconds,
    typename Clock = std::chrono::high_resolution_clock>
    struct perf_timer
{
    template <typename F, typename... Args>
    static Time duration(F&& f, Args... args)
    {
        auto start = Clock::now();

        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

        auto end = Clock::now();

        return std::chrono::duration_cast<Time>(end - start);
    }
};

// Info #1: Let's create a parallel version of map, to start we create a
// template that considers the 'begin' and 'end' iterators.
template <typename Iter, typename F>
void parallel_map(Iter begin, Iter end, F f)
{
    // Info #2: Then check the size of the range and compare it with a
    // threshold, so if it isn0t surpasssed it do the sequential exec.
    auto len = std::distance(begin, end);
    if(size <= THRESHOLD)
    {
        std::transform(begin, end, begin, std::forward<F>(f));
    }
    else
    {
        auto no_th = get_no_of_threads();
        auto part = len / no_th;
        auto last = begin;
        std::vector<std::thread> ths;
        for(unsigned i = 0; i < no_th; ++i)
        {
            if(i == no_th - 1)
            {
                last = end;
            }
            else
            {
                std::advance(last, part);
            }
            ths.emplace_back(
                [=,&f]{std::transform(begin, last, begin,
                    std::forward<F>(f)); }
            );
            begin = last;
        }
        for(auto & th: ths)
        {
            th.join();
        }

    }
}


int main(int argc, char* argv[])
{
    return 0;
}

unsigned get_no_of_threads()
{
    return std::thread::hardware_concurrency();
}