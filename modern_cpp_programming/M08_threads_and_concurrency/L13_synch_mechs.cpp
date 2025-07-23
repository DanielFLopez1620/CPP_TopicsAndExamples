// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Let's check other synchronization tools you can use:
 * 
 * First, we have the std::latch, which implements a counter to synchronize
 * threads, which implement the counter at initialization and can only be
 * decreased. There are other aspects you have to consider, like:
 * 
 * - A thread may decrease the value of the latch and it can do it multiple
 *   times.
 * - The thread can be blocked until the latch countdown reaches zero.
 * - Once the latch reaches zero, it will signal all the blocked threads.
 * 
 * The methods you need to consider are:
 * 
 * - 'count_down()' to decrement the counter by N positions (by default 1)
 *   and this is an atomic operation. AS a note, do not surpass the counter
 *   initial value or it will lead to undefined behaviors.
 * - 'try_wait()' boolean check to know if the latch value reaches zero.
 * - 'wait()' block the calling thread until the counter reaches zero.
 * - 'arrive_and_wait()' equivalent to call the 'count_down()' and
 *   'wait()'
 * 
 * Second, we have the std::barrier, which can is a std::latch with reset 
 * (reuse), so it can be used multiple times to perform the same task with
 * the threads. The reset is done automatically once the counter reaches zero
 * after the threads decrement is reached.
 * 
 * Another special aspect to consider of the barriers is that it has a
 * completion phase, which starts with a synchronization point and
 * ends with a completion step. So the procecess for the execution is done after
 * all the participants have arrived to the synchronization point:
 * 
 * 1. The completion function is invoked.
 * 2. All the threads blocked will be free.
 * 3. Reset occurs and the barrier cycle begins again.
 * 
 * It can invoke a participation or even a revoke from the barrier, this
 * by implementing 'arrive_and_wait()' and 'arrive_and_drop()' correspondently.
 * 
 * Finally, let's explore semaphores, but moslty the binary semaphore, which
 * stands for std::binary_semaphore, which stands for a 
 * std::counting_semaphore<N>.
 * 
 * It uses the next methods:
 * 
 * - 'acquire()' to decrement the internal counter by 1 if its greater than
 *   zero, otherwise it will block until it is available again.
 * - 'try_acquire()' similar to acquire but won't block if semaphore is not
 *   available, have a boolean return.
 * - 'try_acquire_for()' an acquire option that will block but implements
 *   a timeout to processes the action if it occurs. It has a validation
 *   boolean return.
 * - 'try_acquire_until()' similar to the previous one but will specify
 *   a time point to proceed.
 * - 'release' to increment the counter, so if its zero it will allow for a
 *   connection for a thread.
 * 
 * Now, explore the code, when ready, compile and run with:
 * 
 *      g++ -std=c++20 L13_synch_mechs.cpp -o synch_mech.out
 *      ./synch_mech.out
 */

// -------------------------- REQUIRED DEPENDENCIES --------------------------
#include <latch>      // Latch lib
#include <barrier>    // Barrier lib
#include <semaphore>  // Semaphore lib
#include <stop_token> // Implementation to check stop tokens with jthreads
#include <thread>     // Thread library for synch and concurrency
#include <vector>     // Dynamic generated arrays
#include <functional> // General purpose function implementations

// -------------------------- FUNCTION PROTOTYPES ----------------------------

