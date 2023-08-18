// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * OOP is more than classes, programmin paradigm with procedural and function paradigm. And you will 
 * question ... why C if is not object oriented? It is because you can bring some ideas of OOP to your
 * code without trying to recreate C++ or other object oriented languages.
 * 
 * Our minds work for OOP, we have classes and define objects with properties/attributes, so an
 * important aspect goes outside the box: Variable naming, which can be a useful resource or a awful 
 * sentence. A name should apply a concept in a context, it must be clear and easy to understand, and 
 * here, we arrive to objects because they are ideas that are formed in the mind from the perception
 * of the world. If you can name it and can name its attributes, you understand the concept and its 
 * function/task in the world.
 * 
 * A solution to a problem is made based on an explanation in terms of the concepts that conform/create
 * the problem (and its relationship). In the case of a computer, you are the one who solve the problem
 * breaking it in single parts, and the computer is your tool for executing the solution.
*/

#include <string.h>
#define BUF 10

int main(int argc, char **argv)
{
    printf("E1: Classical Object Oriented Thinking in Humans:\n");
    char employee_name [BUF] = "Dan";
    char employee_surname [BUF]= "Smith";
    int employee_age = 16;
    double employee_salary = 100.5;
    printf("\tInfo:\n");
    printf("\tEmployee Name: %s\n", employee_name);
    printf("\tEmployee Surname: %s\n", employee_surname);
    printf("\tEmployee Age: %d\n", employee_age);
    printf("\tEmployee Salary: %f\n", employee_salary);

    return 0;
}
