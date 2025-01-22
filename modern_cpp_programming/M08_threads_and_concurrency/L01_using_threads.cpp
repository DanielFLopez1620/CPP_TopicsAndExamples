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
 * Keep in mind that 'std::thread' has several constructors:
 * 
 * - Default constructor: Create obj but do not start execution.
 * - Move constructor: Representation of another thread (no longer after that).
 * - Variable constructor: Allow passing a function and additional args by
 *   (or not) reference, or even using wrappers.
 * 
 * When using threads, avoid using type-return functions as it is ignored by
 * the thread, it is better to use a shared variable or a function argument
 * with pointers / references.
 * 
 * Also, if a function in a thread ends with an exception, that exception can't
 * be caught with 'try... catch' statement in the contest where the thread was
 * started, can lead to end with std::terminate (abnormally). Then, the exceptions
 * must be managed withing the executing thread, however they can be transported
 * across threads via std::exception_ptr.
 * 
 * A thead that started its execution is joinable and detachable, where the first
 * one implies blocking the execution of the current thread until the end, and
 * the second one aims for decoupling thread object form the thread execution.
 * After you call one of this, the thread becomes non-joinable and it can be
 * destroyed safely (You can check it with 'joinable()').
 * 
 * Each thread has also a unique identifier which can be obtained with
 * 'std::this_thread::get_id()'.
 * 
 * Finally, additional functionalities in the space of 'std::this_thread' are
 * 'yield()' to hint the scheduler to activate another thread, 'sleep_for' to
 * block the execution for at least the specified period of time (may be longer)
 * and 'sleep_until' to block the execution until at leat the specified time
 * point.
 * 
 * In future lessons you will learn more about threads and also the jthread
 * object that solves the inconvenience of calling explicitly the 'join()'
 * function.
 * 
 * When ready, you can compile and run this code with:
 * 
 *      g++ -std=c++17 L01_using_threads.cpp -o using_threads.out
 *      ./using_threads.out
 * 
 * 
 */

// ------------------------- REQUIRED LIBRARIES -------------------------------
#include <thread>  // To use threads for concurrency
#include <chrono>  // Time management with different precisions
#include <iomanip> // Input / Output Manipulators

// ------------------------- FUNCTION PROTOTYPES ------------------------------

inline void display_time_stamp();
void demo_func_no_args();
void demo_func_wt_args(int const n1, float const n2);
void demo_func_rf_args(std::string & msg);
void demo_thread_time();
void demo_thread_until();
void demo_thread_yield(std::chrono::seconds timeout);

// ---------------------------- MAIN IMPLEMENTATION ---------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 1: Using threads with C++\n" << std::endl
              << "Exploring threads objects: " << std::endl;


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
            std::cout << "\tDemo of a lambda inside a thread" << std::endl;
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
    std::cout << "\nThread that waits a specified time: " << std::endl;
    std::thread tm_thread(demo_thread_time);
    tm_thread.join();

    // Info #8: You can stop the execution of a thread until a specified moment
    // by using 'std::this_thread::sleep_until()'
    std::cout << "\tThread that waits until: " << std::endl;
    std::thread un_thread(demo_thread_until);
    un_thread.join();

    // Info #9: If the current thread can have a pause and provide the
    // opportunity to another thread, you can use 'std::this_thread::yield()'
    std::cout << "\tThread that can yield... (check code)" << std::endl;
    std::thread yi_thread(demo_thread_yield, std::chrono::seconds(1));
    yi_thread.join();
    display_time_stamp();

    return 0;

}  // main()

// ------------------------------ FUNCTION DEFINITIONS ------------------------

/**
 * Dipslay the current time launched by chrono considering the local format.
 */
inline void display_time_stamp()
{
    auto now = std::chrono::system_clock::now();
    auto std_time = std::chrono::system_clock::to_time_t(now);
    auto local_time = std::localtime(&std_time);
    std::cout << "\t\t" << std::put_time(local_time, "%c") << std::endl;
}

/**
 * Void function that prints a message, intended to use inside a thread.
 */
void demo_func_no_args()
{
    std::cout << "\tDemo of a function inside a thread" << std::endl;
} // demo_func_no_args()

/**
 * Void function with two const args oriented to test passing args
 * when using threads and executing a sum with them to print it with the
 * values.
 * 
 * @param n1 Constant integer
 * @param n2 Constant float
 */
void demo_func_wt_args(int const n1, float const n2)
{
    std::cout << "\tDemo of a function with args inside thread" << std::endl 
              << "\t\tThe result operation for ( " << n1 << " + " << n2
              << " is: " << n1 + n2 << std::endl;
} // demo_func_wt_args()

/**
 * Void function to print a message passed by reference to a thread.
 * 
 * @param msg Pointer to string message to display
 */
void demo_func_rf_args(std::string & msg)
{
    std::cout << "\tDemo of a function with ref args inside thread" << std::endl
              << "\t\tMessage received: " << msg << std::endl;
} // demo_func_rf_args()

/**
 * Function to stop the execution of a thread for a certain period of time
 */
void demo_thread_time()
{
    using namespace std::chrono;
    display_time_stamp();
    std::this_thread::sleep_for(5s);
    display_time_stamp();
} // demo_thread_time()

/**
 * Function to stop the execution of a thread until a time point is
 * reached.
 */
void demo_thread_until()
{
    using namespace std::chrono;
    display_time_stamp();
    std::this_thread::sleep_until(
        std::chrono::system_clock::now() + 2.5s);
    display_time_stamp();
} // demo_thread_until()

/**
 * Function that yields at some point to let other threads to enter
 * the execution block.
 * 
 * @param timeout Time to give for other threads execution
 */
void demo_thread_yield(std::chrono::seconds timeout)
{
    auto now = std::chrono::system_clock::now();
    auto limit = now + timeout;
    std::cout << "\t\tBefore yielding..." << std::endl;
    do
    {
        std::this_thread::yield();
    } while (std::chrono::system_clock::now() < limit);
    std::cout << "\t\tAfter yielding..." << std::endl;
    
} // demo_thread_yield()