// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

/**
 * BEST PRACTICES OF STACK:
 * 
 * - All Stack variables have a scope, which is related to the lifetime of the var, so
 * the allocation and deallocation is automatic because its nature (FILO or stack and 
 * pop).
 * 
 * - 
 * 
 * 
 * - 
*/


/**
 * Simple function that contains a local variable
*/
int* num_func()
{
    int num = 1620; // Variable that will life until the function returns.
    return &num; // This will go wrong in compilation
}

int main(int argc, char **argv)
{
    int a; // Variable that will life until the main is finished.
    int* num_ptr = num_func(); // Obtain address of local variable
    *num_ptr = 1111; // This will be broken
    return 0;
}
