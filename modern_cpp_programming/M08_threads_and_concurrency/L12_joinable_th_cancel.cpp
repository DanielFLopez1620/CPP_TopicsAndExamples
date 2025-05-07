// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * The std::thread class implemented since C++11 represents a single thread of
 * execution which allow multiple threads execution. But they depend on calling
 * the 'join' method to wait for the thread execution.
 * 
 * In C++20 the 'std::jthread' which stantds for joinable thread, this was
 * intended to call the join method when the object is destroyed and it is
 * still joinable. It also came with additional features like cancellation
 * wtih 'std::stop_source' and 'std::stop_token'.
 */

 #include <thread>
 #include <stop_token>

void th_func1(int i);
void th_func2(std::stop_token stop, float& num);

int main(int argc, char* argv[])
{
    // Info #1: You can implement a thread that automatically join if the
    // object goes out of scope with a joinable thread.
    std::cout << "Example of joinable thread:" << std::endl;
    std::jthread th1(th_func1, 16);

    // Info #2: If you require to cancel a thread (execution), you need to 
    // consider:
    // - Ensure that the function first parameter is a std::stop_token.
    // - Inside the thread function, check if the stop was requested.
    // - Use a joinable thread.
    float num = 1610;
    std::cout << "Example of stopping joinable thread:" << std::endl
              << "\tValue at beginning: " << num << std::endl;
    std::jthread th2(th_func2, std::ref(num));

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

    th2.request_stop();

    std::cout << "\tValue after stopping" << num <<std::endl;

    // Info #3: You can even implement the work of multiple joinable theads,
    // by considering the next:
    // - All the thread functions should implement the first arg as a stop.
    // - All the threads should check periodically for the stop request.
    // - All the theads have to be 'std::jthreads'.
    return 0;
}

void th_func1(int i)
{
    do
    {
        std::cout << "\tCurrent value of i: " << i << std::endl;
    } while (--i > 0);
}

void th_func2(std::stop_token stop, float& num)
{
    do
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        i++;
    } while (!stop.stop_requested() && num < 1619);
    
}