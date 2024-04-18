// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested  with g++ in C++17

#include <iostream>

/**
 * Pipilining is a form of composition, it was briefly mentioned in the last
 * example of the lesson 8 of this module. But that example wasn't a proper
 * composition, here our objective will be to compose functions in order to
 * create new compositions.
 * 
 * Do you remember composition in algebra? Well, it is kinda it, if we have
 * a function 'f' and a function 'h', the composition will be f(g(x)) with x as
 * the argument for the composition.
*/

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>

// Info #1: A basic composition template is shown below:
template <typename F, typename G>
auto compose_t1(F&& f, G&& g)
{
    return [=](auto x){ return f(g(x)); };
}

// Info #2: A composition template for variadic args (funcs) implementations:
template <typename F, typename... R>
auto compose_t1(F&& f, R&&... r)
{
    return [=](auto x) { return f(compose_t1(std::forward<R>(r)...)(x)); };
}

template <typename F, typename R>
R mapf(F&& func, R range)
{
    std::transform(std::begin(range), std::end(range), std::begin(range), 
        std::forward<F>(func));
    return range;
}

template <typename F, typename R, typename T>
const T fold_left(F&& func, R&& range, T init)
{
    return std::accumulate(
        std::begin(range), std::end(range), std::move(init), 
        std::forward<F>(func)
    );
}


int main(int argc, char* argv[])
{
    // Using first compose template for receiving a string that contains a 
    // number, so it convert it to float and then squares the value.
    auto str_float { "3.1416" };
    auto squared_str_float = compose_t1(
        [](float const n) { return n * n; },
        [](std::string const num_text) { return std::stof(num_text); }
    )(str_float);
    std::cout << "Original string: " << str_float << std::endl
              << "Squared result: " << squared_str_float << std::endl;

    // Using variadic compose template
    auto vec_flt = std::vector<std::string>{"-3.1416", "2.91", "-1.41", "16.2"};
    auto sum_vec = compose_t1(
        [](std::vector<float> const & num) {
            return fold_left(std::plus<>(), num, 0.0f); },
        [](std::vector<float> const & num) {
            return mapf([](float const i) {return std::abs(i); }, num); },
        [](std::vector<std::string> const & num_text) {
            return mapf([](std::string const i) {return std::stof(i); }, num_text); })(vec_flt);
    std::cout << "Sum of absolute values: " << sum_vec << std::endl;

    return 0;
}