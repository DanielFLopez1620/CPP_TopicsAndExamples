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

    std::vector<int> barrier_data(jobs);
    int cycle = 1;
    std::stop_source st_src;
    
    std::barrier<std::function<void()>>
        barrier_wk(
            jobs,
            [&barrier_data, &cycle, &st_src]()
            {
                display(barrier_data);
                cycle++;
                if(cycle == 10)
                {
                    st_src.request_stop();
                }
            }
        );

    std::vector<std::jthread> bar_ths;
    for (int i = 1; i <= jobs; ++i)
    {
        bar_ths.push_back(std::jthread(
            [&cycle, &barrier_wk, &barrier_data](std::stop_token st_tk, int const i)
            {
                while (!st_tk.stop_requested())
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(250ms);

                    barrier_data[i] = factor(i, cycle);

                    barrier_wk.arrive_and_wait();
                }
            },
            i
        ));
    }

    for (auto& th : bar_ths)
    {
        th.join();
    }

    // Info #3: Counting sempahore.
    std::vector<int> sem_data;

    std::binary_semaphore bin_sem{0};

    std::vector < std::jthread> sem_ths;
    for (int i = 1; i <= jobs; ++i)
    {
        sem_ths.push_back(std::jthread([&sem_data, i, &bin_sem]
        {
            for(int j = 1; j < jobs + 1; j++)
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(250ms);
                int value = factor(i, j);
                
                bin_sem.acquire();
                sem_data.push_back(value);
                bin_sem.release();
            }
        }));
    }

    display(sem_data);

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
