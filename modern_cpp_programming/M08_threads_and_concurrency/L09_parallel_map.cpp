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
#include <functional>

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

// Info #3: Let's also create a parallel version of fold, here we also
// consider a prototype that considers the 'begin' and 'end' iterator. But also,
// the 'init' value and the 'operation/function' to implement.
template <typename Iter, typename R, typename F>
R parallel_fold(Iter begin, Iter end, R init, F op);

// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
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
}

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

template <typename Iter, typename R, typename F>
R parallel_fold(Iter begin, Iter end, R init, F op)
{
    auto size = std::distance(begin, end);
    if(size <= 10000)
    {
        return std::accumulate(begin, end, init, std::forward<F>(op));
    }
    else
    {
        auto no_of_th = get_no_of_threads();
        auto part = size / no_of_th;
        auto last = begin;

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
        for(auto & th : ths)
        {
            th.join();
        }
        return std::accumulate(std::begin(values), std::end(values), init,
            std::forward<F>(op));
    }
}