// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef DOG_P_H
#define DOG_P_H

// Base declaration
struct dog_t;

// Memory allocator
struct dog_t* dog_new();

// Constructor
void dog_ctor(struct dog_t*);

// Destructor
void dog_dtor(struct dog_t*);

// Function behavior are inherited from the animal class.

#endif