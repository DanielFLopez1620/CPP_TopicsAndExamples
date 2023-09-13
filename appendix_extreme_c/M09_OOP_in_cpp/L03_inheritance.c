// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Here we take a look and compare the inheritance approach between C and CPP, as you should
 * remember, in C we used structures and nested them or we used pointers to these structures.
 * 
 * Do not forget to check the codes and compare them, to get a better understanding of the
 * implementations.
 * 
 * To check the inheritance you can use the debbugger and check the memory allocations, you can
 * use:
 *    gcc -g <file.c> -o <file.out>
 *    gdb ./<file.out>
 * 
 *    g++ -g <file.cpp> -o <file.out>
 *    gdb ./<file.out>
 * 
 * Also, take into account that your limit isn't 'single inheritance' as you can nest multiples
 * structures in C (just remember to know the size of the structures so you can nest structures
 * and use a single pointer) or using multiple public imports in C++.
 * 
*/

#include <string.h>

typedef struct 
{
    char name[20];
    int ID;
} person_t;

typedef struct 
{
    person_t person;
    float salary;
} worker_t;

int main(int argc, char **argv)
{
    worker_t worker;
    strcpy(worker.person.name, "Dan");
    worker.person.ID = 1;
    worker.salary = 100;
    
    printf("Worker data:\n");
    printf("\tName: %s\n", worker.person.name);
    printf("\tID: %d\n", worker.person.ID);
    printf("\tSalary: %f\n", worker.salary);

    return 0;
}


