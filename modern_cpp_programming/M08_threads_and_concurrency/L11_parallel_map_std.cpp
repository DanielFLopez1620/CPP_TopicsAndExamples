// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

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
 */

#include <execution>
#include <algorithm>
#include <functional>

// ----------------- FUNCTION PROTOTYPES --------------------------------------

template <typename Iter, typename F>
void parallel_map_std(Iter begin, Iter end, F f);

template <typename Iter, typename R, typename F>
R parallel_fold_std(Iter begin, Iter end, R init, F op);


// ----------------- MAIN IMPLEMENTATION --------------------------------------
int main(int argc, char** argv[])
{
    return 0;
}

// ----------------- FUNCTION DEFINITIONS ------------------------------------
template <typename Iter, typename F>
void parallel_map_std(Iter begin, Iter end, F f)
{
    std::transform(std::execution::par, begin, end, begin,
        std::forward<F>(f));
}

template <typename Iter, typename R, typename F>
R parallel_fold_std(Iter begin, Iter end, R init, F op)
{
    return std::reduce(std::execution::par, begin, end, init,
        std::forward<F>(op));
}