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
 */

#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

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
}