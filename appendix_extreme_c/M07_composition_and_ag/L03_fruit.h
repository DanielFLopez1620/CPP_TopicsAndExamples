// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef FRUIT_C_H
#define FRUIT_C_H



// Declaration
struct fruit_t;

// Memory Allocator
struct fruit_t* fruit_new();

// Constructor
void fruit_ctor(struct fruit_t*);

// Destructor
void fruit_dtor(struct fruit_t*);

// Behavior functions

void fruit_grow(struct fruit_t*);
void fruit_bye(struct fruit_t*);

#endif