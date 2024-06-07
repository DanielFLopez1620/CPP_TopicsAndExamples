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

// --------------------- STRUCTU AND CLASSES DEFINITIONS -----------------------

// Info #1: Down below you can see the class implementations for three elements
// that can be related with inheritance a vehicle, a car and a sport car. In 
// the vehicle definition you will see the virtual implementations, those which
// aims to be overload in future classes. But you can also check for classes
// methods that cannot be overloaded by using final.

/**
 * Generic vehicle class, it refers to something that has a motor.
*/
class Vehicle
{
public:
    /**
     * Just display message of activation of motor.
    */
    virtual void motor_on() 
    {
        std::cout << "Engine was started..." << std::endl;
    }

    /**
     * Just display message of deactivation of motor.
    */
    virtual void motor_off() 
    {
        std::cout << "Engine was stopped..." << std::endl; 
    }

    /**
     * Print the generic sound of the motor.
    */
    virtual void sound_motor()
    {
        std::cout << "WRoom..." << std::endl;
    }

    /**
     * Print serial identification, cannot be overrided.
    */
    virtual void serial_num() final
    {
        std::cout << "The serial number is...." << std::endl;
    }

}; // class Vehicle

/**
 * Generic car, vehicle with a motor and four tires.
*/
class Car : public Vehicle
{
public:
    
    /**
     * Just display message of motor activation for car.
    */
    virtual void motor_on() override
    {
        std::cout << "Car motor was started..." << std::endl;
    }

    /**
     * Just display message of motor activation for car.
    */
    virtual void motor_off() override
    {
        std::cout << "Car motor was stopped..." << std::endl; 
    }

    /**
     * Override that change the sound of the motor.
    */
    virtual void sound_motor() override
    {
        std::cout << "WRoom WRoom..." << std::endl;
    }

}; // class Car

/**
 * Type of car faster and with more powerful motor.
*/
class SportCar : public Car
{
public:
    /**
     * Sport Car's engine sound
    */
    virtual void sound_motor() override
    {
        std::cout << "VROOOM....." << std::endl;
    }

}; // class SportCar

// ---------------------- MAIN IMPLEMENTATION ---------------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 7: Virtual Methods...\n" << std::endl;
    
    // Info #2: Explore the instance of the objects below to understand the
    // override of the inheritance methods.
    std::cout << "Vehicle object: " << std::endl;
    Vehicle my_vehicle {Vehicle()};
    my_vehicle.motor_on();
    my_vehicle.sound_motor();
    my_vehicle.motor_off();
    my_vehicle.serial_num();
    std::cout << std::endl << "Car object: " << std::endl;
    Car my_car {Car()};
    my_car.motor_on();
    my_car.sound_motor();
    my_car.motor_off();
    my_car.serial_num();
    std::cout << std::endl << "Sport Car object: " << std::endl;
    SportCar my_sport_car {SportCar()};
    my_sport_car.motor_on();
    my_sport_car.sound_motor();
    my_sport_car.motor_off();
    my_sport_car.serial_num();

    return 0;
}