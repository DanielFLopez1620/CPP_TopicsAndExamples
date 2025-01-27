// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Although threads allow you to execute multiple functions in a concurrent way,
 * you may still need access to shared resources, which mus tbe synchronized so
 * only one thread at a tieme can read/write from/to the shared resource.
 * 
 * For this reason, mutexes and locks appeared, and C++ allows them by using
 * the <mutex> header.
 * 
 * A mutex is a synchronization primitive that allows protection against
 * simultaneous access to shared resources from different threads, in C++ it
 * can be:
 * 
 * - std::mutex: Most common mutex type, provides methods to acquiere and
 *   realese the mutex.
 * - std::timed_mutex: Provides two additional methods, like 'try_lock_for()'
 *   that attempt to acquire the mutex and returns it if the mutex is not made
 *   available during a set time and 'try_lock_until' which do the same until
 *   a time point is reached.
 * - std::recursive_mutex: It allows to be acquired multiple itmes form the
 *   thread withouth being blocked.
 * - std::recursive_timed_mutex: Combination of recursive and timed mutex.
 * - std::shared_timed_mutex: Implemented since C++14, aims to scenarios when
 *   multiple readers can access the same resource at the same time wihtout 
 *   causing memory leaks or data races (only one is allowed to write).
 * 
 * Let's highlight that in the second example when using multiple mutexes
 * we aren't block twice the process, but rather changing the wonership for
 * the mutexes and then making the locks. However, you should keep in mind
 * that are more lock options:
 * 
 * - std::lock_guard: It attempts to acquire the mutex at the time of its
 *   construction and realse it upon destruction.
 * - std::unique_lock: Provides support for deferred locking, time locking,
 *   recursive locking, transfer of ownership and using it with condition
 *   variables.
 * - std::shared_lock: Is a mutex-shared ownership wrapper that provides
 *   deferred locking, time locing and transfer of ownership.
 * - std::scope_lock: Is a wrapper for multiple mutexes that attempts to
 *   acquire ownership of the mutexes in a deadlock avoidance manner.
 * 
 * NOTE: When working with mutexes and locks, always consider cases to prevent
 * deadlocks.
 * 
 * When ready, you can compile and run this code with: 
 * 
 *      g++ -std=c++17 L02_mutexes_locks.cpp -o mutexes_locks.out
 *      ./mutexes_locks.out
 */

// --------------------------- REQUIRED LIBRARIES -----------------------------
#include <mutex>     // For using mutexes and locks
#include <thread>    // For concurrent program development
#include <chrono>    // Oriented to time management with different precisions
#include <vector>    // Dynamic arrays
#include <algorithm> // General purpose algorithms

// -------------------------- STRUCTS AND GLOBAL DEFINITIONS -----------------

// Info #1: You can create a mutex by creating a mutex object, which can be from
// the default constructor, you should consider the scope as it can be a class
// or global scope.
std::mutex glb_mtx;

// Info #2: You can define the mutex inside a class or structure, and it can be
// also on a class or just global context.
template <typename T>
struct dyn_container
{
    std::mutex st_mtx;
    std::vector<T> content;
};

// ------------------------- FUNCTION PROTOTYPES ------------------------------
void manage_resource_glb();

template <typename T>
void exchange_data(dyn_container<T>& box1, dyn_container<T>& box2, T const& val); 

// ------------------------ MAIN IMPLEMENTATION -------------------------------
int main(int argc, char* argv[])
{
    // Info # 3: You can use multiple threads to access the same resource.
    // However, you will need to lock th eaccess to avoid problems. This can
    // be achieved by using a global mutex.
    std::cout << "Example of global mutex: " << std::endl;
    std::thread t1(manage_resource_glb);
    std::thread t2(manage_resource_glb);
    std::thread t3(manage_resource_glb);
    std::thread t4(manage_resource_glb);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    // Info # 4: Example by using a structure with a mutex for thread safety so
    // mutiple mutex are locked when interacting with multiple resources.
    std::cout << "Example of struct with intern mutex: " << std::endl;
    dyn_container<int> box1;
    dyn_container<int> box2;
    box1.content = {12, 34, 56, 78};
    box2.content = {16, 62, 20, 1};
    std::cout << "\tContent of box #1: ";
    for (const auto& c : box1.content)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl << "\tContent of box #2: ";
    for (const auto & c: box2.content)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    std::cout << "\tContent of box #1 after exchange: ";
    exchange_data(box1, box2, 34);
    for (const auto& c : box1.content)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl << "\tContent of box #2 after exchange: ";
    for (const auto & c: box2.content)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}

// ------------------------ FUNCTION DEFINITIONS ------------------------------

/**
 * Function oriented to explore the usage of a lock by using a mutex with
 * a global context for synchronizing access with a single shared resource.
 */
void manage_resource_glb()
{
    // Lock (will finish after exiting the scope)
    using namespace std::chrono_literals;
    {
        std::lock_guard<std::mutex> lock(glb_mtx);
        std::cout << "\tRunning thread: " << std::this_thread::get_id()
                  << std::endl;
    }
    // Simulate a work that last 1 second
    std::this_thread::yield();
    std::this_thread::sleep_for(1s);
    
    // Lock again
    {
        std::lock_guard<std::mutex> lock(glb_mtx);
        std::cout << "\tFinished thread: " << std::this_thread::get_id()
                  << std::endl;
    }

} // manage_resource_glb()

/**
 * Exchange a given value present in one vector to another, by cosnidering a
 * thread safe application.
 * 
 * @param box1 First vector
 * @param box2 Second vector
 * @param val Value to exchange between arrays
 */
template <typename T>
void exchange_data(dyn_container<T>& box1, dyn_container<T>& box2, T const& val) 
{
    // Lock both mutexes without risk of deadlock using std::lock
    std::lock(box1.st_mtx, box2.st_mtx);

    // Now we adopt the locks so that they can be managed by lock_guard
    std::lock_guard<std::mutex> lg1(box1.st_mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lg2(box2.st_mtx, std::adopt_lock);

    // Remove the value from box1's content (if it exists)
    box1.content.erase(std::remove(box1.content.begin(), box1.content.end(), val), box1.content.end());

    // Add the value to box2's content
    box2.content.push_back(val);

} // exchange_data()