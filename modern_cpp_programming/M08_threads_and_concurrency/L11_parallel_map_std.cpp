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