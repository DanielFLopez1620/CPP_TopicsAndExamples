// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with g++

#include <string.h>
#include <iostream>


class Person
{
public:
    char name[20];
    int ID;
};

class Worker : public Person
{
public:
    float salary;
};

int main(int argc, char const *argv[])
{
    Worker worker;
    strcpy(worker.name,"Jun");
    worker.ID = 2;
    worker.salary = 105;

    std::cout << "Worker data:" << std::endl;
    std::cout << "\tName: " << worker.name << std::endl;
    std::cout << "\tID:" << worker.ID << std::endl;
    std::cout << "\tSalary: " << worker.salary << std::endl;
    return 0;
}
