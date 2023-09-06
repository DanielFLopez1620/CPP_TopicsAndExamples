// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef BIRD_T1_H
#define BIRD_T1_H

// Base declaration
struct bird_t;

// Memory allocator
struct bird_t* bird_new();


// Constructor
void bird_ctor(struct bird_t*,
               const char* /* species */,
               const char* /* diet */,
               unsigned int /* wingspan */,
               unsigned int /* beak type*/);

// Destructor
void bird_dtor(struct bird_t*);

// Behavior functions
unsigned int bird_get_wingspan(struct bird_t*);
unsigned int bird_get_beak_type(struct bird_t*);

#endif