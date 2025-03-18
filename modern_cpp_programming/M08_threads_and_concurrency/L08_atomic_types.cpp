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
 * Down below you can check about the usage of the atomic definition,
 * 'std::atomic_ref', 'std::atomic_flag'. 
 * 
 * However, there are more implementations, for example:
 * 
 * - Consider the case of the atomic type's members for 'load()',
 *   'store(), 'exchange()' or the non_member 'atomic_load()',
 *   'atomic_load_explicit()', 'atomic_store()', 'atomic_store_explicit()',
 *   'atomic_exchange()' and 'atomic_exchange_explicit()' so you can read,
 *    set or exchange the value of an atomic object.
 * 
 **/

#include <atomic>
#include <thread>
#include <vector>
#include <cassert>
#include <numeric>
#include <random>
#include <algorithm>

void counting(int &counter);
std::vector<float> call_generator();

int main(int argc, char* argv[])
{
    std::cout << "Lesson 8: Atomic types\n" << std::endl;
    
    // Info #1: 'std::atomic' is a class template that allows the creation of
    // objects that supports atomic operations like loading, storing, arithmetic
    // or bitwise operations.
    std::cout << "Using an atomic value: " << std::endl;

    // Usage of atomic value for the increment
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
    // Join threads
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

    // Info #3: You can use the 'std::atomic_flag' class for an atomic
    // boolean type. Do not forget to initialize it properly. Keep in mind
    // that this flags have two states set (true) or clear (false).
    std::cout << "Using atomic flag: " << std::endl;

    // Initialize flag
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    int counter = 0;
    std::cout << "\tInitial value: " << counter << std::endl;
    std::vector<std::thread> th_othercol;
    for (int i = 0; i < 10; ++i)
    {
        // Pass by reference so all the threads have access to lock and counter
        th_othercol.emplace_back([&]()
        {
            
            // Returns the previous flag and set flag to true
            // So... if the previous value is true, it refers to another thread
            // holding the lock. So when it frees the lock, the other one can
            // acquire it.
            while(lock.test_and_set(std::memory_order_acquire));
                // Critical section protected
                ++counter;
                // Unlock
                lock.clear(std::memory_order_release);
        });
    }
    // Join threads
    for (auto & th : th_othercol)
    {
        th.join();
    }
    std::cout << "\tFinal value: " << counter << std::endl;
    
    // Info #4: You can use 'fetch_add()', 'fetch_sub()', 'atomic_fech_add()',
    // 'atomic_fech_add_explicit()', 'atomic_fech_sub()', 
    // 'atomic_fech_sub_explicit()' to atomically add or substract a value from
    // an atomic object and returns its value before the operation.
    std::atomic<float> total {0};
    std::vector<float> nums = call_generator();
    size_t size = nums.size();
    std::vector<std::thread> more_ths;
    std::cout << "Using atomic fecht:" << std::endl;
    for(int i = 0; i < 10; ++i)
    {
        more_ths.emplace_back([&total, &nums]
            (size_t const start, size_t const end)
            {
                for(size_t j = start; j < end; ++j)
                {
                    std::atomic_fetch_add_explicit(
                        &total, nums[j], std::memory_order_acquire);
                        // Can also be implemented as:
                        // total.fetch_add(nums[j], std::memory_order_acquire);
                        
                    }
                }, i*(size/10), (i+1)*(size/10));
            }
    for (auto & th : more_ths)  
    {
        th.join();
    }
    std::cout << "\tFinal sum: " << total << std::endl;

    return 0;
}

void counting(int &counter)
{
    std::atomic_ref<int> at_counter { counter };
    std::vector<std::thread> ths;
    for(int i = 0; i < 10; ++i)
    {
        // Pass at counter by reference so all the threads share the resource
        ths.emplace_back([&at_counter]()
        {
            for(int i = 0; i < 10; ++i)
            {
                // Critical section, prevented by using atomic reference
                ++at_counter;
            }
        });
    }
    // Join threads
    for (auto & th : ths)
    {
        th.join();
    }
}

std::vector<float> call_generator()
   {
      std::random_device rd;
      auto generator = std::mt19937{ rd() };
      auto dis = std::uniform_real_distribution<>{ 16, 20 };
      std::vector<float> numbers(100000, 0);
      std::generate(std::begin(numbers), std::end(numbers), [&dis, &generator] {return dis(generator); });

      return numbers;
   }