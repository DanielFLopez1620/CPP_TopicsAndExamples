// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * COMPOSITION: Those cases when one object is possessed by other one, for example, a 
 * computer object has a CPU object, a RAM object ... inside of it and it is a composition. So,
 * the lifetime is linked and they have both to be freed, and the relationship is given by
 * the problem domain.
 * 
 * You can check the files of the objects battery and my_clock, to get an idea of the implementation
 * of composition in C. For compilation you will need:
 * 
 * NOTE: Two objects that are not of the same type, must not know the other's implementation
 * details, as the information hiding.
*/

#include <stdlib.h>
#include "L02_clock.h"

int main(int argc, char **argv)
{
    struct my_clock_t* my_clock = my_clock_new();

    my_clock_ctor(my_clock);

    printf("my_clock:\n");
    my_clock_status(my_clock);

    for(int i=0; i <= 40; i++)
    {
        my_clock_give_time(my_clock);
        my_clock_status(my_clock);
    }

    my_clock_dtor(my_clock);
    free(my_clock);

    return 0;
}
