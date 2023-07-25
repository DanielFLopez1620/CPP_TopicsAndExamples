// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#ifndef L02_C_PROJECT_H
    #define L02_C_PROJECT_H
    // Custom type definition in header file
    typedef enum
    {
        FEW,
        VALID,
        MANY,
        TOO_MANY
    } sum_type_t;

    // Prototype of function in header
    int sum(int*, int);
    sum_type_t type_sum(int sum);
#endif
