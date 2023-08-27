// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int x;
    int y;
} simple_pos_t;

/**
 * Manually allocation for the simple pos type.
 * 
 *  @return Poiner to the given structure.
*/
simple_pos_t* simple_pos_malloc()
{
    return (simple_pos_t*) malloc(sizeof(simple_pos_t));
}

/**
 * Initialization with zeros of the simple pose type.
 * 
 * @param pos Pointer to the attribute structure.
*/
void pos_init(simple_pos_t* pos)
{
    pos->x = 0;
    pos->y = 0;
}

/**
 * Deallacotation of the object and deletion of the simple pose type.
 * 
 * @param pos Pointer to the attribute structure.
*/
void pos_des(simple_pos_t* pos)
{
    free(pos);
}

/**
 * Update the x pos (integer) for the current simple pose.
 * 
 * @param pos Pointer to the attribute structure.
 * @param x Integer position to update.
*/
int pos_update_x(simple_pos_t* pos, int x)
{
    pos->x = x;
}

/**
 * Update the x pos (integer) for the current simple pose.
 * 
 * @param pos Pointer to the attribute structure.
 * @param x Integer position to update.
*/
int pos_update_y(simple_pos_t* pos, int y)
{
    pos->y = y;
}

int __pos_val(simple_pos_t* pos, char l)
{
    if(l == 'x')
        return ( pos->x >= 0 ? 1 : 0);
    else if (l == 'y')
        return ( pos->y >= 0 ? 1 : 0);
}

void pos_print(simple_pos_t* pos)
{
    if(__pos_val(pos, 'x'))
        printf("\nPositive X: ");
    else
        printf("\nNegative X: ");
    printf("%d", pos->x);

    if(__pos_val(pos, 'y'))
        printf("\nPositive X: ");
    else
        printf("\nNegative X: ");
    printf("%d", pos->y);
}
