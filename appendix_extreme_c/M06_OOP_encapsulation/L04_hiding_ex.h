// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef HIDING_TRY_C_H
#define HIDING_TRY_C_H

#include <unistd.h>

struct simple_pos_t;

struct simple_pos_t* simple_pos_malloc();

void pos_init(struct simple_pos_t*);
void pos_des(struct simple_pos_t*);

int pos_update_x(struct simple_pos_t*, int);
int pos_update_y(struct simple_pos_t*, int);

void pos_print(struct simple_pos_t*);

#endif