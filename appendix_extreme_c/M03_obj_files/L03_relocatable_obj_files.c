// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>
#include "L03_relocatable.h"

/**
 * RELOCATABLE OBJECT FILES: Are considered temporary products of C compilation. They contain
 * machine level instruction from the traslation, values of globals and the symbol table.
 * 
 * A final product is the sum of all the items provided by relocatable object files
 * 
 * For reviewing an .elf file, you can use to the obj file:
 *   - readelf -hSl <file.o>
 *  
 * 
 * EXECUTABLE OBJECT FILES: The final product of the C project, which can link 
 * different relocatable object files.
 * 
 * NOTE: If you forget about compilation the command is showed below, just remember to be 
 *       in the correct directory:
 * 
 *       gcc -c <file.c> -o <file.o>
 * 
 *       If you want to create an executable, then you can run:
 *       gcc <file.o> -o <file.out>
 * 
 *       
 */

int main(int argc, char **argv)
{
    int num1 = 5;
    int num2 = 10;

    int min1 = min(num1, num2);
    int min2 = min_3(num1, num2, -2);

    printf("Minimun of (%d, %d) is %d", num1, num2, min1);
    printf("Minum of (%d, %d, %d) is %d", num1, num2, -2, min2);

    return 0;
}
