// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Atomic? Is this chemistry? No, we are refering to process or task
 * that must execute in a non-interrupted way. Why is this important? Because
 * we are working with thread and using synchronize access to shared data
 * with mutexes, locks, latches, barries and semaphores, and we still may
 * neeed indivisible operations that can be executed concurrently that
 * require to avoid race conditions withouth the usage of locks.
 * 
 * For this lesson we will use the <atomic> header.
 * 
 * 
 **/

#include <atomic>
#include <thread>
#include <vector>

void counting(int &counter);

int main(int argc, char* argv[])
{
    std::cout << "Lesson 8: Atomic types\n" << std::endl;
    
    // Info #1: 'std::atomic' is a class template that allows the creation of
    // objects that supports atomic operations like loading, storing, arithmetic
    // or bitwise operations.
    std::cout << "Using an atomic value: " << std::endl;
    std::atomic<int> at_num { 16 };
    std::cout << "\tStart value: " << at_num << std::endl;
    std::vector<std::thread> th_collection;
    for(int i = 10; i > 1; --i)
    {
        th_collection.emplace_back([&at_num]()
        {
            for(int i = 0; i < 10; ++i)
            {
                --at_num;
            }
        });
    }
    for(auto & th : th_collection)
    {
        th.join();
    }
    std::cout << "\tAEnding value: " << at_num << std::endl;
    
    // Info #2: After C++20 you can use std::atomic_ref to apply
    // atomic operations to the referenced objects, which can
    // be a reference or a pointer to known types. Check the
    // function definition for more information.
    int my_value = 20;
    std::cout << "Using atomic ref: " << std::endl
              << "\tInitial value: " << my_value << std::endl;
    counting(my_value);
    std::cout << "\tFinal value: " << my_value << std::endl;

    return 0;
}

void counting(int &counter)
{
    std::atomic_ref<int> at_counter { counter };
    std::vector<std::thread> ths;
    for(int i = 0; i < 10; ++i)
    {
        ths.emplace_back([&at_counter]()
        {
            for(int i = 0; i < 10; ++i)
            {
                ++at_counter;
            }
        });
    }
    for (auto & th : ths)
    {
        th.join();
    }
}