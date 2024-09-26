// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * When an execution ends, you may like to have a clean up, writea  log or
 * do an end operation. You can achieve this with std::exit() and 
 * std::quick_exit() as they allow you to load an action before everything
 * finish.
 * 
 * The header you will need is: <cstdlib>
 * 
 * 
 */

#include <cstdlib>

void when_exitting_log();
void when_exitting_disp();
void when_quickexit_log();
void when_quickexit_disp();

int main(int argc, char* argv[])
{
    std::cout << "Lesson 11: Exit call of functions:\n" << std::endl
              << "IMPORTANT NOTE: Change the code to obtain different results"
              << std::endl;

    // Info: You can create calls with the std::atexit() and 
    // std::at_quick_exit() to call some actions when exiting the main program.
    // Comment the exit call and see what happen.
    std::atexit(when_exitting_log);
    std::atexit(when_exitting_disp);
    std::atexit([](){ std::cout << "Exit Lambda Log" << std::endl; });
    std::at_quick_exit(when_quickexit_log);
    std::at_quick_exit(when_quickexit_disp);
    std::atexit([](){ std::cout << "Quick exit Lambda Log" << std::endl; });

    return 0;
}

void when_exitting_log()
{
    std::cout << "Logging: std::atexit() called" << std::endl;
}

void when_exitting_disp()
{
    std::cout << "Displaying: Just finished program " << std::endl;
}

void when_quickexit_log()
{
    std::cout << "Logging: std::at_quick_exit() called" << std::endl;
}

void when_quickexit_disp()
{
    std::cout << "Displaying: Just finished program quickly" << std::endl;
}
