// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef PLANT_C_H
#define PLANT_C_H

// Type Definitions
struct plant_t;
struct fruit_t;

// Memory allocator
struct plant_t* plant_new();

// Constructor
void plant_ctor(struct plant_t*, const int);

// Destructor
void plant_dtor(struct plant_t*);

// Behavior functions
void plant_appear_fruit(struct plant_t*, struct fruit_t*);
void plant_nutrient_fruit(struct plant_t*);
void plant_leave_fruit(struct plant_t*);

#endif