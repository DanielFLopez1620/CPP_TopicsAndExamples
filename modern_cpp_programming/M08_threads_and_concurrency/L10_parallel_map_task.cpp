// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Let's take a similar approach for implementing parallel mmappings and
 * folding operations, but implemeting tasks.
 * 
 * Task are high-level alternatives to threads for performing concurrent
 * computations, for example, 'std::asyncs()' enable us to execute
 * functions asynchronously withouth the requirement of a lower-level
 * thread. 
 */

// --------------------- REQUIRED HEADERS -------------------------------------
#include <functional>
#include <algorithm>
#include <thread>
#include <future>

// --------------------- FUNCTION PROTOTYPES ----------------------------------

unsigned get_no_of_threads();

// Info #1: Define a function template for iterating over a range by
// considering a function to apply, in this case, to all the elements as it is
// a map.
template <typename Iter, typename F>
void parallel_map_tasks(Iter begin, Iter end, F f);

int main(int argc, char* argv[])
{

    return 0;
}

// ------------------- FUNCTION DEFINTIONS -----------------------------------
/**
 * Return the number allowed of threads for concurrency
 * 
 * @return Hardware concurrency
 */
unsigned get_no_of_threads()
{
    return std::thread::hardware_concurrency();
}

template <typename Iter, typename F>
void parallel_map(Iter begin, Iter end, F f)
{
    // Info #2: Check the size of the range. If it is smaller than the 
    // specified threshold, it will apply the map in a direct way.
    auto size = std::distance(begin, end);
    if(size <= 10000)
    {
        std::transform(begin, end, begin, std::forward<F>(f));
    }
    else
    {
        // Info #3: Consider how many parts are required for a proper
        // parellel process.
        auto no_of_tasks = get_no_of_threads();
        auto part = size / no_of_tasks;
        auto last = begin;

        // Info #4: Considering future tasks, create a loop to async
        // launch the elemnts by using lambda functions
        std::vector<std::future<void>> tasks;
        for(unsigned i = 0; i < no_of_tasks; ++i)
        {
            if(i == no_of_tasks - 1)
            {
                last = end;
            }
            else
            {
                std::advance(last, part);
            }
            tasks.emplace_back(std::async(
                std::launch::async,
                [=, &f]
                {
                    std::transform(begin, last, begin, std::forward<F>(f));
                }
            ));
            begin = last;
        }

        // Info #5: Wait for the task to be completed
        for (auto & task : tasks)
        {
            task.wait();
        }
    }
}