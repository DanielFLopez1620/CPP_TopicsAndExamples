// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef CLOCK_C_H
#define CLOCK_C_H

struct clock_t;

// Memory Allocator
struct clock_t* clock_new();

// Constructor
void clock_ctor(struct clock_t*);

// Destructor
void clock_dtor(struct clock_t*);

// Behavior functions
void clock_give_time(struct clock_t*);
double clock_status(struct clock_t*);
void clock_recharge(struct clock_t*);

#endif