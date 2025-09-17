// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * 'std::recursive_mutex' and 'std::recursive_timed_mutex' allow protection
 * in the case of access to shared resources, and therefore also mutiple
 * locks. However, if the number of 'unlock()' calls  is less than the
 * 'locks()' calls, it will be still locked. What is the problem? This create
 * a deadlock and create a greater overhead that non-recursive mutexes.
 * 
 * Do not forget to check the class implementation as this code doesn't really
 * do anything. It will just display a reminder to check the implementation
 * 
 *      g++ --std=c++17 L03_no_recursive_mtx.cpp -o no_recursive_mtx.out
 *      ./no_recursive_mtx.out
 * 
 */

#include <mutex>

// Info #1: Bad usage of recursive mutex that may lead to deadlocks in the
// implementation.

/**
 * Object that stores a float and allow setting the value by using recursive
 * mutexes and locks, also counts with an option to return the previous value
 * during a set.
 */
class obj_with_recmtx
{
    std::recursive_mutex recmtx;  // Recursive mutex 
    float value;                  // Floating number

public:
    obj_with_recmtx(float const num = 0) : value(num) {}

    /**
     * Setter of value, considering recursive mutex
     * 
     * @param num Value to update
     */
    void set_value(float const num)
    {
        std::lock_guard<std::recursive_mutex> lock(recmtx);
        value = num;
    }

    /**
     * Setter of the value with the option to return the previous value, by
     * also making a lock with a recursive mutex.
     * 
     * @param num Value to update
     * 
     * @return Previous float to set up
     */
    float set_and_return_value(float const num)
    {
        std::lock_guard<std::recursive_mutex> lock(recmtx);
        auto temp = value;
        set_value(num);
        return temp;
    }
};

// Info #2: Changes made to the previous class in order to avoid recursive
// mutex usage.

/**
 * Object that stores a float and allow setting the value by using a standard
 * mutex and locks, also counts with an option to return the previous value
 * during a set.
 */
class obj_without_recmtx
{
    std::mutex mtx;  // Std mutex
    float value;     // Floating value
 
    /**
     * Setter of value
     * 
     * @param Value to update
     */
    void set_value(int const num)
    {
        value = num;
    }

public:
    obj_without_recmtx(int const num = 0) : value(num) {}

    /**
     * Public setter to prevent usage of recursive mutex.
     * 
     * @param num Value to update
     */
    void use_set_value(int const num)
    {
        std::lock_guard<std::mutex> lock(mtx);
        set_value(num);
    }

    /**
     * Setter of the value with the option to return the previous value,
     * it considers call to base setter.
     * 
     * @param num Value to update
     * 
     * @return Previous float to set up
     */
    float set_and_return_value (int const num = 0)
    {
        std::lock_guard<std::mutex> lock(mtx);
        auto temp = value;
        set_value(num);
        return temp;
    }
};

int main(int argc, char* argv[])
{
    std::cout << "Lesson 3: Avoiding usage of recursive mutexes:\n" << std::endl
              << "\tCheck code for class implementation." << std::endl;

    return 0;
}