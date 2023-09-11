// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef ANIMAL_P_H
#define ANIMAL_P_H

// Base type declaration
struct animal_t;

// Memory allocator
struct animal_t* animal_new();

// Constructor
void animal_ctor(struct animal_t*,
                 const char* /* species name*/,
                 int /* num legs*/);

// Destructor
void animal_dtor(struct animal_t*);


// Behavior functions
void animal_get_species(struct animal_t*, char*);
void animal_walk(struct animal_t*);

#endif