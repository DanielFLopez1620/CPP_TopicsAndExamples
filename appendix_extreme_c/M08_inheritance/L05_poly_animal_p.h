// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef ANIMAL_P_P_H
#define ANIMAL_P_P_H

// Pointer to function that morphs
typedef void (*walk_func_t) (void*);

// Private definition
typedef struct
{
    char species[20];
    int num_legs;
    walk_func_t walk_func;
} animal_t;

#endif