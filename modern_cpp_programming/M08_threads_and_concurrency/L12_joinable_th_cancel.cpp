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
 * 
 * This came as a fix to the C++11 threads, implementing changes like:
 * 
 * - Implementing a shared stop-state for requesting stop executiongs.
 * - Cooperative cancellation with tools like 'get_stop_source()', which returns
 *   std::stop_source objects related with the stop state; or 'get_stop_token()'
 *   which returns a std::stop_token which can be used for cancellation
 *   requests.
 * - The destructor calls the 'request_stop()' and 'join()'.
 * 
 * As you may note below, you can initiate a joinable threads as you would do
 * with a normal thread. However, the first argument possible may refer to a
 * 'std::stop_token()' to make possible the cooperative cancel scenarios. If
 * the first argument isn't this token, the token is passed to the function
 * and cat get retrieved with 'get_stop_token()'.
 * 
 * This stop token must be checked regularly with 'stop_requested()' boolean
 * member. Also, in the case of multiple stop takens are linked with the same
 * stop source, just the first one will be taken.
 * 
 * The process to request a stop is simple, you just need to use
 * 'request_stop()'. You can check if a 'std::stop_source' is associated witt
 * a stop-state by using 'stop_possible()'.
 * 
 * One last thing to mention is that if multiple 'std::stop_callbacks' are
 * called, the order of them when invoken is unspecified but they will be
 * executed synchronously.
 */

 #include <thread>
 #include <stop_token>

void th_func1(int i);
void th_func2(std::stop_token stop, float& num);
void th_func3(std::stop_token stop, float& value);
void th_func4(std::stop_token stop, float& info);

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
    float value1 = 16;
    float value2 = 10;
    std::stop_source stop_th;
    std::cout << "Example of multiple stops:" << std::endl;

    std::jthread th3(th_func3, stop_th.get_token(), std::ref(value1));
    std::jthread th4(th_func3, stop_th.get_token(), std::ref(value2));

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

    stop_th.request_stop();
    std::cout << "\tValue1: " << value1 << "\t\nValue2: " << value2
              << std::endl; 
    
    // Info #4: You can implement callbacks so you can implemnt executions
    // of certain pieces of code when you call a stop request in joinable
    // threads.
    float info = 1;

    std::cout << "Usage of canceletation callback" << std::endl;
    std::stop_source stop_src;
    std::stop_token token = stop_src.get_token();
    std::stop_callback callback(token,
        []{std::cout << "\tThis is the callback..." << std::endl; });

    std::jthread th5(th_func4, token, std::ref(info));
        
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);

    stop_src.request_stop();
    std::cout << "\tInfo value" << info << std::endl;

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
        num++;
    } while (!stop.stop_requested() && num < 1619);
    
}

void th_func3(std::stop_token stop, float& value)
{
    do
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        value++;
    } while(!stop.stop_requested() && value < 20);
    
}

void th_func4(std::stop_token stop, float& info)
{
    do
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(150ms);
        info++;
    } while (!stop.stop_requested() &&  info < 16);
    
}