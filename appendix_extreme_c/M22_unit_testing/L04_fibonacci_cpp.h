// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#ifndef FIBONACCI
#define FIBONACCI

// Libraries needed

#include <stdint.h>
#include <unistd.h>

#if __cplusplus
extern "C"
{
#endif
// Function prototypes

int next_number();
int fibonacci(int);

#if __cplusplus
}
#endif

#endif