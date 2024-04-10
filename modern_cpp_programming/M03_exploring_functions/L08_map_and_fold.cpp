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
//   range.
template <typename F, typename R>
R mapf(F&& func, R range)
{
    std::transform(std::begin(range), std::end(range), std::begin(range), 
        std::forward<F>(func));
    return range;
}
// - Generic function template that takes a function and an object as params,
//   then using the map created, insert the transformed value obtained
//   in the iteration of the elements after it applyed the function.
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
//   finally apply the function and add (push) the return to a new queue.
template<typename F, typename T>
std::queue<T> mapf(F&& func, std::queue<T> q)
{
    std::queue<T> r;
    while(!q.empty())
    {
        r.push(func(q.front()));
        q.pop();
    }
}


int main(int argc, char** argv)
{

}
