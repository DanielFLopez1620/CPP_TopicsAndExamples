// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with clang in C++20

#include <iostream>

/**
 * In the two previous lesson we explored about maps and folds with
 * threads and tasks in a parallel way. However, it doesn't stop there
 * as you can implement other elements for this process, for example,
 * until now we have amde the parallelization details (splitting data
 * and creation of tasks/threads) manually.
 * 
 * After C++17, many standard algorithms received a parallelization, even
 * some of them interact in a parallel way according the execution policy.
 * This will be the focus of this lesson.
 * 
 * To consider the execution of std algorithms with parallel setting,
 * keep in mind the next:
 * 
 * - Search for the algorithm and check it can be parallelized. Also,
 *   verify it is faster in a parallel way, for example, check that
 *   the operations are O(n) or worse complexity.
 * - Include the <execution> header.
 * - Provide the correct execution policy, for example, 
 *   'std::execution::par'.
 * 
 * In our case, mapping and foldings have a parallel implementation, and
 * you can check them in the code implementation.
 * 
 * Meanwhile, let's explore more about parallel functions. After C++17,
 * 69 standard algorithms included a paralell overload, and as mentioned
 * previously there are available by using execution policies from
 * <execution> header. These policies are:
 * 
 * - std::execution::sequenced_policy: Implemented in C++17, it indicates
 *   that the algorithm may no be executed in a parallel way, the object
 *   related to it is 'std::execution::seq'.
 * - std::execution::parallel_policy: Implemented in C++17, it indicates
 *   that the algorithm's execution may be parallelized and refers to the
 *   object 'std::execution::par'.
 * - std::execution::parallel_unsequenced_policy: Implemented in C++17,
 *   it aims for a parallelized and vectorized execution. The object related
 *   is 'std::execution::par_unseq'.
 * - std::execution::unsequenced_policy: Implemented in C++20, it searches
 *   for a vectorized execution, and the object is 'std::execution::unseq'.
 * 
 * Other useful algorithms you should know:
 * 
 * - 'std::for_each_n': Apply a given function to the N first elements, by
 *    considering a given policy.
 * - 'std::exclusive_scan': Computes partial sum of a range of elements but
 *   excludes the ith element form the ith sum.
 * - 'std::inclusive_scan': Computes the partial sum of a range of elements,
 *   but includes the ith element in the ith sum.
 * - 'std::transform_exclusive_scan': Applies a function and then calculates
 *   a exclusive scan.
 * - 'std::reduce': Out of order version of 'std::accumulate'
 * - 'std::transform_reduce' applies a function, then accumulates out of
 *   order.
 * 
 * Again, let's highlight that a algorithm that can run in parallel doesn't
 * imply it will. The reason is that the execution depends on hardware, data
 * and particularities of the algorithm, for example, algorithms like copy,
 * copy_n, fill, reverse, rotate and so on don't perform parallelization.
 * 
 * Let's take the opportunity to highlight that there is another function,
 * called 'std::transform_reduce' which composes the two opperations presented
 * in the two previous lesson into a single one. Even, it support parallelism
 * and vectorization.
 * 
 * Once you are ready, let's compile and execute the code:
 * 
 *      clang++ -std=c++20 -ltbb L11_parallel_map_std.cpp -o std_parallel.out
 *      ./std_parallel.out
 * 
 */

// ---------------------------- REQUIRED LIBRARIES ----------------------------
#include <execution>  // For using parallel/vector policies with certain alg.
#include <algorithm>  // General purpose algorithm collection
#include <functional> // Related with functions usage
#include <iomanip>    // I/O Manipulator
#include <assert.h>   // Assertions from C

// ----------------- FUNCTION PROTOTYPES --------------------------------------

template <typename Iter, typename F>
void parallel_map_std(Iter begin, Iter end, F f);

template <typename Iter, typename R, typename F>
R parallel_reduce_std(Iter begin, Iter end, R init, F op);

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



// ----------------- MAIN IMPLEMENTATION --------------------------------------
int main(int argc, char* argv[])
{
    std::vector<int> sizes
    {
        10000, 100000, 500000,
        1000000, 2000000, 5000000,
        10000000, 25000000, 50000000
    };

    std::cout << std::right << std::setw(8) << std::setfill(' ') << "size"
              << std::right << std::setw(8) << "sec map"
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
                parallel_map_std(std::begin(vec_copy2), std::end(vec_copy2),
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
              << std::right << std::setw(8) << std::setfill(' ') << "Sec Fld"
              << std::right << std::setw(8) << std::setfill(' ') << "Pll Fld"
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
                res2 = parallel_reduce_std(std::begin(vec_copy4), std::end(vec_copy4), 0LL, std::plus<long long>());

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

// ----------------- FUNCTION DEFINITIONS ------------------------------------

/**
 * Generic implemenation of a map function that uses a parallel execution
 * 
 * @param begin Begin iterator of the range
 * @param end  End iterator of the range
 * @param f Function to apply to all the elements
 */
template <typename Iter, typename F>
void parallel_map_std(Iter begin, Iter end, F f)
{
    std::transform(std::execution::par, begin, end, begin,
        std::forward<F>(f));
}

/**
 * Generic implemenation of a fold function that uses a parallel execution
 * 
 * @param begin Begin iterator of the range
 * @param end  End iterator of the range
 * @param init Value to initialize the fold
 * @param op Function to apply to all the elements
 * 
 * @return Folded value after applying the function
 */
template <typename Iter, typename R, typename F>
R parallel_reduce_std(Iter begin, Iter end, R init, F op)
{
    return std::reduce(std::execution::par, begin, end, init,
        std::forward<F>(op));
}