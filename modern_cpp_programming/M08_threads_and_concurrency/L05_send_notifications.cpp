// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

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
#include <random>              // Pseudo-random number generation
#include <vector>              // Memory dynamic arrays
#include <array>               // Functions and methods with arrays
#include <queue>               // For using queues (last in, first out)
#include <atomic>              // For additional prevention of race conditions

// -------------------- FUNCTION PROTOTYPES -----------------------------------
// Functions used in the second example

void producer(int const id, std::mt19937& gen, 
    std::uniform_int_distribution<int>& dsleep,
        std::uniform_int_distribution<int>& dcode);

void consumer();

// --------------------- GLOBAL DEFINITIONS -----------------------------------
// Variables used in second example

std::mutex sec_lockprint;
std::mutex sec_lockqueue;
std::condition_variable sec_cv;
std::queue<int> sec_buffer;
std::atomic<bool> sec_done { false };

// ------------------- MAIN IMPLEMENTATION ------------------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 5: Sending notificiations between threads\n"
              << std::endl;
    
    // Info #1: You can define a condition variable as shown below:
    std::condition_variable cnvar;

    // Info #2: You still need mutexes to lock threads. In this case we will
    // use two, one for lock on and the other for synchronizing access to
    // the console.
    std::mutex cnvar_mtx;
    std::mutex io_mtx;

    // Info #3: Define the shared data
    float sh_info = 16.20;

    std::cout <<"Starting producing and consuming P1" << std::endl;

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
            std::lock_guard lock(io_mtx);
            std::cout << "\t[1° Producer] Change of data: " << sh_info 
                      << std::endl;
        }

        // Info #5: After the process, you can create the notification with
        // the condition variable
        cnvar.notify_one();
    });

    // Info #6: Now, we have the implemenation of the consuming thread
    std::thread consuming([&]()
    {
        // Waiting notification
        {
            std::unique_lock lock(cnvar_mtx);
            cnvar.wait(lock);
        }
        // Info #7: After receiving the notifcation, you can develop the next
        // scope.
        {
            std::lock_guard lock(io_mtx);
            std::cout << "\t[1° Consumer] Consume of data: " << sh_info 
                      << std::endl;
        }       
    });

    producing.join();
    consuming.join();


    std::cout <<"Finishing producing and consuming P1" << std::endl;

    // Info #8: Let's review an additional (and more complex example)
    auto seed = std::array<int, std::mt19937::state_size> {};
    std::random_device rnd_dev;

    std::generate(std::begin(seed), std::end(seed), std::ref(rnd_dev));

    std::seed_seq seq(std::begin(seed), std::end(seed));

    auto generator = std::mt19937{ seq };
    auto dsleep = std::uniform_int_distribution<> { 1, 6};
    auto dcode = std::uniform_int_distribution <> {160, 200};

    std::cout << "Starting production and consuming P2...." << std::endl;

    std::thread complexconsumer(consumer);

    std::vector <std::thread> complexproducing;
    
    for( int i = 0; i < 5; ++i)
    {
        complexproducing.emplace_back(
            producer,
            i + 1,
            std::ref(generator),
            std::ref(dsleep),
            std::ref(dcode));
    }

    for (auto & th : complexproducing)
    {
        th.join();
    }
    
    sec_done = true;

    sec_cv.notify_one();

    complexconsumer.join();
    std::cout << "Finishing producing and consuming P2..." << std::endl;

    return 0;
} // main()

// ---------------------------- FUNCTION DEFINITIONS --------------------------
void producer(int const id, std::mt19937& gen, 
    std::uniform_int_distribution<int>& dsleep,
        std::uniform_int_distribution<int>& dcode)
{
    for (int i = 0; i < 5; ++i)
    {
        // Simulate work (with multiple/variable duration due to iterations)
        std::this_thread::sleep_for(std::chrono::seconds(dsleep(gen)));

        // Generate data
        int value = id * 20 + dcode(gen);

        {
            std::unique_lock<std::mutex> locker(sec_lockprint);
            std::cout << "\t[2° producer]: " << value << std::endl;
        }

        // Notify the consumer
        {
            std::unique_lock<std::mutex> locker(sec_lockqueue);
            sec_buffer.push(value);
            sec_cv.notify_one();
        }

    }
}

void consumer()
{
    // Loop until end is signaled
    while(!sec_done || !sec_buffer.empty())
    {
        std::unique_lock<std::mutex> locker(sec_lockqueue);

        sec_cv.wait_for(
            locker,
            std::chrono::seconds(1),
            [&]() { return !sec_buffer.empty() || sec_done; });

        // Check queue and process pending task
        while(!sec_buffer.empty())
        {
            std::unique_lock<std::mutex> locker(sec_lockprint);
            std::cout << "\t[2° consumer]: " << sec_buffer.front() << std::endl;
            sec_buffer.pop();
        }

    }
}