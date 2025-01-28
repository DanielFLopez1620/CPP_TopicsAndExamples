// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * As we mentioned in a previous lesson, you cannot use try/catch to manage
 * exceptions of a thread if it isn't part of the thread's context. The reason
 * is that they can abnornally terminate with a call of 'std::terminate()'.
 * 
 * However, exceptions can be transported between threads within an 
 * 'std::exception_ptr' wrapper, that is what we are going to check in this
 * lesson. 
 * 
 * 
 */

#include <thread>
#include <vector>
#include <mutex>

// Info #1: Create a global container to hold instances of a 
// 'std::exception_ptr'
std::vector<std::exception_ptr> thread_exceptions;

// Info #2: use a mutex (global) to synchronize acces to the shared container
std::mutex gmtx;

int main(int argc, char* argv[])
{
    
    return 0;
}