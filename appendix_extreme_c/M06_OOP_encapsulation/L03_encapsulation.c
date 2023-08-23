// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * ENCAPSULATION: Or in a easier way... when you group thinks that are related and separe them of
 * the world. It improves readability and helps to prevent struggles with variables.
 * 
 * For using encapsulation, prefer the explicit relationships so you (the programmer) and the program
 * get a better understanding of the situation. Also, remember that it can help to prevent error in
 * runtime, as in your OOP description you can find and report error in the explicit groups.
 * 
 * In C, you an use custom datatypes to encapsulate your data, the info inside the object is known as
 * 'attribute' and the type is know as 'class'. 
 * 
 * NOTE: Remember that with structs, you access to the attributes with dot '.'. If it is a pointer to a
 * structure, you use '->'.
 * 
 * //219
*/


// Custom type for example 2, as encapsulation showcase.
typedef struct 
{
    int x; // X position attribute
    int y; // Y position attribut
} coordinate_t;

int main(int argc, char **argv)
{
    // The most basic low level of encapsulation, which can be slow and meaningless.
    printf("E1: Not encapsulated variables...");
    int coor1_x = 1;
    int coor1_y = 2;
    int coor2_x = 6;
    int coor2_y = 0;
    printf("Coordinate 1: %d,%d", coor1_x, coor1_y);
    printf("Coordinate 2: %d, %d", coor2_x, coor2_y);

    // A better usage of encapsulation, with custom type.
    coordinate_t pos1, pos2;  // Object definition
    pos1.x = 1;
    pos2.x = 6;
    pos1.y = 2;
    pos2.y = 0;

    return 0;
}
