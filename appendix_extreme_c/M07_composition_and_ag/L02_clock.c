// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "L02_battery.h"

// This only works with the public interface of the battery

typedef struct 
{
    struct battery_t* battery;
    int ID;
} my_clock_t;

/**
 * Manually allocator for my_clock objects
 * 
 * @return The allocated address of the obj
*/
my_clock_t* my_clock_new()
{
    return (my_clock_t*) malloc(sizeof(my_clock_t));
}

/**
 *  Constructor for the class my_clock
 * 
 * @param my_clock The pointer to the my_clock you wanna construct
*/
void my_clock_ctor(my_clock_t* my_clock, int id)
{
    my_clock->battery = battery_new();
    battery_ctor(my_clock->battery);
    my_clock->ID = id;
}

/**
 *  Destructor for the class my_clock
 * 
 * @param my_clock The pointer to the my_clock you wanna destruct
*/
void my_clock_dtor(my_clock_t* my_clock)
{
    battery_dtor(my_clock->battery);
    free(my_clock->battery);
}

/**
 * Behavior function to get the battery of the my_clock.
 * 
 * @param my_clock Pointer to the my_clock object you want to check.
 * 
 * @return % of battery of the my_clock
*/
double my_clock_status(my_clock_t* my_clock)
{
    return battery_status(my_clock->battery);
}


/**
 * Behavior function to recharge the my_clock
 * 
 * @param my_clock Pointer to the my_clock object you want to check
*/
void my_clock_recharge(my_clock_t* my_clock)
{
    battery_recharge(my_clock->battery);
}

/**
 * Behavior function to get the current time
 * 
 * @param my_clock Pointer to the my_clock object you want to check
 * 
 * @ref Neuron, https://stackoverflow.com/questions/45914070/how-to-get-current-time-in-c-using-gettime
*/
void my_clock_give_time(my_clock_t* my_clock)
{
   time_t now = time(NULL) ;
   struct tm tm_now ;
   localtime_r(&now, &tm_now) ;
   char buff[100] ;
   strftime(buff, sizeof(buff), "%Y-%m-%d, time is %H:%M", &tm_now) ;
   printf("Time is '%s'\n", buff) ;
   battery_give_power(my_clock->battery);
   if(my_clock_status(my_clock) <= 0.0)
    {
        my_clock_recharge(my_clock);
    }
}



