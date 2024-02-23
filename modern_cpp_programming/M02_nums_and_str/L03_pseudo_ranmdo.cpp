// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++11

#include <iostream>

// If you didn't know, it is a common application in games and cartography, and
// if someone tell you that you can write random numbers, it isn't true as
// the algorithms used are determinist, then, it is a pseudo random
// implementation.
// If the numbers were really random, they couldn't be predictive, but it isn't
// done here. Most of the cases, pseudo random num uses statistical
// distributions, with the uniform one being one of the most common.



#include <random>

int main(int argc, char** argv)
{
    // INFO #1: Let's generate a pseudo random number, do not forget to include
    // the random library from C++.

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
}