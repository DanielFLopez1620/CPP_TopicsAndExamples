// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++14

#include <iostream>
/*
 * If you didn't know, it is a common application in games and cartography, and
 * if someone tell you that you can write random numbers, it isn't true as
 * the algorithms used are determinist, then, it is a pseudo random
 * implementation.
 * If the numbers were really random, they couldn't be predictive, but it isn't
 * done here. Most of the cases, pseudo random num uses statistical
 * distributions, with the uniform one being one of the most common.
 * Most of the engines produces integer numbers on a uniform distribution, and
 * they implement the following methods:
 * 
 * - min(): Minimum value that can be produced with the generator.
 * - max(): Maximum value that can be produced.
 * - seed(): Initialization of the algorithm, not aplicable to 'random_devices'.
 * - operator(): Generate a new number according the distributions and limits.
 * - discard(): Discard a given psedo-random number.
 * - entropy(): Will return 0 for a determinitstic generator, and a nonzero for
 *   non-determinitics generator.
 * 
 * Some generators you can implement and use are:
 * 
 * - linear_congruential_engine: That follows the form x(i) = (A*x(i-1)+C)%M.
 * 
 * - mersenne_twister_engine: Follows the idea of W*(N-1)*R bits, as a bitset
 *   play to generate pseudo-random numbers from segments of bits.
 * 
 * - substract_with_carry_engine: Based on x(i) = (x(i-R)-(i-S)-cy(i-1))%M, 
 *   where cy can be one or zero according it is positive or negative.
 * 
 * And you can also find engine adapters (or wrappers):
 * 
 * - discard_block_engine: From every block of P numbers, keeps only R numbers
 *   and discard the rest.
 * 
 * - independent_bits_engine: A generator that produces numbers of different
 *   bits than the orginal.
 * 
 * - shuffle_order_engine: Produces K shuffled tables of numbers based on the
 *   base engine, so then they are replaced.
 * 
 * Selecting a random pseudo-generator, should be considered under 
 * your requirements for the case you are working, for example, linear-
 * congruential is a little slower that subsct with carry, but the last one
 * requires more memory. Also, mersenne twister can be slower one but can
 * provide the longest non repetitive sequence if initialized properly.
 * 
 * Finally, let's mention some distributions you can keep in mind: 
 * 
 * - Uniform: Which comes with uniform_int_distribution, 
 *   uniform_real_distribution.
 * 
 * - Bernoulli: Which comes with bernoull_distribution (bool), 
 *   binomial_distribution (int), negative_binomial_distribution (int),
 *   geometric_distribution (int).
 * 
 * - Poisson: With poisoon_distribution (int), exponential_distribution (real),
 *   weibull_distribution (real) and extrem_value_distribution (real).
 * 
 * - Normal: With normal_distribution (real), lognormal_distribution (real),
 *   chi_squared_distribution (real), cauchy_distribution (real), 
 *   fisher_f_distribution (Real), student_t_distribution (real).
 * 
 * - Sampling: That includes: discrete_distribution (integer),
 *   piecewise_constant_distribution (real) and piecewise_linear_distribution
 *   (real).
 * 
 * For running this code, you can execute:
 * 
 *      g++ -std=c++14 L03_pseudo_ranmdo.cpp -o pseudo.out
 *      ./pseudo.out
 */



#include <random>
#include <chrono>
#include <functional>
#include <map>
#include <iomanip>
#include <algorithm>

void gen_and_display(std::function<int(void)> , int const);

int main(int argc, char** argv)
{
    // INFO #1: Let's generate a pseudo random number, do not forget to include
    // the random library from C++. The generators use distributions, so you
    // will need to pick one.

    // Seeding a pseudo-random engine.
    std::random_device rand_dev{};

    // Using engine and initialize with a seed.
    auto gen = std::mt19937{ rand_dev() };

    // Use an available distribution to output the engine
    auto uniform_d = std::uniform_int_distribution<> {16, 1620};

    // Now, let's try the random generation:
    auto my_num = uniform_d(gen);
    for(int i = 0; i < 15; ++i)
    {
        my_num = uniform_d(gen);
        std::cout << "Num #: " << i << " is: " << my_num << std::endl;
    }
    
    // Info #2: Using mtgen for mersenne twister.
    std::random_device rand_dev2{};
    auto gen2 = std::mt19937 {rand_dev2()};
    auto uniform_d2 = std::uniform_int_distribution<> {1, 16};
    gen_and_display(
        [&gen2, &uniform_d2]() {return uniform_d2(gen2);}, 1000);

    return 0;
}

void gen_and_display(std::function<int(void)> generator,
                     int const iterations)
{
    auto storage = std::map<int, int>{};

    for(auto n=0; n < iterations; ++n)
    {
        ++storage[generator()];
    }

    auto max_non_rep = 
        std::max_element(std::begin(storage), std::end(storage),
        [](auto value1, auto value2) {return value1.second < value2.second; });

    for (auto i = max_non_rep->second / 200; i > 0; --i)
    {
        for (auto value : storage)
        {
            std::cout
                << std::fixed << std::setprecision(1) << std::setw(3)
                << (value.second / 200 >= 1 ? (char)219 : ' ');
        }
        std::cout << std::endl;
    }

    for (auto value : storage)
    {
        std::cout 
            << std::fixed << std::setprecision(1) << std::setw(3) << value.first;
    }

    std::cout << std::endl;
}