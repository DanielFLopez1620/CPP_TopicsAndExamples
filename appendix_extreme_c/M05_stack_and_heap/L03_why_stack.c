// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc (this program may crash for learning purposes)

/**
 * BEST PRACTICES OF STACK:
 * 
 * - All Stack variables have a scope, which is related to the lifetime of the var, so
 * the allocation and deallocation is automatic because its nature (FILO or stack and 
 * pop).
 * 
 * - Do not try to access by pointer to local variables, as they will 'die' when the 
 * context is completed, it could produce an error called 'return-local-addr'.
 * 
 * - Stack memory has a limited size, so do not abuse of it.
 * 
 * - The segment grows backward, as forward means that something was pushed.
 * 
 * - It has automatic memory managment (allocation and deallocation). 
 * 
 * NOTE: Some warnings can become errors, so you can specify them as erreros with the
 * flag -Werror in gcc, and you can make it more specific, for example, with 
 * -Werror=return-local-addr
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