int factor(int num, int fac);
void display(std::vector<int> const& data);

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char* argv[])
{
    using namespace std::chrono_literals;

    // Info #1: A latch waits until a certain number of events have ocurred 
    // before continuing, but it is only a one-time-use, for example, with a
    // rocket launch countdown where a certain number of engineers must press
    // the ready button before the launch starts.
    // More technical, it is a thread counter that will notify you when it
    // reaches zero. In the example below, five threads will create data and
    // the main thread will wait for them.
    
    // Latch counter
    int const jobs = 5;
    
    // Latch definition
    std::latch latch_wk(jobs);
    
    // Data for latch
    std::vector<int> latch_data(jobs);
    
    // Joinable threads for the process
    std::vector<std::jthread> lat_ths;

    // Loop that will use lambdas to assign task to the threads
    for (int i = 1; i <= jobs; ++i)
    {
        lat_ths.push_back(std::jthread([&latch_data, i, &latch_wk]
            {
                std::this_thread::sleep_for(2s);
                latch_data[i] = factor(i, 5);
                latch_wk.count_down();
            }
        ));
    }

    // Will wait to the threads to finish and notify when zero is reached
    latch_wk.wait();
    std::cout << "Using latches:" << std::endl;
    display(latch_data);
    
    // Info #2: It's a reusable version of a latch, will block threads at a
    // certain point until it reach it, then execute a function and later it
    // will reset the process

    // Elements to consider
    const auto games = {"Halo", "Fall Guys", "Fornite"};

    // No exception lambda to display certain element
    auto on_download = []() noexcept
    {
        static auto element = 
            "\t...completed\n"
            "\tIntalling...\n";
        std::cout << element;
        element = "\t...completed\n";
    };

    // Define barrier with its size and the function to execute on completion
    std::barrier barrier_wk(std::ssize(games), on_download);
    
    // Lambda function that will be executed on the threads
    auto for_game = [&](std::string name)
    {
        // First process
        std::cout << "\t " + name + " is available\n";
        barrier_wk.arrive_and_wait();

        // Second process
        std::cout << "\t " + name + " is installed\n";
        barrier_wk.arrive_and_wait();
    };

    std::cout << "Using barriers...." << std::endl 
              << "\tSearching" << std::endl;

    // Defining vector for threads and reserve the required space
    std::vector<std::jthread> barrier_ths;
    barrier_ths.reserve(std::size(games));

    // Add the content to the threads and wait for their execution
    for(auto const& g : games)
    {
        barrier_ths.emplace_back(for_game, std::string(g));
    }

    // Additionally sleep to avoid overlaping with next lesson
    std::this_thread::sleep_for(2s);

    // Info #3: A sempahore can be understood with the analogy of a parking
    // garage with 3 spacers, if there are 3 cars inside, new cars must
    // wait until one leaves. However, in this case we will implement the
    // binary sempahore which only grants one permit as the implemented below.
    
    // Sempahore definiton
    std::binary_semaphore semaphore_wk(1);
    
    // Work lamda definition
    auto printing_page = [&](const std::string& user, int pages)
    {
        for(int i = 1; i <= pages; ++i)
        {
            // Obtain semaphore and stop other processes
            semaphore_wk.acquire();

            // Do a certain action/work
            std::cout << "\t" << user << " is priting page " << i << "...\n";
            std::this_thread::sleep_for(500ms);
            std::cout << "\t" << user << " finished page" << std::endl;
            
            // Let semaphore to others
            semaphore_wk.release();

            // Add a delay to the thread
            std::this_thread::sleep_for(100ms);
        }
    };
    
    // Display results for semaphore
    std::cout << "Using semaphore (binary)..." << std::endl;
    std::jthread person_1_th([&] { printing_page("Dan", 5); });
    std::jthread person_2_th([&] { printing_page("Fel", 3); });

    return 0;
} // main()

// ------------------------ FUNCTION DEFINITIONS -----------------------------

/**
 * A simple function to ensure the multiplication of two given factors
 * 
 * @param int First factor
 * @param int Second factor
 * 
 * @return Product of the factos
 */
int factor(int num, int fac)
{
    return num * fac;
} // factor()

/**
 * Display function that shows all the elements of a given vector
 * by separating them with coma and a final escape line.
 * 
 * @param data Integer vector with data of interest.
 */
void display(std::vector<int> const& data)
{
    std::cout << "\t";
    for (auto const d : data)
    {
        std::cout << d << ", ";
    }
    std::cout << std::endl;
} // display()
