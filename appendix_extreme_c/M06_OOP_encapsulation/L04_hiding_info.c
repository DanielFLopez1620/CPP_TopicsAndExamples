// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>
#include <stdlib.h>

/**
 * In OOP you need to protect your data or secure it, so it isn't visible to other parts of the code. So,
 * there is only a 'public API' that allows to use the class without any consequeances in the
 * implementation of the class/structure. For achieving this in C, you will need to determine
 * what is public and what is private. Also, you will need to take advantage for the manually 
 * allocation and naming convention ( '__' as a prefix of private structures).
 * 
 * For compilation make sure to run:
 *    gcc -c L04_hiding_ex.c -o ex.o
 *    gcc -c L04_hiding.info.c -o main.o
 *    gcc main.o ex.o -o try.out
 *    ./try.out
*/

#include "L04_hiding_ex.h"

int main(int argc, char **argv)
{
    struct simple_pos_t* pos = simple_pos_malloc();

    pos_init(pos);

    pos_update_x(pos, 3);
    pos_update_y(pos, 1);

    pos_des(pos);

    return 0;
}
