#include <string.h>
#include "L03_c_object.h"


/**
 * Behavior function that create an account_t data with the name, the base ID and 
 * initial balance equal to zero.
 * 
 * @param ac Pointer to the account attribute structure.
 * @param name Name for the account creation.
*/
void account_construct(account_t* ac, const char* name)
{
    strcpy(ac->name, name);
    ac->ID = 1;
    ac->balance = 0.0;
}

/**
 * Behavior function that destroys an account_t object.
 * 
 * @param ac Pointer to the account attribute structure.
*/
void account_destruct(account_t* ac)
{
    free(ac);
}

/**
 * Behavior function that add money to the account.
 * 
 * @param ac Pointer to the account attribute structure.
 * @param deposit Value recieved in the account.
*/
void account_deposit(account_t* ac, double deposit)
{
    ac->balance += deposit;
}

/**
 * Behavior function used for payments.
 * 
 * @param ac Pointer to the account attribute structure.
 * @param pay Value to pay and take from the account.
*/
void account_withdraw(account_t* ac, double pay)
{
    ac->balance -= pay;
}