// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdint.h>

// Forward declaration
struct shared_counter_t;

// Method prototypes
struct shared_counter_t* shared_counter_new();
void shared_counter_delete(struct shared_counter_t*);

void shared_counter_ctor(struct shared_counter_t*, const char*);

void shared_counter_dtor(struct shared_counter_t*);

void shared_counter_setvalue(struct shared_counter_t*, __int32_t);

void shared_counter_setvalue_ifowner(struct shared_counter_t*, __int32_t);

__int32_t shared_counter_getvalue(struct shared_counter_t*);