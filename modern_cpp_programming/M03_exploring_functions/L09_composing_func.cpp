// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested  with g++ in C++17

#include <iostream>

/**
 * Pipelining is a form of composition, it was briefly mentioned in the last
 * example of the lesson 8 of this module. But that example wasn't a proper
 * composition, here our objective will be to compose functions in order to
 * create new compositions.
 * 
 * Do you remember composition in algebra? Well, it is kinda it, if we have
 * a function 'f' and a function 'h', the composition will be f(g(x)) with x as
 * the argument for the composition.
 * 
 * But you can also check that composition can be made with opertors, in
 * general, the composition can be represented with '.' or '*', and in C++
 * we can use the operator* to work.
 * 
 * Down below you can check three examples, you can test them with:
 * 
 *      g++ -std=c++17 09_composing_func.cpp -o comp.out
 *      ./comp.out
*/

// ---------------------------- REQUIRED DEPENDENCIES -------------------------
#include <string>    // Methdos and funcs for using string and char arrays.
#include <vector>    // For using variable size arrays
#include <algorithm> // Contains useful algorithms for general utilities
#include <numeric>   // For numeric operation and useful function related

// --------------------------- FUNCTION DEFINITIONS ---------------------------
// Info #1: A basic composition template is shown below:
/**
 * Composable function.
 * 
 * @param f External function to compose.
 * @param g Internal function to compose.
 * 
 * @return Result of the composition.
*/
template <typename F, typename G>
auto compose_t1(F&& f, G&& g)
{
    return [=](auto x){ return f(g(x)); };

} // compose t1

// Info #2: A composition template for variadic args (funcs) implementations:
/**
 * Variadic composition function.
 * 
 * @param f First function to apply.
 * @param r Rest of function to apply in a composable way.
 * 
 * @return Result of the composition.
*/
template <typename F, typename... R>
auto compose_t1(F&& f, R&&... r)
{
    return [=](auto x) { return f(compose_t1(r...)(x)); };

} // compose_t1 (variadic args)

/**
 * Map function, oriented to apply a function to all the elements of the
 * range, vector or list. Taking advantage of the transform fucntion.
 * 
 * @param func Function to apply to the elements.
 * @param range List or vector to considered
 * 
 * @return Range, list or vector after the transformation.
*/
template <typename F, typename R>
R mapf(F&& func, R range)
{
    std::transform(std::begin(range), std::end(range), std::begin(range), 
        std::forward<F>(func));
    return range;
} // mapf (ranges)

/**
 * Folding left function, in order to apply a function to a range of elements
 * to obtain only one by considering the function provided 
 * (reused from L08 from this module)
 * 
 * @param func Function to apply to the elements
 * @param range Vector or list to consider in the folding
 * @param init Value to initialize the operation or process
 * 
 * @return Accumulation or result of the folding.
*/
template <typename F, typename R, typename T>
const T fold_left(F&& func, R&& range, T init)
{
    return std::accumulate(
        std::begin(range), std::end(range), std::move(init), 
        std::forward<F>(func)
    );
} // fold_left (range)

// ---------------------------- MAIN IMPLEMENTATION ---------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 9: Function composition...\n" << std::endl;

    // Using first compose template for receiving a string that contains a 
    // number, so it convert it to float and then squares the value.
    auto str_float { "3.1416" };
    auto squared_str_float = compose_t1(
        [](float const n) { return n * n; },
        [](std::string const num_text) { return std::stof(num_text); }
    )(str_float);
    std::cout << "Original string: " << str_float << std::endl
              << "Squared result: " << squared_str_float << std::endl;

    // Using variadic compose template with higher order functions. So we can
    // achieve the sum of the doubled absolute values of the elements.
    auto vec_flt = std::vector<float>{-3.1416, 2.91, -1.41, 16.2};
    auto sum_vec = compose_t1(
        [](std::vector<float> const & num) {
            return fold_left(std::plus<>(), num, 0.0f); },
        [](std::vector<float> const & num) {
            return mapf([](float const i) { return i*2; }, num); },
        [](std::vector<float> const & num_text) {
            return mapf([](float const i) { return std::abs(i); }, num_text); }
        )(vec_flt);
    std::cout << std::endl << "Original floating values: ";
    for(float data : vec_flt)
    {
        std::cout << data << ", ";
    }
    std::cout << std::endl << "Sum of absolute values doubled: " << sum_vec 
              << std::endl;

    return 0;

} // main