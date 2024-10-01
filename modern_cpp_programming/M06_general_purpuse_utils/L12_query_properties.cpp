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
 * The type traits can provide info about the types, properties and realtions
 * (is_integer, is_airthmetic, is_array, is_enum, is_class, is_const,
 * is_trivial, is_standard_layout, is_construcitble, is_same... that can
 * return boolean responses in the member value) or modifiers (add_const, 
 * remove_const, add_pointer, remove_pointer, make_signed, make_unsigned...
 * that has a memeber type that provide a typedef.)
 * 
 * Both usages are illustrated below with enable_if, static_assert, const_type
 * and add_const.
 * 
 * Go and check out the example, modify and make experiments, when ready, you 
 * can execute and run: 
 * 
 *      g++ -std=c++20 L12_query_properties -o trait_query.out
 *      ./trait_query.out
 * 
 */

// ------------------------- STRUCT AND CLASS DEFINITIONS ---------------------

/**
 * Generic division that validates the type trait before it implements the
 * template.
 * 
 * @param t1 Num to divide.
 * @param t2 Num for divide.
 * 
 * @return Result of the division.
 */
template <typename T,
          typename = typename std::enable_if_t<std::is_arithmetic_v<T> > >
T custom_division(T const t1, T const t2)
{
    return t1 / t2;
} // custom_division()

/**
 * POD struct that validates if the attribute passed is POD
 */
template <typename T>
struct pod_struct
{
    static_assert(std::is_standard_layout_v<T> && std::is_trivial_v<T>,
        "This type isn't a POD!");
    T value;
}; // struct pod_struct

/**
 * Struct that checks that the passed specification is a constant to
 * allow the definition.
 */
template <typename T>
struct const_checker
{
    typedef typename std::conditional_t<std::is_const_v<T>, T,
        typename std::add_const_t<T>> const_type;
}; // struct const_checker


/**
 * Generic negation implementation that checks the type to make boolean, 
 * numerical or sign negation. If no type is correpond, then it returns
 * the same type.
 * 
 * @param arg Generic argument that can be negate.
 * template <typename T>
struct pod_struct
{
    static_assert(std::is_pod_v<T> && std::is_trivial_v<T>,
        "This type isn't a POD!");
    T value;
}; // struct pod_struct
 * @return Negate arg if allowed. 
 */
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
} // negate()

// ------------------------ MAIN IMPLEMENTATION -------------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 12: More about query properties in type traits\n"
              << std::endl;

    std::cout << "Checkpoint: Using type traits for division considrations."
              << std::endl;
    auto div1 = custom_division(20.0, 16.20);
    // auto div2 = custom_division("16", "20"); // Will indicate error

    std::cout << "Checkpoint: Using pod verification." << std::endl;
    pod_struct<int> pod1 {1620};
    // auto pod_struct<std::string> pod2 {"Dan"}; // Will launch error

    std::cout << "Checkpoint: Assertion for constant checker." << std::endl;
    static_assert(
        std::is_const_v<const_checker<int>::const_type>);
    static_assert(
        std::is_const_v<const_checker<int const>::const_type>);

    std::cout << "Checkpoint: Generic negations by using different templates."
              << std::endl;
    auto neg1 = negate(true);
    auto neg2 = negate(16);
    auto neg3 = negate(-20);

    return 0;
} // main()