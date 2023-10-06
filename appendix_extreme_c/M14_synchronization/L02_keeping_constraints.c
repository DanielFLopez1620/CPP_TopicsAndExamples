// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * The invariant constraints must remain, here we show some examples:
 * 
 * - Case 1: To print the desired number, the order is strict.
 * - Case 2: Print a organized routine, that is implemented in "chaos".
 * - Case 3: Data integrity, you must be sure that the system reads the latest value and update
 *   the corresponding state before continuing.
 * 
 * NOTE: Read the code, as if the tasks can be interrupted and the switched to another, this is
 * when the interleavings can happen.
*/

int main(int argc, char **argv)
{
    printf("Example 1: Constraints with print\n");
    printf("\tSystem \n");
    printf("\t{\n");
    printf("\t    State\n");
    printf("\t    {\n");
    printf("\t        int x = 0;\n");
    printf("\t    }\n");
    printf("\t    Task A\n");
    printf("\t    {\n");
    printf("\t        x = 1620;\n");
    printf("\t    }\n");
    printf("\t    Task B\n");
    printf("\t    {\n");
    printf("\t        printf(\"%%d\", x);\n");
    printf("\t    }\n");
    printf("\t\n");
    printf("\t}\n\n");

    printf("Example 2: Print order\n");
    printf("\tSystem \n");
    printf("\t{\n");
    printf("\t    State\n");
    printf("\t    {\n");
    printf("\t        char word[7];\n");
    printf("\t    }\n");
    printf("\t    Task A\n");
    printf("\t    {\n");
    printf("\t        word = \"Second\"\n");
    printf("\t    }\n");
    printf("\t    Task B\n");
    printf("\t    {\n");
    printf("\t        word = \"Third\"\n");
    printf("\t    }\n");
    printf("\t    Task C\n");
    printf("\t    {\n");
    printf("\t        word = \"First\"\n");
    printf("\t    }\n");
    printf("\t\n");
    printf("\t}\n\n");

    printf("Example 3: Integrity constraint\n");
    printf("\tSystem \n");
    printf("\t{\n");
    printf("\t    State\n");
    printf("\t    {\n");
    printf("\t        int num = 1620\n");
    printf("\t    }\n");
    printf("\t    Task A\n");
    printf("\t    {\n");
    printf("\t        int a;\n");
    printf("\t        a = x;\n");
    printf("\t        a = a + 1;\n"); // a++ or a+=1 aren't atomic.
    printf("\t        x = a;\n");
    printf("\t    }\n");
    printf("\t    Task B\n");
    printf("\t    {\n");
    printf("\t        int b;\n");
    printf("\t        b = x;\n");
    printf("\t        b = b + 3;\n");
    printf("\t        x = b;\n");
    printf("\t    }\n");
    printf("\t    Task C\n");
    printf("\t    {\n");
    printf("\t        word = \"First\"\n");
    printf("\t    }\n");
    printf("\t\n");
    printf("\t}\n");


    return 0;
}
