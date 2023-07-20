// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with clang

/**
 * FUNCTIONS: C is procedural, so functions with act as well as procedures. It is
 * a block of logic with a name and can only return a single value. This blocks need
 * to accomplish the task before returning a value.
 * 
 * STACK SEGMENT: Literaly a segment that behaves as a stack, so the storage is
 * about storage and pop. It is used for function calls.
 * 
 * STACK FRAME: After calling a function, it contains the return address and the
 * params which are located on top of the segment.
 * 
 * LOCAL VARIABLES: Those variables that are located in top of the stack segment, so
 * the wil be freed when the stack is pop out.
 * 
 * PASS_BY_VALUE: The only way in C to pass arguments, the arguments are copied as
 * local variables.
*/

void assign(int num);
void assign2(int *num);

int main()
{
    int value = 1;
    // Example 1: Watching that local variables are local contexts.
    printf("E1: Local variables in functions...\n");
    printf("Before calling assign fucntion: %d\n", value);
    assign(value);
    printf("After calling assign function: %d\n", value);
    
    // Example 2: Passing by reference does not exist.
    printf("E2: Illusion of py bass reference...\n");
    int* val_ptr = &value;
    printf("Variable before calling assign fucntion: %d\n", value);
    printf("Pointer fefore calling assign fucntion: %p\n", (void*)val_ptr);
    assign2(val_ptr);
    printf("Variable after calling assign fucntion: %d\n", value);
    printf("Pointer after calling assign fucntion: %p\n", (void*)val_ptr);
    // <-

    return 0;
}

/**
 * Simple assign in the local context.
 * @param num Var to locally adapt the value.
*/
void assign(int num)
{
    num = 1620;
}

/**
 * Illusion function to pass and argument by reference, which allow modification.
 * @param num Integer pointer of the value that you want to be changed.
*/
void assign2(int *num)
{
    int value = 1620;
    *num = value;
    num = &value;
}
