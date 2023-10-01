// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Here we will explore some pseudocodes to undestand 'before constraint' context. 
 * 
 * Check the main for three cases of implementation:
 *      1. Base case of implementation, as a secuential list.
 *      2. Includes switch task
 *      3. Includes switch task, in a different order from the preovius one.
 * 
 * For these, you can say you have 'shared resources' and you may not know the exact moment of the switch.
 * This implies that a task can have different 'intermediate states' in different machines, althought
 * they are the same task. For this, you will need a good 'syncronization' method or methods to determinate
 * the situation with a good chance.
*/

int main(int argc, char **argv)
{
    // First Case:
    printf("First pseudo code:\n");
    printf("\t1. GotoStore()\n");
    printf("\t2. SelectApples(5)\n");
    printf("\t3. BuyApples(3)\n");
    printf("\t4. PackApples(3)\n");
    printf("\t5. LeaveStore()\n");

    // Second Case:
    printf("\nSecond pseudo code:\n");
    printf("\t1. GotoStore()\n");
    printf("\t<< Switch Task>>");
    printf("\t2. SelectApples(5)\n");
    printf("\t3. BuyApples(3)\n");
    printf("\t<< Switch Task>>");
    printf("\t4. PackApples(3)\n");
    printf("\t5. LeaveStore()\n");

    // Third Case:
    printf("\nSecond pseudo code:\n");
    printf("\t1. GotoStore()\n");
    printf("\t2. SelectApples(5)\n");
    printf("\t<< Switch Task>>");
    printf("\t3. BuyApples(3)\n");
    printf("\t4. PackApples(3)\n");
    printf("\t<< Switch Task>>");
    printf("\t5. LeaveStore()\n");

    return 0;
}
