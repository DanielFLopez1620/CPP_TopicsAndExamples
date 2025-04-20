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
 * 
 * In the code below we implemnt mappings and folding, divided in common ones
 * and parallel ones. We base this desicion on the quantity of elements to
 * consider, if a threshol is surpassed then the process is divided.
 * 
 * The division is made by considering the 'std::thread::hardware_concurrency()'
 * which returns the number of concurrent threads supported. Howerver, this is
 * a hint rather than an accurate value.
 * 
 * The implementations are based on 'std::transform()' and 'std::accumulate()',
 * that were presented in the module 3.
 * 
 * When ready, you can compile and run with:
 * 
 *      g++ -std=c++20 L09_parallel_map.cpp -o parallel_f_and_m.out
 *      ./parallel_f_and_m.out
 */

// --------------------------- REQUIRED HEADERS -------------------------------
#include <thread>      // For using concurrency and parallel process.
#include <algorithm>   // A collection of common and usefult algorithms.
#include <numeric>     // Usage of different type of numeric values.
#include <chrono>      // For time management with different precisions.
#include <cassert>     // For assertions and raise of errors/exceptions
#include <functional>  // Related with functions usage

// --------------------------- GLOBAL DEFINTIONS ------------------------------
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

// ---------------------------- FUNCTION PROTOTYPES --------------------------

unsigned get_no_of_threads();


// Info #1: Let's create a parallel version of map, to start we create a
// template that considers the 'begin' and 'end' iterators. Go to the function
// definition and info #2 to understand the implementation.
template <typename Iter, typename F>
void parallel_map(Iter begin, Iter end, F f);

// Info #5: Let's also create a parallel version of fold, here we also
// consider a prototype that considers the 'begin' and 'end' iterator. But also,
// the 'init' value and the 'operation/function' to implement.
template <typename Iter, typename R, typename F>
R parallel_fold(Iter begin, Iter end, R init, F op);

// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    // Initialization of sizes and display
    std::vector<int> sizes
    {
    10000, 100000, 500000, 
    1000000, 2000000, 5000000, 
    10000000, 25000000, 50000000
    };

    std::cout << std::right << std::setw(8) << std::setfill(' ') << "Size"
              << std::right << std::setw(8) << std::setfill(' ') << "Std Map"
              << std::right << std::setw(8) << std::setfill(' ') << "Par Map"
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
                parallel_map(std::begin(vec_copy2), std::end(vec_copy2),
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
                res2 = parallel_fold(std::begin(vec_copy4), std::end(vec_copy4), 0LL, std::plus<long long>());

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

// ------------------------ FUNCTION DEFINITIONS ------------------------------

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
 * Implement a map that is paralel in case of a big number of features to process.
 * 
 * @param begin Beginning iterator of the array
 * @param end End iterator of the array
 * @param f Function to implement to each element
 */
template <typename Iter, typename F>
void parallel_map(Iter begin, Iter end, F f)
{
    // Info #2: Then check the size of the range and compare it with a
    // threshold, so if it isn0t surpasssed it do the sequential exec.
    auto len = std::distance(begin, end);
    if(len <= THRESHOLD)
    {
        std::transform(begin, end, begin, std::forward<F>(f));
    }
    else
    {
        // Info #3: For larger number consider a different number of threads
        // so it divides the task to make it parallel.
        auto no_th = get_no_of_threads();
        auto part = len / no_th;
        auto last = begin;

        // Info #4: Start the threads and generate a subsequential mapping to
        // each one.
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

        // Join the threads for the mapping
        for(auto & th: ths)
        {
            th.join();
        }
    }
} // parallel_map()

/**
 * Implement a custom fold (apply a function then sum the values) in a parallel
 * way for cases where there are many instances.
 * 
 * @param begin Beginning iterator of the array.
 * @param end Ending iterator of the array.
 * @param init Value to initialize the folding process.
 * @param op Function to apply to the elements.
 * 
 * @return Single value that summarize the folding (sum of values to the
 *         applied function).
 */
template <typename Iter, typename R, typename F>
R parallel_fold(Iter begin, Iter end, R init, F op)
{
    // Info #6: Check the size to consider if doing the process in one
    // single step or to divide it in multiple threads.
    auto size = std::distance(begin, end);
    if(size <= THRESHOLD)
    {
        return std::accumulate(begin, end, init, std::forward<F>(op));
    }
    else
    {
        // Info #7: For larger ranges split the number of thread by considering the
        // number of threads that your machine is able to do.
        auto no_of_th = get_no_of_threads();
        auto part = size / no_of_th;
        auto last = begin;

        // Info #8: Start the threads and create a subsequential fold
        std::vector<std::thread> ths;
        std::vector<R> values (no_of_th);
        for(unsigned i = 0; i < no_of_th; ++i)
        {
            if(i == no_of_th - 1)
            {
                last = end;
            }
            else
            {
                std::advance(last, part);
            }
            ths.emplace_back(
                [=, &op](R& result)
                {
                    result = std::accumulate(begin, last, R{},
                        std::forward<F>(op));
                }, std::ref(values[i])
            );
            begin = last;
        }

        // Join the threads for completing the partial folds.
        for(auto & th : ths)
        {
            th.join();
        }

        // Info #9: Wait for the threads to join and accumulate the final
        // result.
        return std::accumulate(std::begin(values), std::end(values), init,
            std::forward<F>(op));
    }
} // parallel_fold()