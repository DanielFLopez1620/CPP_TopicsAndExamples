// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// This only works with the public interface of the battery

typedef struct 
{
    struct battery_t* battery;
    int ID;
} clock_t;

/**
 * Manually allocator for clock objects
 * 
 * @return The allocated address of the obj
*/
clock_t* clock_new()
{
    return (clock_t*) malloc(sizeof(clock_t));
}

/**
 *  Constructor for the class clock
 * 
 * @param Clock The pointer to the clock you wanna construct
*/
void clock_ctor(clock_t* clock, int id)
{
    clock->battery = battery_new();
    battery_ctor(clock->battery);
    clock->ID = id;
}

/**
 *  Destructor for the class clock
 * 
 * @param Clock The pointer to the clock you wanna destruct
*/
void clock_dtor(clock_t* clock)
{
    battery_dtor(clock->battery);
    free(clock->battery);
}

/**
 * Behavior function to get the current time
 * 
 * @param clock Pointer to the clock object you want to check
 * 
 * @ref Neuron, https://stackoverflow.com/questions/45914070/how-to-get-current-time-in-c-using-gettime
*/
void clock_give_time(clock_t* clock)
{
   time_t now = time(NULL) ;
   struct tm tm_now ;
   localtime_r(&now, &tm_now) ;
   char buff[100] ;
   strftime(buff, sizeof(buff), "%Y-%m-%d, time is %H:%M", &tm_now) ;
   printf("Time is '%s'\n", buff) ;
}

/**
 * Behavior function to get the battery of the clock.
 * 
 * @param clock Pointer to the clock object you want to check.
 * 
 * @return % of battery of the clock
*/
double clock_status(clock_t* clock)
{
    return battery_status(clock->battery);
}


/**
 * Behavior function to recharge the clock
 * 
 * @param clock Pointer to the clock object you want to check
*/
void clock_recharge(clock_t* clock)
{
    battery_recharge(clock->battery);
}

