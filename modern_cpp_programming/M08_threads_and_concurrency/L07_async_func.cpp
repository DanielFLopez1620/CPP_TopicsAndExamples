// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * As you briefly watched in th e previous lesson, you cna execute asynchronous
 * task. Then, you can expand this concept to functions by taking advantage
 * of std::asynch() and std::future().
 * 
 * As a reminder, do not forget to use the <future> header.
 * 
 * In this lesson, we will implement the variadic function template std::asynch
 * which has two overloads, one that specifies a launch policy as the first arg
 * and other that doesn't. The other arguments will refer to functions that
 * should be considered for the thread.
 * 
 * Here, the launch policy is defined with a scoped enumeration called 
 * std::launch which can have the "async (a new thread is launched to execute
 * the program asynchronously) or "deferred" (the task is executed on the
 * calling thread the first time the result is required) state. Additionally,
 * if you call both it will act as the default in a no deterministic way.
 * 
 * The usage of std::async results in a "future" object, which refers to the
 * shared state. So, if you need the result, you just call the "get()"
 * method on the obj. When using 'get' you block the current thread until
 * the result value or an exception appears. However, there would be cases
 * where you need to ensure the operation and it doesn't count with a
 * return, so you can use "wait()", or timed/constrained options like
 * "wait_for()" and "wait_until()".
 * 
 * When ready, check the code and compile it with:
 * 
 *      g++ -std=c++20 L07_async_func.cpp -o async.out
 *      ./async.out
 * 
 */

 // ------------------------- REQUIRED LIBRARIES ------------------------------
#include <future>  // For using future objects in async/defered operations
#include <mutex>   // Implementation of mutexes and locks
#include <chrono>  // For time management with different precisions

// ------------------------ FUNCTION PROTOTYPES -------------------------------

void say_it();
void say_it_again();
int do_math();
int do_math_again();

// ------------------------- GLOBAL DEFINITIONS -------------------------------

std::mutex glb_mtx;

// ------------------------- MAIN IMPLEMENTATION -----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 7: Executing functions asynchronously...\n"
              << std::endl;

    // Info #1: You can start a new trhead with a specific function by using
    // "std::asynch" with "std::launch::async" policy to ensure it as
    // asynchrounous.
    std::cout << "Let's make an async call..." << std::endl;
    auto async_call = std::async(std::launch::async, say_it);
    say_it_again();
    async_call.wait();
    std::cout << "\tAll done with the call..." << std::endl; 

    // Info #2: You can also have reutrn values by considering the get() method
    // with a object running asynchronously.
    std::cout << "Let's make an async call..." << std::endl;
    auto async_return = std::async(std::launch::async, do_math);
    auto res1 = do_math_again();
    auto res2 = async_return.get();
    std::cout << "\tAll done with the call..." << std::endl; 
    return 0;
} // main()

// ------------------------ FUNCTION DEFINITIONS ------------------------------

/**
 * Function that displays a message by considering the lock of a mutex to avoid
 * interruptions of the output stream..
 */
void say_it()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }

    std::lock_guard<std::mutex> lock(glb_mtx);
    std::cout << "\tSay it out loud!" << std::endl;
} // say_it()

/**
 * Function that displays a different message and considers the lock of a mutex
 * to avoid interruptions of the output stream.
 */
void say_it_again()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }

    std::lock_guard<std::mutex> lock(glb_mtx);
    std::cout << "\tSay it out LOUD again!" << std::endl;
} // say_it_again()

/**
 * Compute an operation.
 */
int do_math()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }

    return (16 + 20);
} // do_math()

/**
 * Compute a little more complex operation.
 */
int do_math_again()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }

    return (16 + 16 + 20 + 20);
} // do_math_again()