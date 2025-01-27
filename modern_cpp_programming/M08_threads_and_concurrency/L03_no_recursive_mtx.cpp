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
 * 
 * 
 */

#include <mutex>

class obj_with_recmtx
{
    std::recursive_mutex recmtx;
    float value;

public:
    obj_with_recmtx(float const num = 0) : value(num) {}

    void set_value(float const num)
    {
        std::lock_guard<std::recursive_mutex> lock(recmtx);
        value = num;
    }

    float set_and_return_value(float const num)
    {
        std::lock_guard<std::recursive_mutex> lock(recmtx);
        auto temp = value;
        set_value(num);
        return temp;
    }
};

class obj_without_recmtx
{
    std::mutex mtx;
    float value;

private:
    void set_value(int const num)
    {
        value = num;
    }
};

int main(int argc, char* argv[])
{
    return 0;
}