// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with g++

#ifndef L03_ENCAPSULATION_CPP_H
#define L03_ENCAPSULATION_CPP_H

class Account 
{

public:
    // Class Constructor
    Account(const char*);

    // Class Destructor
    ~Account();

    // Member Functions
    void Deposit(double);
    void Withdraw(double);

    // Data Members
    char name[15];
    int ID;
    double balance;
};

#endif