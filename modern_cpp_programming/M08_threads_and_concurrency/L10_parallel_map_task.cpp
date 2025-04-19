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
 * 
 * The difference to the approach on the previous lesson is the usage of
 * asunchronous functions, where the results are made available by using
 * 'std::future'. Again, we use 'std::thread::hardware_concurrency' so we can
 * have a hint on how many threads can be implemented.
 * 
 * What are the reasons for this approach? Well, it avoid lower-level details
 * for threading and it could provide the fastest execution time for the
 * parallel function because there is a minimum overhead of context
 * switching and waiting time.
 */

// --------------------- REQUIRED HEADERS -------------------------------------
#include <functional>
#include <algorithm>
#include <thread>
#include <future>
#include <iomanip>

// --------------------- FUNCTION PROTOTYPES ----------------------------------

unsigned get_no_of_threads();

// Info #1: Define a function template for iterating over a range by
// considering a function to apply, in this case, to all the elements as it is
// a map.
template <typename Iter, typename F>
void parallel_map_tasks(Iter begin, Iter end, F f);

template <typename Iter, typename R, typename F>
R parallel_reduce_tasks(Iter begin, Iter end, R init, F op);

int main(int argc, char* argv[])
{
    std::vector<int> sizes
    {
        10000, 100000, 500000,
        1000000, 2000000, 5000000,
        10000000, 25000000, 50000000
    };

    std::cout << std::right << std::setw(8) << std::setfill(' ') << "size"
              << std::right << std::setw(8) << "std map"
              << std::right << std::setw(8) << "pll map"
              << std::endl;

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
void parallel_map_tasks(Iter begin, Iter end, F f)
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

template <typename Iter, typename R, typename F>
R parallel_reduce_tasks(Iter begin, Iter end, R init, F op)
{
    auto size = std::distance(begin, end);
    if(size <= 10000)
    {
        return std::accumulate(begin, end, init, std::forward<F>(op));
    }  
    else
    {
        auto no_of_tks = get_no_of_threads();
        auto part = size / no_of_tks;
        auto last = begin;
        std::vector<std::future<R>> tasks;
        for(unsigned i = 0; i < no_of_tks; ++i)
        {
            if(i == no_of_tks - 1)
            {
                last = end;
            }
            else
            {
                std::advance(last, part);
            }
            tasks.emplace_back(
                std::async(std::launch::async,
                [=,&op]
                {
                    return std::accumulate(begin, last, R{}, std::forward<F>(op));
                }
            ));
            begin = last;
        }
        std::vector<R> values;
        for(auto &tk : tasks)
        {
            values.push_back(tk.get());
        }
        return std::accumulate(std::begin(values), std::end(values),
            init, std::forward<F>(op));
    }
}