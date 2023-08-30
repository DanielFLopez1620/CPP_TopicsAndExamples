// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <stdio.h>

typedef enum
{
    ON,
    OFF
} state_t;

typedef struct
{
    double percentage;
    state_t status;
} battery_t;

/**
 * Manually allocator for battery objects
 * 
 * @return The allocated address of the obj
*/
battery_t* battery_new()
{
    return (battery_t*) malloc(sizeof(battery_t));
}

/**
 *  Constructor for the class battery
 * 
 * @param battery The pointer to the clock you wanna construct
*/
void battery_ctor (battery_t* battery)
{
    battery->status = OFF;
    battery->percentage = 0.3;
}

/**
 *  Destructor for the class battery
 * 
 * @param Clock The pointer to the battery you wanna destruct
*/
void battery_dtor (battery_t* battery) {}

/**
 * Behavior function to get the status of the battery
 * 
 * @param battery Pointer to the battery to check
 * 
 * @return Battery percentage which can give you info of the status
*/
double battery_status(battery_t* battery)
{
    printf("Battery is %s", (battery->status == ON ? "ON" : "OFF"));
    if(battery->percentage > 0)
        printf("Percentage is: %f", (battery->percentage*100));
    return battery->percentage;
}

/**
 * Behavior function for the battery to give energy to something.
 * 
 * @param battery Pointer to the battery you are using.
*/
void battery_give_power(battery_t* battery)
{
    battery->percentage -= 0.01;
    if(battery->percentage <= 0.0)
        battery->status = OFF;

}

/**
 * Behavior function for the battery to recharge.
 * 
 * @param battery Pointer to the battery you are using.
*/
void battery_recharge(battery_t* battery)
{
    if(battery->status == OFF)
        battery->status = ON;
    battery->percentage = 1.0;
}
