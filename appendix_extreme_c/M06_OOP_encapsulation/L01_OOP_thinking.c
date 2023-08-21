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
 * 
 * Each object has attributes, it can be color, size, status... and go on with the ideas that defines
 * the object you are considering. But keep in mind it can change, you can paint something to change its
 * color, or the size can change through the time, it means they are 'mutable'. Also, they can be 
 * 'stateless' beacuse they do not carry states, for example, if the concept cannot change, because the 
 * darkness will always be the same.
 * 
 * The objects we are considering are present in a well-defined domain, the boundaries of the system where 
 * it works, and they are related with a general concept that relates the objects present in the domain. It
 * also relates with the programming language, as it would be difficult to use if the domain
 * isn't compatible with the desired objective. Inside this domains, there are relationships, which can
 * complement the definitions and the models of the object, which derivates the relationships are born with 
 * the addition of common attributes which can be 'mutable' and 'immutable'.
 * 
 * To have an object we need to construct it (no create or build the object):
 *  - It can be an empty object (without attributes or minimum attributes).
 *  - Attributes are added in the run time according to the inner structure and the surrounding environment.
 *  - Each object is a different entity, even though, they have the same information.
 *  - In interpreted programming languages the object is kept as a map/hash that can be modified during
 *    the execution, it also known as 'prototype-based OOP'. (It happens with Ruby, Python, PHP)
 *  - Another approach is to create immutable objects since the beginning, as the structure will be kept. This
 *    is known as predesiged 'object template' or 'class template', which will be the base for the OOP. (Present
 *    int Java, C++) , but it real name is 'class-based OOP'.
 * 
 * Now, time for clarification an object and an instance are the same thing, but it doesn't mean the same with 
 * reference. This last one means that a pointer has the memory adress of the object. And here, in C, the objects
 * doesn't have name but the reference has one, do you remember about Stack and Heap? (Including its differences
 * with the memory allocation and managment".
 * 
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
