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
 * - std::transform(ini, end , pos, func):
 *      For applying functions to the elements of the given array.
 * - std::forward(element):
 *      Pass the lvalue as lvalue or rvalue.
 * - std::plus<>():
 *      Function object to perform a effective addition on two instances
 * 
 * NOTE: If you do not know the difference, a vector is a dynamic array with
 * the abiltily to resize automatically (contiguous storage), while a list is 
 * double linked sequence (in non contiguous memory).
 * 
 * For running this code you can use:
 * 
 *      g++ -std=c++17 L08_map_and_fold.cpp -o mapfold.out
 *      ./mapfold.out
*/

// ----------------------- REQUIRED HEADERS -----------------------------------
#include <vector>    // Oriented to use variable-size arrays.
#include <list>      // To manage sequences stored in non contiguous memory.
#include <map>       // Pair elements that consist of a key and a value.
#include <array>     // For using arrays
#include <queue>     // For stack elements with pop and push operations
#include <string>    // Oriented to string and char arrays management
#include <algorithm> // For common implementations of functions
#include <cmath>     // Constants and math values
#include <numeric>   // For numerical functions

// ----------------------- FUNCTION DEFINITIONS -----------------------------

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
} // mapf (ranges)

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
        range_to_return.insert(func(element));
    }
    return range_to_return;
} // mapf (maps)

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
    return r;
} // mapf (queue)

// Info #2: Down below, you can find implementations of fold expressions.
// - Generic function template which takes a function, a range and an initial 
// value to implement an accumulation of the elements of the range (it uses 
// left folding).
template <typename F, typename R, typename T>
const T fold_left(F&& func, R&& range, T init)
{
    return std::accumulate(
        std::begin(range), std::end(range), std::move(init), 
        std::forward<F>(func)
    );
} // fold_left (ranges)

// - Generic function template which takes a function, a range and an initial
//   value to implement an accumulation of the elements of the range (it uses
//   right folding)
template <typename F, typename R, typename T>
constexpr T fold_right(F&& func, R&& range, T init)
{
    return std::accumulate(
        std::rbegin(range), std::rend(range), std::move(init), 
        std::forward<F>(func)
    );
} // fold_right (ranges)

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
} // fold_left (queues)

/**
 * Custom implementation to iterate through a queue or stack object
 * 
 * @param q Standard queue with the data to access
 * @param func Reference to function that will be used with the queue.
*/
template<typename F, typename T>
void for_each_queue(std::queue<T>& q, F&& func) {
    while (!q.empty()) {
        func(q.front());
        q.pop();
    }
} // for_each_queue

// -------------------------- MAIN IMPLEMENTATION -----------------------------

int main(int argc, char** argv)
{
    std::cout << "Lesson 8: Maps and folds with functions...\n" << std::endl;

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
    auto low_phonem = mapf(
        [](std::pair<std::string, std::string> const pair_ele)
        {
            return std::make_pair(mapf(tolower, pair_ele.first), 
                pair_ele.second);
        }, phonem);
    std::cout << "Original pairs: " ;
    std::for_each(phonem.begin(), phonem.end(), [](const auto& kvp)
    {
        std::cout << "( " << kvp.first << ", " << kvp.second << "), ";
    });
    std::cout << std::endl << "Converted pairs: ";
    std::for_each(low_phonem.begin(), low_phonem.end(), [](const auto& kvp)
    {
        std::cout << "( " << kvp.first << ", " << kvp.second << "), ";
    });
    std::cout << std::endl << std::endl;

    // Info #7: Using queues for determinating if a grade is approved or not
    // using maps.
    auto student_grades = std::queue<float>();
    student_grades.push(5.0);
    student_grades.push(2.6);
    student_grades.push(3.5);
    student_grades.push(4.0);
    student_grades.push(1.7);
    auto reviewed_grades = mapf([](int const i)
        {
            return i > 3.0 ? 'A' : 'D';
        }, student_grades);
    std::cout << "Student Grades: ";
    for_each_queue(student_grades, [](float grade) {
        std::cout << grade << ", ";
    });
    std::cout << std::endl << "Grades review: " ;
    for_each_queue(reviewed_grades, [](char review) {
        std::cout << review << ", ";
    });
    std::cout << std::endl << std::endl;

    // Info #8: Using fold expression to make sums of elements. Keep in mind
    // that the sum can also be achieved with std::plus<>().
    auto int_vec = std::vector<int>{16, 17, 18, 19};
    auto sum_int_vec = fold_left([](const int n1, const int n2) 
        {return n1 + n2; }, int_vec, 0); 
    std::cout << "Original vector of nums: " ;
    for (float num : list_nums)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << "Sum of values: " << sum_int_vec << std::endl;

    // Info #9: Using fold expression to concatenate strings. Similar to the
    // previous case, you can also use std::plus<>  but only when joining chars 
    // to create a string.
    auto chains = std::vector<std::string>{"This", "is", "Esparta", "!"};
    auto conca_ch = fold_right( [](std::string const & t1, 
        std::string const & t2 ) { return t1 + t2; } , chains, std::string{});
    std::cout << "Original words: " ;
    for (float num : list_nums)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << "Right Concatenation: " << conca_ch << std::endl;

    // Info #10: Using fold expressions with maps and pairs, to sum data stored
    // in the keys.
    auto data = std::map<char, int>{{'a', 3}, {'b', 5}, {'d', 2}};
    auto counter = fold_left([](int const freq, std::pair<char, int> const dict)
        { return freq + dict.second; }, data, 0);
    std::cout << std::endl << "Original pairs of data and their frequency: " ;
    std::for_each(phonem.begin(), phonem.end(), [](const auto& kvp)
    {
        std::cout << "( " << kvp.first << ", " << kvp.second << "), ";
    });
    std::cout << "\nThe num of data registered is: " << counter << std::endl;

    // Info #11: You can combine fold and map operations, to get a single 
    // result, but keep in mind the proper order. This process is also know as
    // pipelined.
    auto vec_flt = std::vector<float>{ -1.6, 1.7, -1.8, 1.9};
    auto comb_flt = fold_left(
        std::plus<>(), 
        mapf([](int const num) {return num*2;}, mapf(
        [](int const num) { return std::abs(num); }, vec_flt)), 0
    );
    std::cout << "Original float numbers: " ;
    for (float num : vec_flt)
    {
        std::cout << num << ", ";
    } 
    std::cout << std::endl << "Result fold and map expressions: " << comb_flt 
              << std::endl;

    return 0;

} // main

