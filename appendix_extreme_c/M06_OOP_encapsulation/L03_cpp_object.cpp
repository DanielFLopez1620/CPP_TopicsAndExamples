// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with g++


/** 
 * Take into account that with C++ the pointers are replace with the key word 'this' and it means
 * the current object, which aims to simplify functions and pointer management.
*/
#include <string.h>
#include "L03_cpp_object.h"

/**
 * Base constructor for the account object (cpp version).
 * 
 * @param name Name of the account's holder
*/
Account::Account(const char* name)
{
    strcpy(this->name, name);
    this->ID = 0;
    this->balance = 0.0;
}

/**
 * Base destructure for the account object (cpp version)
*/
Account::~Account() {}


/**
 * Member function to generate deposits in the account
 * 
 * @param deposit Value to deposit
*/
void Account::Deposit(double deposit)
{
    this->balance += deposit;
}

/**
 * Member funcction to generate payments in the account
 * 
 * @param pay Value to take from the account
*/
void Account::Withdraw(double pay)
{
    this->balance -= pay;
}
