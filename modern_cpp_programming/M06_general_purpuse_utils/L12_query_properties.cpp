// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Template metaprogramming enable to write and reuse generic code to work
 * with all types. But when combining implementations of POD, non POD and
 * custom types you may want to implement slightly different features.
 * 
 * In this context, type traits appear for meta-types that provide information
 * about other types, its library contains a long list for querying type 
 * properties (same type validations, checking whether type....) and type
 * transformations. So, in this lesson we are goint to explore further on them.
 * 
 * Type traits requiere the <type_traits> headers that was included in C++11.
 * 
 */

template <typename T,
          typename = typename std::enable_if_t<std::is_arithmetic_v<T> > >
T custom_division(T const t1, T const t2)
{
    return t1 / t2;
}

template <typename T>
struct pod_struct
{
    static_assert(std::is_pod_v<T> && std::is_trivial_v<T>,
        "This type isn't a POD!");
    T value;
};

template <typename T>
struct const_checker
{
    typedef typename std::conditional_t<std::is_const_v<T>, T,
        typename std::add_const_t<T>> const type;
    
    static_assert(
        std::is_const_v<const_checker<int>::const_type>);
    static_assert(
        std::is_const_v<const_checker<int const>::const_type>);
};

template <typename T>
auto negate(T arg)
{
    if constexpr (std::is_same_v<T, bool>)
        return !arg;
    else if constexpr (std::is_integral_v<T>)
        return -arg;
    else if constexpr (std::is_floating_point_v<T>)
        return -std::abs(arg);
    else
        return arg;
}