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
 * - You can even consider logical operators like 'fetch_add()', 'fetch_or()'
 *   and 'fetch_xor()' as member functions. Or go further with non-member
 *   functions like 'atomic_fetch_and()','atomic_fetch_and_explicit()', 
 *   'atomic_fetch_or()', 'atomic_fetch_or_explicit()', 'atomic_fetch_xor()'
 *   and 'atomic_fetch_xor_explicit()'.
 * - Another option is to use 'std:atomic_flag' with its members:
 *   'test_and_set()' and 'clear()'; or its non-members: 
 *   'atomic_flag_test_and_set()', 'atomic_flag_test_and_set_explicit()',
 *   'atomic_flag_clear()' and 'atomic_flag_clear_explicit()'. Additionally,
 *   with C++20 you have an additional member 'test()' and two non-members
 *   'atomic_flag_test()' and 'atomic_flag_test_explicit()'.
 * - There are also more add-on after C++20 to perform thread synchronization
 *   with members like 'wait()', 'notify_one()', 'notify_all()' that are
 *   available to 'std::atomic', 'std::atomic_ref' and 'std::atomic_flag',
 *   'atomic_wait()', 'atomic_wait_explicit()', 'atomic_notify_one()' and
 *   'atomic_notify_all()'.
 * 
 * But let's go again to the point, a 'std::atomic' is a class template that
 * defines an atomic type which behavior is well defined in order to avoid
 * conflicts when working with multiple threads without the need of a lock. 
 * Some of its specializations are:
 * 
 * - 'atomic_bool' which is a full boolean specialization.
 * - 'atomic_int', 'atomic_long', 'atomic_char' and 'atomic_wchar' for
 *   integral definitions.
 * - Partial specialization for pointer types.
 * - Full specialization for float, double and long doule after C++ 20.
 * - 'std::atomic<std::shared_ptr<U>>' and 'std::atomic<std::weak_ptr<U>>'
 *   for the corresponding pointers after C++20.
 * 
 * You should have in mind the members to perform atomic operations in a proper
 * way:
 * 
 * - 'load()': Load an return the value.
 * - 'store()': Save a non atomic-value inside the object.
 * - 'exchange()': Save a non-atomic value and return the previous value.
 * - 'operator=': Operator with the same effect as store.
 * - 'fetch_add()': To add a non_atomic argument to an atomic value stored
 *   previously.
 * - 'fetch_sub()': To subsctract a non-atomic argument to an atomic value
 *   stored previously.
 * - 'fetch_and()': Atomic AND oepration.
 * - 'fetch_or()': Atomic OR operation.
 * - 'fetch_xor()': Atomic XOR operation.
 * - The usage of operator++ and operator-- are atomicly implemented.
 * - You can also take advantage of operators +=, -=, &=, |=, ^=.
 * 
 * In the case of 'std::atomic<bool>' and std::atomic_flag, you also count with
 * the next options:
 * 
 * - 'test_and_set()': Set the value to true and return the previous one.
 * - 'clear()': To set the value to false.
 * - 'test()': After C++20 to return the value of the flag.
 * - ATOMIC_FLAG_INIT: Do not forget to set up the flag. However this macro
 *   was deprecated.
 * 
 * When talking about atomic types, you should also consider the memory order,
 * which refers to an option to overload 'std::atomic' and 'std::atomic_flag'
 * to specify how non-atomic memory accesses are to be ordered around atomic
 * operations, the default is called 'sequential consistency'. 
 * 
 * Following this, we have ordering types with 'std::memory_order' which
 * comes with a enumeration that is shown below:
 * 
 * - 'memory_order_relaxed': No synchronization or ordering constraints.
 * - 'memory_order_consume': Mostly compiler optimizations, focused on 
 *   avoiding read/write in the current thread with depedent values. So,
 *   it only writes to data-dependent variables present in other threads
 *   that release the same atomic variable visisble in the current thread.
 * - 'memory_order_release': No read/write operations and no reorder from
 *   this. All writes in the current thread are visible in other threads
 *   and writes that carry a dependency to the atomic value visible in
 *   that consume the same atomic.
 * - 'memory_order_acq_rel': Read/write operation is both an acquire operation
 *   and a release operation. All writes are visible before the modification in
 *   other threads, and the modification is visible in other threads that
 *   aquire the same atomic variable.
 * - 'memory_order_seq_cst': All the threads observe all the modifications in
 *   the same order.
 * 
 * Lastly, when considering references you cannot use 'std::atomic'. That is the
 * reason 'std::atomic_ref' is a handly solution after C++20. So you can manage
 * a non atomic elemetn with an atomic reference, just keep in mind that you
 * should avoid accessing to it without the atomic reference in other instances
 * once you have used it.
 * 
 * The 'std::atomic_ref' has specializations for any trivially-copyable type,
 * partial specialization for all pointers, specialization for integral types
 * (inclusing cstdint header types) and specializations for float, double and
 * long double types.
 * 
 * Additionally for a 'std::atomic_ref', it is not thread-safe to accss
 * to subobjects referenced. However, it is possible to modify the referenced
 * value through a const atomic reference type.
 * 
 * Once you are ready, you can compile and run this code with:
 * 
 *      g++ -std=c++20 L08_atomic_types.cpp -o atomic_t.out
 *      ./atomic_t.out
 * 
 * NOTE: C++20 also came with new members and non-members that are efficient
 * for thread synchronization like 'wait()', 'atomic_wait()',
 * 'atomic_wait_explicit()', 'atomic_flag_wait()', 'atomic_flag_wait()',
 * 'atomic_flag_wait_explicit()' which act to block a thread until a notification
 * of a change values arrived. Also, we have 'notify_one()',
 * 'atomic_notify_one()' and 'atomic_flag_notify_one()' for single cases of
 * notifcation with threads, and notify_all(),
 * 'atomic_notify_all()' and 'atomic_flag_notify_all()' to unblock all the
 * threads blocked in an aotmic waiting operation.
 * 
 * NOTE: What is sequential consistency? Well, it means that all the
 * instructions are executed in some order and all the write are visible
 * throught the system at the moment they are made.
 **/

 // -------------------------------- REQUIRED LIBRARIES -----------------------
#include <atomic>    // For atomic processes with variables
#include <thread>    // Related with concurrency implementations
#include <vector>    // Dynamic memory arrays
#include <cassert>   // Asssertions from C
#include <numeric>   // Additional numeric elements
#include <random>    // For pseudo-random operations
#include <algorithm> // Inclusion of general purpose algorithms

// ------------------------------ FUNCTION PROTOTYPES ------------------------

void counting(int &counter);
std::vector<float> call_generator();

// ------------------------------ MAIN IMPLEMENTATION ------------------------
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

} // main()

// --------------------------- FUNCTION DEFINTIONS ----------------------------

/**
 * Void function that implements a thread safe counter.
 * 
 * @param counter Integer value to consider for the counter.
 */
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

/**
 * Function that returns a vector of 100000 position of pseudo random
 * numbers.
 * 
 * @return Pseudo random floating array generated.
 */
std::vector<float> call_generator()
{
    std::random_device rd;
    auto generator = std::mt19937{ rd() };
    auto dis = std::uniform_real_distribution<>{ 16, 20 };
    std::vector<float> numbers(100000, 0);
    std::generate(std::begin(numbers), std::end(numbers), 
        [&dis, &generator] {return dis(generator); });

    return numbers;
}