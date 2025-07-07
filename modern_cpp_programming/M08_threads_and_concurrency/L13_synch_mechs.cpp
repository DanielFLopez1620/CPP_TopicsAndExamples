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
    std::vector<int> data(jobs);
    std::vector<std::jthread> ths;
    for (int i = 1; i <= jobs; ++i)
    {
        ths.push_back(std::jthread([&data, i, &latch_wk]
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(2s);
                data[i] = factor(i, 5);
                latch_wk.count_down();
            }
        ));
    }
    latch_wk.wait();
    std::cout << "Using latches:" << std::endl;
    display(data);
    
    // Info #2: Barriers

    return 0;
}

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
