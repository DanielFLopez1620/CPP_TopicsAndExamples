// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * SPIN LOCKS: They are mutex implementations, and these can act as memory barries, check the first example below. They
 * usually are made by simply busy-waiting. This implies a delay, so you will have to keep in mind that the critical
 * section must be small.
 * 
*/

int main(int argc, char **argv)
{
    printf("Example 1: First printing A, then B with spin locks\n");
    printf("System\n");
    printf("{\n");
    printf("    Shared State\n");
    printf("    {\n");
    printf("        int done = 0;\n");
    printf("        M = Mutex();\n"); // Not official implementation
    printf("    Task A\n");
    printf("    {\n");
    printf("        printf(\"A\");\n");
    printf("        SpinLock(M);\n");
    printf("        done = 1;\n");
    printf("        SpinUnlock(M);\n");
    printf("    }\n");
    printf("    Task B\n");
    printf("    {\n");
    printf("        SpinLock(M)\n");
    printf("        while(!done);\n");    
    printf("        {\n");
    printf("            Unlock(M);\n"); 
    printf("            Lock(M);\n");
    printf("        }\n");
    printf("        UnLock(M)\n");
    printf("        printf(\"B\");\n");  
    printf("    }\n");
    printf("}\n\n");
    
    return 0;
}
