// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * As we mentioned in a previous lesson, you cannot use try/catch to manage
 * exceptions of a thread if it isn't part of the thread's context. The reason
 * is that they can abnornally terminate with a call of 'std::terminate()'.
 * 
 * However, exceptions can be transported between threads within an 
 * 'std::exception_ptr' wrapper, that is what we are going to check in this
 * lesson. 
 * 
 * Here we will illustrate the concept with multiple threads by considering a
 * vector of exception pointers. However, if you only have one thread, you do
 * not need only one container.
 * 
 * We are using 'std::current_exception()' which is a funtion that is typically
 * used in the catch clause to capture the current exception and create a 
 * instance of a 'std::exception_ptr'. This then creates a copy or reference to
 * the original exception that remains valid, then if no exception is being 
 * handled, then creates an empty 'std::exception_ptr'.
 * 
 * But what is a std::exception_ptr? Well, it is just a wrapper for an exception
 * and it can be passed to other threads to be rethrouwn and caught in a 
 * 'try... catch', for example, with 'std::rethrown exception'. These functions
 * are all available since C++11. 
 * 
 */

// ------------------------- REQUIRED LIBRARIES -------------------------------
#include <thread>  // Thread library implementation
#include <vector>  // For dynamic array
#include <mutex>   // For mutexes and locks implementation

// ------------------------- GLOBAL DEFINITIONS -------------------------------

// Info #1: Create a global container to hold instances of a 
// 'std::exception_ptr'
std::vector<std::exception_ptr> thread_exceptions;

// Info #2: use a mutex (global) to synchronize acces to the shared container
std::mutex gmtx;

// ------------------------ FUNCTION PROTOTYPES -------------------------------
void launch_exception_1();
void launch_exception_2();
void thread_exc_1();
void thread_exc_2();

// ------------------------- MAIN IMPLEMENTATION ------------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesosn 4: Handling exceptions in threads\n" << std::endl;
    
    // Info #3: Clear the container from the main thread
    thread_exceptions.clear();

    // Info #4: Execute the threads with functions that contain exception throw
    // commands, check the implementations below.
    std::thread th1(thread_exc_1);
    std::thread th2(thread_exc_2);
    th1.join();
    th2.join();

    // Info #5: With the vector of thread exception, we check each element and
    // dispaly the exceptions thrown.
    std::cout << "Listing exceptions during thread execution:" << std::endl;
    for (auto const & excp : thread_exceptions)
    {
        try
        {
            if (excp != nullptr)
            {
                std::rethrow_exception(excp);
            }
        }
        catch(const std::exception& ex)
        {
            std::cerr << "\t" << ex.what() << std::endl;
        }
    }
    return 0;
} // main()

// ------------------------- FUNCTION DEFINITIONS -----------------------------

/**
 * Generic function that throw an exception
 * 
 * @throw Custom runtime error.
 */
void launch_exception_1()
{
    throw std::runtime_error("My runtime error 1...");
} // launch_exception_1()

/**
 * Generic function that throw another exception
 * 
 * @throw Custom runtime error.
 */
void launch_exception_2()
{
    throw std::runtime_error("My runtime error 2...");
} // launch_exception_2()

/**
 * Function to pass the exception when using try except with
 * threads to check an exception.
 * 
 * @throw Custom runtime error
 */
void thread_exc_1()
{
    try
    {
        launch_exception_1();
    }
    catch(...)
    {
        std::lock_guard<std::mutex> lock(gmtx);
        thread_exceptions.push_back(std::current_exception());
    }
} // thread_exc_1()

/**
 * Function to pass the exception when using try except with
 * threads to check another exception.
 * 
 * @throw Custom runtime error
 */
void thread_exc_2()
{
    try
    {
        launch_exception_2();
    }
    catch(...)
    {
        std::lock_guard<std::mutex> lock(gmtx);
        thread_exceptions.push_back(std::current_exception());
    }
} // thread_exc_2()