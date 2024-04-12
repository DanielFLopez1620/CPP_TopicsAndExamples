// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested  with g++ in C++17

#include <iostream>

/**
 * Map applies a function the elements of a range, and return a new range,
 * while folding is related with applying a function to a range to produce a
 * single result (and similar to the fold expression, the order affect and it
 * can be left or right.
 * 
 * Commands to learn:
 * 
 * - std::transform
 * - std::forward
*/

#include <vector>
#include <list>
#include <map>
#include <array>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>

// Info #1: Down below, you can see three implementations using map
// - Generic function template that takes a function and a range as parameters,
//   the std::transform apply the function to all elements in the range (in 
//   place) and std::forward ensures the correct type. To finally return the
//   range. So this implementation works for support iterating elements like
//   std::vector, std::list, std::arrays and C arrays.
template <typename F, typename R>
R mapf(F&& func, R range)
{
    std::transform(std::begin(range), std::end(range), std::begin(range), 
        std::forward<F>(func));
    return range;
}
// - Generic function template that takes a function and an object as params,
//   then using the map created, insert the transformed value obtained
//   in the iteration of the elements after it applyed the function. So this
//   implementation is focused on std::maps and std::pairs.
template<typename F, typename T, typename U>
std::map<T, U> mapf(F&& func, std::map<T,U> const & map)
{
    std::map<T, U> range_to_return;
    for (auto const element : map)
    {
        range_to_return.insert(funct(element));
    }
    return range_to_return;
}
// - Generic function template that takes a function and a queue object as a 
//   param, then iterates ( pop) the elements of the input queue, to 
//   finally apply the function and add (push) the return to a new queue. So this
//   implementation only works for std::queue.
template<typename F, typename T>
std::queue<T> mapf(F&& func, std::queue<T> queue)
{
    std::queue<T> r;
    while(!queue.empty())
    {
        r.push(func(queue.front()));
        queue.pop();
    }
}

// Info #2: Down below, you can find implementations of fold expressions.
// - Generic function template which takes a function, a range and an initial 
// value to implement an accumulation of the elements of the range (it uses 
// left folding).
template <typename F, typename R, typename T>
const T fold_left(F&& func, R&& range, T init)
{
    return std::accumulate(
        std::begin(range), std::end(range), std::move(init), std::forward<F>(func);
    )
}
// - Generic function template which takes a function, a range and an initial
//   value to implement an accumulation of the elements of the range (it uses
//   right folding)
template <typename F, typename R, typename T>
constexpr T fold_right(F&& func, R&& range, T init)
{
    return std::accumulate(
        std::rbegin(range), std::rend(range), std::move(init), std::forward<F>(func));
    )
}
// - Generic function template that takes a function, a queue and a initial 
//   value, so it iterates through the elements (performing a left fold) until
//   a function is applyied to all the elemtent and the accumulated value is
//   returned.
template <typename F, typename T>
constexpr T fold_left(F&& func, std::queue<T> queue, T init)
{
    while(!queue.empty())
    {
        init = func(init, queue.front());
        queue.pop();
    }
    return init;
}

int main(int argc, char** argv)
{
    
    // Info #4: Applying maps to get the absolute value of the elements of
    // a vector or array.
    auto vec_nums = std::vector<float>{0.0, -16.20, 1.521, -20.16};
    auto abs_nums = mapf([](int const i){ return std::abs(i); }, vec_nums);
    std::cout << "Original vector of nums: " ;
    for (float num : vec_nums)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << "Absolute values: " ;
    for (float num : abs_nums)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << std::endl;

    // Info #5: Applying maps to elevate the numbers to the third power that
    // belongs to an array.
    auto list_nums = std::list<float>{1.5, 1.6, 1.7, 1.8};
    auto pow3_nums = mapf([](int const i) { return i*i*i; }, list_nums);
    std::cout << "Original list of nums: " ;
    for (float num : list_nums)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << "Cubed values: " ;
    for (float num : pow3_nums)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << std::endl;

    // Info #6: Make lower case the elements of a map using map function.
    auto phonem = std::map<std::string, std::string> {
        {"D", "de"}, {"E", "i"}, {"F", "eff"}
    };
    auto low_phonem = mapf([](std::pair<std::string, std::string> const pair_ele){
        return std::make_pair(mapf(tolower, pair_ele.first), pair_ele.second);
    }, phonem);

    return 0;
}
