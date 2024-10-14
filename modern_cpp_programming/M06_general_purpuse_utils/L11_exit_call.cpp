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
 * Keep in mind that if the termination is done in an abnormal way via
 * std::terminate() and std::abort(), none of the exit methods will be called.
 * 
 * Also, all the functions used for exit handlers must not have parameters
 * and return void vlaues, and they aannot be unregistered once they were
 * registered.
 * 
 * std::atexit() and std::at_quick_exit() are thread-safe an can be called
 * simultaneously from different threads withouth incurring a race condicition.
 * 
 * If multiple handlers are registered, then they will be called in the reverse
 * order of registration. 
 * 
 * When you are ready, you can execute this code with:
 * 
 *      g++ -std=c++20 L11_exit_call.cpp -o exit.out
 *      ./exit.out
 * 
 */

// ------------------------- REQUIRED HEADERS ---------------------------------
#include <cstdlib>

// ------------------------- PROTOTYPES FUNCTIONS -----------------------------
void when_exitting_log();
void when_exitting_disp();
void when_quickexit_log();
void when_quickexit_disp();

// ------------------------- MAIN IMPLEMENTATION ------------------------------
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

} // main()

// ------------------------- FUNCTION DEFINITIONS -----------------------------

/**
 * Logging exitting function oriented to use with std::atexit()
 */
void when_exitting_log()
{
    std::cout << "Logging: std::atexit() called" << std::endl;
}

/**
 * Display message function oriented to use with std::atexit()
 */
void when_exitting_disp()
{
    std::cout << "Displaying: Just finished program " << std::endl;
}

/**
 * logging exitting function oriented to use with std::at_quick_exit() 
 */
void when_quickexit_log()
{
    std::cout << "Logging: std::at_quick_exit() called" << std::endl;
}

/**
 * Display message function oriented to use with std::at_quick_exit()
 */
void when_quickexit_disp()
{
    std::cout << "Displaying: Just finished program quickly" << std::endl;
}
