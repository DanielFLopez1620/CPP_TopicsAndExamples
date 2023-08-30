// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef my_clock_C_H
#define my_clock_C_H

struct my_clock_t;

// Memory Allocator
struct my_clock_t* my_clock_new();

// Constructor
void my_clock_ctor(struct my_clock_t*);

// Destructor
void my_clock_dtor(struct my_clock_t*);

// Behavior functions
void my_clock_give_time(struct my_clock_t*);
double my_clock_status(struct my_clock_t*);
void my_clock_recharge(struct my_clock_t*);

#endif