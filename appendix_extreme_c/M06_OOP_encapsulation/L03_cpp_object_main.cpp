// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with g++

#include <iostream>
#include "L03_cpp_object.h"

int main(int argc, char const *argv[])
{
    // Object creation
    Account ex_acc("Dan");

    // Example implementation
    ex_acc.Deposit(100.0);
    std::cout << "Current deposit is: " << ex_acc.balance << std::endl;

    ex_acc.Withdraw(28.0);
    std::cout << "Current deposit is: " << ex_acc.balance << std::endl;

    return 0;
}
