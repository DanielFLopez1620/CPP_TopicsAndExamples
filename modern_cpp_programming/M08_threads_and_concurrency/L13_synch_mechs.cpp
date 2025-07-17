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
    // Info #1: Latches
    int const jobs = 5;
    std::latch latch_wk(jobs);
    std::vector<int> latch_data(jobs);
    std::vector<std::jthread> lat_ths;
    for (int i = 1; i <= jobs; ++i)
    {
        lat_ths.push_back(std::jthread([&latch_data, i, &latch_wk]
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(2s);
                latch_data[i] = factor(i, 5);
                latch_wk.count_down();
            }
        ));
    }
    latch_wk.wait();
    std::cout << "Using latches:" << std::endl;
    display(latch_data);
    
    // Info #2: Barriers
    const auto games = {"Halo", "Fall Guys", "Fornite"};

    auto on_download = []() noexcept
    {
        static auto element = 
            "\t...completed\n"
            "\tIntalling...\n";
        std::cout << element;
        element = "\t...completed\n";
    };

    std::barrier barrier_wk(std::ssize(games), on_download);
    
    auto for_game = [&](std::string name)
    {
        std::cout << "\t " + name + " is available\n";
        barrier_wk.arrive_and_wait();

        std::cout << "\t " + name + " is installed\n";
        barrier_wk.arrive_and_wait();
    };

    std::cout << "Using barriers...." << std::endl 
              << "\tSearching" << std::endl;
    std::vector<std::jthread> barrier_ths;
    barrier_ths.reserve(std::size(games));
    for(auto const& g : games)
    {
        barrier_ths.emplace_back(for_game, std::string(g));
    }

    // Semaphores 
    std::binary_semaphore semaphore_wk{0};
    auto printing_page = [&](const std::string& user, int pages)
    {
        for(int i = 1; i <= pages; ++i)
        {
            semaphore_wk.acquire();

            using namespace std::chrono_literals;

            std::cout << user << " is priting page " << i << "...\n";
            std::this_thread::sleep_for(500ms);

            std::cout << user << " finished page" << std::endl;
            semaphore_wk.release();
            std::this_thread::sleep_for(100ms);
        }
    };


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
