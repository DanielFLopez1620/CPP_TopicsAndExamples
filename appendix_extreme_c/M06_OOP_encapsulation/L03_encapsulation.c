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
 * 'attribute' and the type is know as 'class'. Other important considerations are that 'attributes' convey
 * 'values' and 'methods' convay 'behaviors'. Here, we will need to use the implicity as ANSI C doesn't
 * allow to write class, and for this we need to know:
 * 
 * - Usage of structures to keep the attributes (attribut structure).
 * - For behaviors we use 'behavior function' which are outside the attribute structure.
 * - Behavior functions must accept an structure pointer (for reading/modification purposes).
 * - Naming should relate with the class for behavior functions
 * - The file must have a declaration header which contains the behavior functions.
 * 
 * To see the previous advices in practices, check the file L03_c_object.h.
 * 
 * NOTE 1: Remember that with structs, you access to the attributes with dot '.'. If it is a pointer to a
 * structure, you use '->'.
 * 
 * NOTE 2: When we are talking about C++, methods are called 'member functions' and attributes are called
 * 'data members'
 *
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
    printf("E2: Encapsulation try with variables...");
    coordinate_t pos1, pos2;  // Object definition
    pos1.x = 1;
    pos2.x = 6;
    pos1.y = 2;
    pos2.y = 0;
    printf("Coordinate 1: %d,%d", pos1.x, pos1.y);
    printf("Coordinate 2: %d, %d", pos2.x, pos2.y);

    printf("E2");
    return 0;
}
