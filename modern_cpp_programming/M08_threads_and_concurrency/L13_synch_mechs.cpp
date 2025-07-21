// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * 
 */

#include <latch>
#include <barrier>
#include <semaphore>
#include <stop_token>
#include <thread>
#include <vector>
#include <functional>

int factor(int num, int fac);
void display(std::vector<int> const& data);

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
    
    // Work lamnda definition
    auto printing_page = [&](const std::string& user, int pages)
    {
        for(int i = 1; i <= pages; ++i)
        {
            semaphore_wk.acquire();

            std::cout << "\t" << user << " is priting page " << i << "...\n";
            std::this_thread::sleep_for(500ms);

            std::cout << "\t" << user << " finished page" << std::endl;
            semaphore_wk.release();
            std::this_thread::sleep_for(100ms);
        }
    };
    
    std::cout << "Using semaphore (binary)..." << std::endl;
    std::jthread person_1_th([&] { printing_page("Dan", 5); });
    std::jthread person_2_th([&] { printing_page("Fel", 3); });

    return 0;
} // main()

int factor(int num, int fac)
{
    return num * fac;
}

void display(std::vector<int> const& data)
{
    std::cout << "\t";
    for (auto const d : data)
    {
        std::cout << d << ", ";
    }
    std::cout << std::endl;
}
