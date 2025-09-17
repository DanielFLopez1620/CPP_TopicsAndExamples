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
 * 
 * Do not forget to compare the times between this lesson and the previous
 * one and obtain a conclusion on how to proceed.
 * 
 * Once you are done reading, you can compile and execute with:
 * 
 *      g++ -std=c++20 L10_parallel_map_tasks.cpp -o pll_map_tasks.out
 *      ./pll_map_tasks.out
 */

// --------------------- REQUIRED HEADERS -------------------------------------
#include <functional> // Related with function implementions
#include <algorithm>  // General purpose algorithms
#include <thread>     // Usage of threads for concurrency and parallelism
#include <future>     // Related with asynchronous process and tasks
#include <iomanip>    // Input/Ouput Stream Manipulator
#include <cassert>    // For assertions and raises of errors/exceptions
#include <numeric>    // Used for different numeric types and number operations

// --------------------- GLOBAL DECLARATIONS ---------------------------------
const int THRESHOLD = 10000;

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

// --------------------- FUNCTION PROTOTYPES ----------------------------------

unsigned get_no_of_threads();

// Info #1: Define a function template for iterating over a range by
// considering a function to apply, in this case, to all the elements as it is
// a map.
template <typename Iter, typename F>
void parallel_map_tasks(Iter begin, Iter end, F f);


// Info #6: Define a function template for iterating over a range by
// considery a function to apply and having a value to initialize the
// fold/reduction.
template <typename Iter, typename R, typename F>
R parallel_reduce_tasks(Iter begin, Iter end, R init, F op);

// --------------------- MAIN IMPLEMENTATION ---------------------------------

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

    // Loop for mappings
    for(auto const size : sizes)
    {
        std::vector<int> num_vec(size);
        std::iota(std::begin(num_vec), std::end(num_vec), 1);
        auto vec_copy1 = num_vec;
        auto nor_map = perf_timer<>::duration([&]
            {
                std::transform(std::begin(vec_copy1), std::end(vec_copy1),
                    std::begin(vec_copy1), [](int const i){return i * i; }); 
            });
        auto vec_copy2 = num_vec;
        auto  pl_map = perf_timer<>::duration([&]
            {
                parallel_map_tasks(std::begin(vec_copy2), std::end(vec_copy2),
                    [](int const i){return i * i; }); 
            });
        std::cout << std::right << std::setw(8) << std::setfill(' ') << size
                  << std::right << std::setw(8) 
                  << std::chrono::duration<double, std::micro>(nor_map).count()
                  << std::right << std::setw(8) 
                  << std::chrono::duration<double, std::micro>(pl_map).count()
                  << std::endl;
        
        assert(vec_copy1 == vec_copy2);
    }

    std::cout << std::right << std::setw(8) << std::setfill(' ') << "Size"
              << std::right << std::setw(8) << std::setfill(' ') << "Std Fld"
              << std::right << std::setw(8) << std::setfill(' ') << "Par Fld"
              << std::endl;

    // Loop for foldings
    for(auto const size : sizes)
    {
        std::vector<int> num_vec2(size);
        std::iota(std::begin(num_vec2), std::end(num_vec2), 1);
        auto vec_copy3 = num_vec2;
        auto res1 = 0LL;
        auto nor_fld = perf_timer<>::duration([&]
            {
                res1 = std::accumulate(std::begin(vec_copy3), std::end(vec_copy3),
                    0LL, std::plus<>()); 
            });
        auto vec_copy4 = num_vec2;
        long long int res2 = 0LL;
        auto pl_fld = perf_timer<>::duration([&]
            {
                res2 = parallel_reduce_tasks(std::begin(vec_copy4), std::end(vec_copy4), 0LL, std::plus<long long>());

            });
        std::cout << std::right << std::setw(8) << std::setfill(' ') << size
                  << std::right << std::setw(8) 
                  << std::chrono::duration<double, std::micro>(nor_fld).count()
                  << std::right << std::setw(8) 
                  << std::chrono::duration<double, std::micro>(pl_fld).count()
                  << std::endl;

        assert(res1 == res2);
    }

    return 0;

} // main()

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

/**
 * Implements a parallel map for ranges proposed as a generic template
 * that uses taks and asynchronous functions.
 * 
 * @param begin Init of the range
 * @param end End of the range
 * @param f Function to apply to all the elements
 * 
 */
template <typename Iter, typename F>
void parallel_map_tasks(Iter begin, Iter end, F f)
{
    // Info #2: Check the size of the range. If it is smaller than the 
    // specified threshold, it will apply the map in a direct way.
    auto size = std::distance(begin, end);
    if(size <= THRESHOLD)
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
} // parallel_map_tasks()


/**
 * Implements a parallel reduction for ranges proposed as a generic template
 * that uses taks and asynchronous functions.
 * 
 * @param begin Init of the range
 * @param end End of the range
 * @param init Value to initialize the fold
 * @param op Function to apply to all the elements
 * 
 */
template <typename Iter, typename R, typename F>
R parallel_reduce_tasks(Iter begin, Iter end, R init, F op)
{
    // Info #7: Check the size of the range, if it is smaller than the proposed
    // threshold, execute the folding as usual.
    auto size = std::distance(begin, end);
    if(size <= THRESHOLD)
    {
        return std::accumulate(begin, end, init, std::forward<F>(op));
    }  
    else
    {
        // Info #8: For bigger ranges, start by considering the possible
        // number of task to fragment the process.
        auto no_of_tks = get_no_of_threads();
        auto part = size / no_of_tks;
        auto last = begin;

        // Info #9: Start the asunchronous functions and execute the
        // folding for each fragment.
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

        // Info #10: Wait for the asynchrnous function to finish the execution
        // and finally fold the partial results.
        std::vector<R> values;
        for(auto &tk : tasks)
        {
            values.push_back(tk.get());
        }
        return std::accumulate(std::begin(values), std::end(values),
            init, std::forward<F>(op));
    }

} // parallel_reduce_tasks()