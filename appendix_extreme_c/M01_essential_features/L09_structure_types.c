// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

/**
 * ALIASES FOR STRUCTURES: In order to improve the structure, you can create type of 
 * structures by adding 'typedef' at the beginning and the name of the type at last.
 * 
 * NOTE: Similar to the recommendation of new type, you should use '_t' at the end of them.
 * 
 * NOTE: Memory is slower than CPU processes, one byte is called a word and it is
 * specified or stored in the memory access which was read by the CPU.
 * 
 * Packing structures is a good practice to prevent binaries incompatibilites and
 * performance degradation, you can do it like this:
 * 
 * struct __attribute__((__packed__)) ex_struct_t 
 * {
 *     <type> <name>;
 *     ...
 * };
 * 
 * NESTED STRUCTURES: Like conditions, structures can be nested so they will become
 * "complex data types". This allows to simplify the code and avoid redundancy.
 * 
*/

// Example 1: Simple structure type example
typedef struct 
{
    char c;
    char cpp;
    char py;
} extension_t;

// Example 2: Simple structure type and nested structure
typedef struct 
{
    double x;
    double y;
    double z;
} point3d_t;

typedef  struct 
{
    point3d_t linear;
    point3d_t angular;
} command_t;

int main(int argc, char **argv)
{
    // Example 1: Using a new type of structure.
    printf("E1: New type of structure: \n");
    extension_t collect;
    collect.c = 'c';
    collect.cpp = '+';
    collect.py = 's';
    printf("Structure:\tC: %c ,\tC++: %c ,\tPy: %c\n", collect.c, collect.cpp, collect.py);

    // Example 2: Using nested structure.
    printf("\nE2: A nested structure...");
    point3d_t coordinate;
    command_t commander;
    coordinate.x = 0;
    coordinate.y = 1;
    coordinate.z = 0;
    commander.linear = coordinate;
    commander.angular.x = 2;
    commander.angular.x = 1;
    commander.angular.x = 3;

    printf("Nested Structure: \n");
    printf("\tLinear: x:%f, y:%f, z:%f\n", commander.linear.x, commander.linear.y, commander.linear.z );
    printf("\tAngular: x:%f, y:%f, z:%f\n", commander.angular.x, commander.angular.y, commander.angular.z );

    return 0;
}
