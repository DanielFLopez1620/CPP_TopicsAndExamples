// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Why threading and concurrency? Because we can do it!
 * Well... answering in a more proper way, computers now contain multiple
 * processors or cores, then leveraging this allow us to unlock the real power
 * of our computers as we can avoid the mindset of sequential execution.
 * 
 * First, we have the threads, they are a sequence of instructions that can be
 * managed independently by a scheduler. It can be of two types:
 * 
 * - Software thread: Threads of execution that are managed by the OS.
 * - Hardware: Threads of execution at physical level, CPU or CPU core.
 * 
 * At this point we have to highlight differences between parallel and
 * concurrent. In the first one two tasks are executed at the same time in
 * different cores, while in the second one, the two task are executed in
 * small steps continously and intercaleted by considering time slicing
 * (short periods dedicated to one or another).
 * 
 * C++ provides the 'thread' class available in the header <thread>. Also,
 * there are additional utilities unde r the namespace 'std::this_thread'.
 * 
 */

#include<thread>
#include <chrono>

inline void display_time_stamp();

int main(int argc, char* argv[])
{
    return 0;
}

inline void display_time_stamp()
{
    auto now = std::chrono::system_clock::now();
    auto std_time = std::chrono::system_clock::to_time_t(now);
    auto local_time = std::localtime(&std_time);
    std::cout << std::put_time(local_time, "%c") << std::endl;
}