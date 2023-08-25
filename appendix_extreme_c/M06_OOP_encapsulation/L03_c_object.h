// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef L03_ENCAPSULATION_C_H
#define L03_ENCAPSULATION_C_H

// Attribute structure definition
typedef struct
{
    char name[15];
    int ID;
    double balance;
} account_t;

// Prototypes declaration for behavior functions
void account_construct(account_t*, const char*);
void account_destruct(account_t*);
void account_deposit(account_t*, double);
void account_withdraw(account_t*, double);

#endif