// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

/**
 * STRUCTURE POINTERS: They must be declared linked to the structure (&) like
 * the conventional pointers. For accessing to attributes, you use the operator
 * '->', for example: 
 *      <pointer_str>-><attribute>
*/

typedef struct 
{
    int x;
    int y;
    int z;

} coordinate_t;


int main(int argc, char **argv)
{
    // Example 1: Usage of a structure pointer.
    printf("E1: Structure pointer:");
    coordinate_t bot_pos;
    coordinate_t* st_prt = &bot_pos;
    printf("\tPointer: %p\n", (void*)st_prt);

    // Example 2: Taking advantage of pointer.
    printf("\nE2: Dereference struct pointer\n");
    st_prt->x = 3;
    st_prt->y = 4;
    st_prt->z = 0;
    printf("\tCoordinate: %d, %d, %d\n", bot_pos.x, bot_pos.y, bot_pos.z);
    return 0;
}
