// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * C++ doens't have an implementation for interfaces (pure virtual methods)
 * and it has problems with declaration of virtual methods. The usage is
 * intended with 'virtual' but it is used as optional, then let's check
 * implementations with 'override' and 'final' implemented in C++11 to create
 * virtual functions or classes.
 * 
 * Here we can check an example with three classes, oriented with vehicles and
 * cars, in case of a vehicle, we assume that a common characteristic is the 
 * motor, but it can be different according the vehicle, and the action related
 * with the start/stop/sound of the motor will be different. Then we can
 * use 'virtual' and 'override' to create overrided instances on the child
 * objects, but there are some methods that cannot be changed, in this case, 
 * printing or displaying the serial of the vehicle, them, we use 'final' to
 * prevent overrides.
 * 
 * Explore the code, and when you are ready, you can use:
 * 
 *      g++ -std=c++20 L07_virtual_methods.cpp -o virt.out
 *      ./virt.out
*/

class Vehicle
{
    virtual void motor_on() 
    {
        std::cout << "Engine was started..." << std::endl;
    }

    virtual void motor_off() 
    {
        std::cout << "Engine was stopped..." << std::endl; 
    }

    virtual void sound_motor()
    {
        std::cout << "WRoom..." << std::endl;
    }

    virtual void serial_num() final
    {
        std::cout << "The serial number is...." << std::endl;
    }
};

class Car : public Vehicle
{
    virtual void motor_on() override
    {
        std::cout << "Car motor was started..." << std::endl;
    }

    virtual void motor_off() override
    {
        std::cout << "Car motor was stopped..." << std::endl; 
    }

    virtual void sound_motor() override
    {
        std::cout << "WRoom WRoom..." << std::endl;
    }
};

class SportCar : public Car
{
    virtual void sound_motor() override
    {
        std::cout << "VROOOM....." << std::endl;
    }
};

int main(int argc, char* argv[])
{
    return 0;
}