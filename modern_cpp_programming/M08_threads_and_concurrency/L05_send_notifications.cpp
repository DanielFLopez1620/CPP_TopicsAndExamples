// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * We have already checked out mutexes which are synchronization primitives that
 * can be used to protect access to shared data, but it isn't the only one.abs
 * 
 * The standard library also provides the condition variables that
 * enables threadsto signal others when a certain condition is achieved. So,
 * the threads can be blocked until a certain condition is achieved (or
 * a tiemout is completed, what happens first if you prefer so)
 * 
 * Here appear two types of threads, the thread-producing one and the
 * thread-consuming one, which are explored in the code below.
 * 
 * The first thing to do is to import the header for the condition variable
 * that is called <condition_variable>.
 * 
 * In this case we want to simulate with the sleep a long term producing thread
 * that will communicate with a consume thread at the moment the production
 * just ends. This is possible thanks to the condition variable that the
 * consuming thread waits for, which then remains blocked. This implies that:
 * 
 * - At least one thread is waiting on the condition variable to be notified.
 * - At least one thread is signaling the condition variable.
 * - The waiting thread must first acquire a lock on a mutex and pass it
 *   to the wait method of the condition variable.
 * - The thread that signals can notify just one or all using the condition
 *   variable.
 * 
 * Keep in mind, that there are two types of condition variables:
 *
 * - std::condition_variable: Associated with a std::unique_lock.
 * - std::condition_variable_any: General interpreation that works with lock()
 *   and unlock(), that can be used for interruptible waits.ADJ_OFFSET_SINGLESHOT
 * 
 * Also, there are two overloads for a condition variable:
 * 
 * - std::unique_lock<std::mutex> which causes the thread to remain blocked
 *   until the condition variable is signaled.
 * - An overload with a prediction, that can be used to avoid spurious wakeups.
 * 
 * NOTE: When using condition variables, spurious wakeups my ocurr and a thread
 * may be signaled even if nobady signal the condition variable. This tends to
 * happen in mutiprocessor systems and require loop tests for reviewing.
 * 
 * When ready, you can compile and run this code with:
 *  
 *      g++ -std=c++17 L05_send_notifications.cpp -o send_notification.out
 *      ./send_notification.out
 * 
 */

// ------------------ REQUIRED LIBRARIES --------------------------------------
#include <thread>              // For using concurrency
#include <condition_variable>  // Condition variables with mutexes and threads
#include <mutex>               // For generating locks in threads
#include <chrono>              // Time-related lib with different precisions

// ------------------- MAIN IMPLEMENTATION ------------------------------------
int main(int argc, char* argv[])
{
    // Info #1: You can define a condition variable as shown below:
    std::condition_variable cnvar;

    // Info #2: You still need mutexes to lock threads. In this case we will
    // use two, one for lock on and the other for synchronizing access to
    // the console.
    std::mutex cnvar_mtx;
    std::mutex io_mtx;

    // Info #3: Define the shared data
    float sh_info = 16.20;

    // Info #4: Our first case is to use a producing thread, which have to be
    // locked before we modify the data
    std::thread producing([&](){
        // Process
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(3s);
        }
        // Production
        {
            std::unique_lock lock(cnvar_mtx);
            sh_info = 20.16;
        }
        // Message
        {
            std::lock_guard(io_mtx);
            std::cout << "Change of data: " << sh_info << std::endl;
        }

        // Info #5: After the process, you can create the notification with
        // the condition variable
        cnvar.notify_one();
    });

    // Info #6: Now, we have the implemenation of the consuming thread
    std::thread consuming([&]()
    {
        // Wiating notification
        {
            std::unique_lock lock(cnvar_mtx);
            cnvar.wait(lock);
        }
        // Info #7: After receiving the notifcation, you can develop the next
        // scope.
        {
            std::lock_guard lock(io_mtx);
            std::cout << "Consume of data: " << sh_info << std::endl;
        }       
    });

    return 0;
} // main()