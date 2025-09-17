// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Another alternative for communication with threads can be the usage of 
 * a return value or an exception by considering 'std::promises'.abs
 * 
 * Before moving on, do not forget to import the <future> header as promises
 * and futures classes (that will be used in this lesson) are present in
 * this header.
 * 
 * A promise and a future are pairs for communication, it is a chat that
 * enables a thread to communicate with antoher using a shared state. 'promise'
 * is an asynchronous provider of the result and has an associated 'future'
 * whihc represents an asynchronous return object.
 * 
 * To implement this type of channel, you require first a promise (which
 * craete a shared state), then it can be read by the future associated.
 * 
 * For setting the result of a promise you can use 'set_value()',
 * 'set_value_at_thread_exit()', 'set_exception()' and
 * 'set_exception_at_thread_exit'. 
 * 
 * After you have set the promise, you can retrieve the future by using the
 * 'get_future()' method. This blocks the calling thread until the value from
 * the shared state is made available. However, the future class has other
 * implementation for block the thread untirl retrieving the resource:
 * 
 *      - 'wait()': Only results the available result.
 *      - 'wait_for()': Return the result if it is on time, otherwise it will
 *         return the value at the moment a timmer expires.
 *      - 'wait_until()': Similiar to for but instaed consider a time point.
 * 
 * Note that this process isn't complex and asynchronous. Howerver, there would
 * be times where you require to use 'std::asynch', which is a higher-level
 * uitlily that runs a function asyncrhonosly.
 * 
 * When ready, complie this code with:
 * 
 *      g++ -std=c++20 L06_promises_futures.cpp -o promises_futures.out
 *      /./promises_futures.out 
 */

// ------------------------- REQUIRED LIBRARIES -------------------------------

#include <future>  // For asynscrhornously executed task management
#include <thread>  // Related with concurrent development of task
#include <mutex>   // For implementing locks and mutex
#include <chrono>  // Library for time mangement with different precisions

// ------------------------ FUNCTION PROTOTYPES -------------------------------

void production_promise(std::promise<float>& prom);
void consume_future(std::future<float>& fut);

// ------------------------- GLOBAL DEFINITIONS ------------------------------
std::mutex glb_mtx;

// ------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 6: Using future and promises\n" << std::endl;

    // Info #5: In the calling thread, we are using 'get_future()' to get
    // the future associated with the promise.
    {
        std::promise<float> prom;
        std::thread th1(production_promise, std::ref(prom));

        std::future<float> fut = prom.get_future();
        std::thread th2(consume_future, std::ref(fut));

        th1.join();
        th2.join();
    }

    return 0;

} // main()

// --------------------------- FUNCTION DEFINITIONS ---------------------------

/**
 * Function that create a promise for a floating number
 * 
 * @param prom Reference value to promise
 */
void production_promise(std::promise<float>& prom)
{
    // Info #1: We are inside a thread function that will make a promise, that
    // is the reason why its only parameter is a std::promise.
    
    // Long task simulation
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5s);
    }

    // Info #2: You can use 'set_value' and 'set_exception' to set a result to
    // represent a value or exception.
    prom.set_value(16.20);

}  // production_promise()



/**
 * Function that consums asyncrhonously a given number once it is ready
 * 
 * @param fut Reference to float number of interest
 */
void consume_future(std::future<float>& fut)
{
    // Info #3: We are inside a thread function that will associate the future
    // with a premise available to the other thread function throug a param.

    // Info #4: Get current future value and use a mutex to lock the thread, in
    // order to print a message
    auto current = fut.get();
    std::lock_guard<std::mutex> lock(glb_mtx);
    std::cout << "Using value: " << current << std::endl;

} // consume_future()