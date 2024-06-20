// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

/**
 * As you see in the previous lesson, initializing properly a seed for random
 * number generation is a priority, for example, the case of Mersenne twister
 * that tends to repeat and ignore certain values.
 * 
 * A better result of pseudo-random generation can be achieved by initializing
 * properly all the bits before generating a num. So, check the code below and
 * watch the implementation.
 * 
 * If you ask, what is the problem with the initialization we made in the
 * previous, it that we only set one bit and the mt19937 has 624 32 bit ints, so
 * we need to set everyone.
 * 
 * You can compile this code with: 
 * 
 *      g++ -std=c++11 L04_init_bits_random.cpp -o init_pseudo.out
 *      ./init_pseudo.out
*/

// ---------------------- REQUIRED HEADERS ------------------------------------

#include <random>     // For random number generation facilities
#include <algorithm>  // A collection of functions for iterations and related
#include <array>      // For fixed-size arrays
#include <functional> // Related with functional objects

// --------------------- MAIN IMPLEMENTATION ----------------------------------
int main(int argc, char** argv)
{
    std::cout << "Lesson 4: Bit initialization for better pseudo random"
              << "generation...\n" << std::endl;

    // Info #1: Properly initializing a seed.
    std::random_device rand_dev;
    std::array<int, std::mt19937::state_size> seed_info{};
    std::generate(std::begin(seed_info), 
                  std::end(seed_info), 
                  std::ref(rand_dev));
    std::seed_seq sequence(std::begin(seed_info), std::end(seed_info));
    auto eng = std::mt19937{ sequence };
    auto distro = std::uniform_real_distribution<>{0, 0.5};

    // Simple test
    for(int i = 0; i < 15; ++i)
    {
        auto my_num = distro(eng);
        std::cout << "Num # " << i << " is: " << my_num << std::endl;
    }

    return 0;

} // main