// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef BATTERY_C_H
#define BATTERY_C_H

struct battery_t;

// Memory Allocator
struct battery_t* battery_new();

// Constructor
void battery_ctor(struct battery_t*);

// Destructor
void battery_dtor(struct battery_t*);

// Behavior functions
double battery_status(struct battery_t*);
void battery_give_power(struct battery_t*);
void battery_recharge(struct battery_t*);

#endif
