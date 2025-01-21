// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Why threading and concurrency? Because we can do it!
 * Well... answering in a more proper way, computers now contain multiple
 * processors or cores, then leveraging this allow us to unlock the real power
 * of our computers as we can avoid the mindset of sequential execution.
 * 
 * First, we have the threads, they are a sequence of instructions that can be
 * managed independently by a scheduler. It can be of two types:
 * 
 * - Software thread: Threads of execution that are managed by the OS.
 * - Hardware: Threads of execution at physical level, CPU or CPU core.
 * 
 * At this point we have to highlight differences between parallel and
 * concurrent. In the first one two tasks are executed at the same time in
 * different cores, while in the second one, the two task are executed in
 * small steps continously and intercaleted by considering time slicing
 * (short periods dedicated to one or another).
 * 
 * C++ provides the 'thread' class available in the header <thread>. Also,
 * there are additional utilities unde r the namespace 'std::this_thread'.
 * 
 */

#include <thread>
#include <chrono>
#include <iomanip>

inline void display_time_stamp();
void demo_func_no_args();
void demo_func_wt_args(int const n1, float const n2);
void demo_func_rf_args(std::string & msg);
void demo_thread_time();

int main(int argc, char* argv[])
{
    // Info #1: You can create threads by using the std::thread object with the
    // default constructor.
    std::thread df_thread;

    // Info #2: You can start the execution of a function on another thread by 
    // passing a function as an argument.
    std::thread fn_thread(demo_func_no_args);
    fn_thread.join();

    // Info #3: You can also pass a lambda to a thread to initialize it
    std::thread lb_thread(
        []()
        {
            std::cout << "Demo of a lambda inside a thread" << std::endl;
        }
    );
    lb_thread.join();

    // Info #4: IF you want to use a function with arguments to start a thread,
    // you can pass them to the thread
    int const n1 = 20;
    float const n2 = 1.6;
    std::thread fa_thread(demo_func_wt_args, n1, n2);
    fa_thread.join();

    // Info #5: On one hand, to wait for a thread to finish its execution, use
    // the 'join()' method, as it was presented along the others examples. On the
    // other hand, you have 'detach' which allow the thread to continue its 
    // execution independently of the curren thread (the process willnot be
    // followed by any thread)

    // Info #6: You can pass a rargment to a function of a thread as a reference
    // by using std::ref or std::cref (this last one is a constant reference)
    std::string msg = "My message";
    std::thread fr_thread(demo_func_rf_args, std::ref(msg));
    fr_thread.join();

    // Info #7: You can stop the execution of a thread during a specified
    // duration by considering 'std::this_thread::sleep_for()'
    std::thread tm_thread(demo_thread_time);
    tm_thread.join();

    return 0;
}

inline void display_time_stamp()
{
    auto now = std::chrono::system_clock::now();
    auto std_time = std::chrono::system_clock::to_time_t(now);
    auto local_time = std::localtime(&std_time);
    std::cout << std::put_time(local_time, "%c") << std::endl;
}

void demo_func_no_args()
{
    std::cout << "Demo of a function inside a thread" << std::endl;
}

void demo_func_wt_args(int const n1, float const n2)
{
    std::cout << "\tDemo of a function with args inside thread" << std::endl 
              << "\t\tThe result operation for ( " << n1 << " + " << n2
              << " is: " << n1 + n2 << std::endl;
}

void demo_func_rf_args(std::string & msg)
{
    std::cout << "\tDemo of a function with ref args inside thread" << std::endl
              << "\t\tMessage received: " << msg << std::endl;
}

void demo_thread_time()
{
    using namespace std::chrono;
    display_time_stamp();
    std::this_thread::sleep_for(5s);
    display_time_stamp();
}