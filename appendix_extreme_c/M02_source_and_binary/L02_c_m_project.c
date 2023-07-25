// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>
#include "L02_c_project.h"

/**
 * INSTRUCTION FOR PROJECT COMPILATION:
 * - PREPROCESING: Here some directives must be resolved, those preprocessing directives
 *                 begin with '#' in C and C++. The command related is:
 *                       gcc -E <c_file>.c
 *                       clang -E <c_file>.c
 *                 It deletes the comments and copies the declarations present in the header.
 * - COMPILATION: Once the traslation unit completed its task, it is necessary to obtain the
 *                assembly code. The flag is -S:
 *                       gcc -S  <c_file>.c
 *                This will create a .s file, with the code for a machine, but needs more 
 *                processing.
 * - ASSEMBLY: Here it's need to transform the code into machine-level instructions, usually to
 *             an object file, which can be a synonum of binary. The command is:
 *                        as <s_code>.s -o <final_file>.o
 *             But there is a better option
 *                        gcc -c <file.c>
 * -> 98/70
 * 
*/

int main(int argc, char** argv)
{
    int data[5] = {2, 4, 8, 1, 10};
    int sum_all = sum(data, 5);
    sum_type_t data_type = type_sum(sum);

    return 0;
}