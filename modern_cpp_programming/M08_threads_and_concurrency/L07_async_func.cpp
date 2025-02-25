// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * As you briefly watched in th e previous lesson, you cna execute asynchronous
 * task. Then, you can expand this concept to functions by taking advantage
 * of std::aynch() and std::future().
 * 
 * As a reminder, do not forget to use the <future> header.
 */

#include <future>
#include <mutex>
#include <chrono>

void say_it();
void say_it_again();
int do_math();
int do_math_again();

std::mutex glb_mtx;

int main(int argc, char* argv[])
{
    std::cout << "Lesson 7: Executing functions asynchronously...\n"
              << std::endl;

    

    return 0;
}

void say_it()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }

    std::lock_guard<std::mutex> lock(glb_mtx);
    std::cout << "\tSay it out loud!" << std::endl;
}

void say_it_again()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }

    std::lock_guard<std::mutex> lock(glb_mtx);
    std::cout << "Say it out LOUD again!" << std::endl;
}

int do_math()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }

    return (16 + 20);
}

int do_math_again()
{
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }

    return (16 + 16 + 20 + 20);
}