// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc (This code is intended to fails)

#include <stdio.h>

/**
 * Key concept, the programmer is the unique person that know the lifetime of a variable in
 * the Heap region, and for that is the responsible for the deallocation.
 * 
 * One strategy for this is using owners for memory blocks instead of having a scope
 * that relates with a block. This is also called ownership.
 * 
 * For example, in this code, there are two ownerships (com1) inside the structure and the
 * (form) structure present in main. So, if the block is owned, it should not be freed by 
 * someone outside that ownership.
 * 
 * Also, remember, much or many is not better, if you free space twice or more, it will create a
 * corruption issue.
 * 
 * RAII is another technique which come from Resource Acquisiton Is Initialization....
 * 
 * Note: C had a garbage collector, you can know more of it here: https://www.hboehm.info/gc/
*/

#include <stdlib.h>

#define QUEUE_MAX_SIZE 100

typedef struct 
{
    int num1;
    int num2;
    double* com1;
} complex_t;

// ----- Prototype declarations ------------------------------------
void assign(complex_t* form);
void deassign(complex_t* form);
void append(complex_t* form, double obj);
double deappend(complex_t* form);

// --------- MAIN -------------------------------------------------
int main(int argc, char **argv)
{
    complex_t* comp = (complex_t*)malloc(sizeof(complex_t));

    // Create allocation and keep values
    assign(comp);

    // EnQueue
    append(comp, 1.0);
    append(comp, 2.0);
    append(comp, 3.0);

    //Dequeue
    printf("%f\n", deappend(comp));
    printf("%f\n", deappend(comp));
    printf("%f\n", deappend(comp));

    // Final deallocations and free pointer
    deassign(comp);
    free(comp);
    return 0;
}

// ------ Function definitons --------------------------------------

/**
 * Function for filling the a complex structure type.
 * 
 * @param form Struct you want to initialize.
*/
void assign(complex_t* form)
{
    form->num1 = 0;
    form->num2 = 0;
    form->com1 = (double*)malloc(QUEUE_MAX_SIZE * sizeof(double));
}

/**
 * Deallocate the memory region of the com1 property of the structure.
 * 
 * @param form Struct you want to deallocate (free) the com1 property
*/
void deassign(complex_t* form)
{
    free(form->com1);
}

/**
 * Queue alike function for the complex structure
 * 
 * @param form Complex structure you want to append (in this case add queue)
 * @param obj Object to append (in this case add queue)
*/
void append(complex_t* form, double obj)
{
    form->com1[form->num2] = obj;
    form->num2++;
}

/**
 * Dequeue alike function for the complex structure
 * 
 * @param form Complex structure you want to deappend (int his case dequeue)
*/
double deappend(complex_t* form)
{
    double obj = form->com1[form->num1];
    form->num1++;
    return obj;
}
