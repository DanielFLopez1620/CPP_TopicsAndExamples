// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * There would be cases where the memory is a scarce and valuable resource, sometimes it 
 * can be called 'constrained environment' which means there are constrains related to the
 * resources, in this case memory, so the solution is to search optimization and good
 * management.
 * 
 * One example of this cases are embedded systems, where memory and time are the matter,
 * also called 'time complexity', which is added by every algorithm (Big-O functions). The
 * key is to get the best of both worlds (memory and time). So, it is a good practice to
 * assume we are working with constrained environments.
 * 
 * - PACKED STRUCTURES: They discard memory aligment and a better storing (compact). It
 * consumes less memory, but create a slower program.
 * 
 * - COMPRESSION: Good for programs with a lot of text data, because it has a high
 * compression ratio, which allows to save memory but has a CPU intensive cost.
 * 
 * - EXTERNAL DATA STORAGE: It means taking help for the network, cloud or a hard drive,
 * it relates with the cache (it is not main storage), although external memory is lows,
 * it can be balanced with algorithms, some services are PostgreSQL and Oracle.
 * 
 * - PERFORMANT ENVIRONMENT: Another problem is that for faster algorithms, you will need
 * more memory. One option can be 'caching' data which can increase performance, if it is 
 * the correct implementation. In simple terms, it refers to the interaction between two
 * data storage that read/write speeds are different, and the CPU is fast but fetching data
 * from memory is slow. So, you need to study the 'performance gain', this implies that the 
 * cache usually is the faster (and commonly the smaller) memory, then you can exchange data
 * from the two drives to the faster when needed, this is known as 'hit' (already in cache)
 * and 'miss' (pending in cache).
 * 
 *    - Cache-friendly code: It needs to consider the CPU and the fetching process, and in 
 *      the process, blocks are transferred into the cache (usually more that needed). A
 *      proximity is a value needed near the previous address (of the block) added, the reason
 *      follows the 'principle of locality' (neighborhood) and this can be exploted to create 
 *      more efficient algorithms.
 * 
 * 
 * NOTE: To verify the time comsuption, you can use time:
 *       time ./<file.out> <params>
*/

#include <stdlib.h> // For allocation functions in heap
#include <string.h> // For string functions like strcmp

void custom_fill(int* matrix, int num_rows, int num_cols);
void display_matrix(int* matrix, int num_rows, int num_cols);
void dis_opt_matrix(int* matrix, int num_rows, int num_cols);
int sum_matrix(int* matrix, int num_rows, int num_cols);
int sum_opt_matrix(int* matrix, int num_rows, int num_cols);



int main(int argc, char **argv)
{
    // Let's try a cache-friendly code
    printf("This is a cache-friendly attempt code:\n");

    if (argc < 4)
    {
        printf("Usage: %s [printf | sum_matrix | sum_opt_matrix] ");
        printf("[number-of-rows] [number-of-cols]\n", argv[0]);
    }

    char* operation = argv[1];
    int num_rows = atol(argv[2]);
    int num_cols = atol(argv[3]);

    int* matrix = (int*) malloc(num_rows * num_cols * sizeof(int));
    
    custom_fill(matrix, num_rows, num_cols);

    if (strcmp(operation, "print") == 0)
    {
        display_matrix(matrix, num_rows, num_cols);
        dis_opt_matrix(matrix, num_rows, num_cols);
    }
    else if (strcmp(operation, "sum_matrix") == 0)
    {
        int sum = sum_matrix(matrix, num_rows, num_cols);
        printf("Matrix sum type 1: %d\n", sum);
    }
    else if(strcmp(operation,"sum_opt_matrix"))
    {
        int sum = sum_opt_matrix(matrix, num_rows, num_cols);
        printf("Matrix sum type 2: %d\n", sum);
    }
    else
    {
        printf("ERROR: Invalid options\n");
        exit(1);
    }

    return 0;
}

/**
 * Function to fill a integer matrix with a sequence.
 * 
 * @param matrix Integer pointer to the matrix.
 * @param num_rows Integer number of the quantity of rows.
 * @param num_cols Integer number of the quantity of rows.
*/
void custom_fill(int* matrix, int num_rows, int num_cols)
{
    int ind = 1;
    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_cols; j++)
        {
            *(matrix + i * num_cols + j)= ind + j;
        }
        ind += num_cols;
    }
}

/**
 * Function to display/print a matrix (matrix form) by using a pointer.
 * 
 * @param matrix Integer pointer to the desired matrix.
 * @param num_rows Integer number of the quantity of rows.
 * @param num_cols Integer number of the quantity of rows.
*/
void display_matrix(int* matrix, int num_rows, int num_cols)
{
    int ind;
    printf("Info in matrix pointer:\n");
    for (int i = 0; i < num_rows; i++)
    {
        printf("| ");
        for (int j = 0; j < num_cols; j++)
        {
            printf("%d |", *(matrix + i * num_cols + j));
        }
        printf("\n");
    }
}

/**
 * Function to display/print a matrix (flat form) by using a pointer.
 * 
 * @param matrix Integer pointer to the desired matrix.
 * @param num_rows Integer number of the quantity of rows.
 * @param num_cols Integer number of the quantity of rows.
*/
void dis_opt_matrix(int* matrix, int num_rows, int num_cols)
{
    printf("Another display of the matrix is:\n");
    printf("{");
    for (int i = 0; i < (num_rows * num_cols); i++)
    {
        printf(" %d,", *(matrix + i));
    }
    printf("}\n");
}

/**
 * Sum of all values in a matrix by using a pointer.
 * 
 * @param matrix Integer pointer to the desired matrix.
 * @param num_rows Integer number of the quantity of rows.
 * @param num_cols Integer number of the quantity of rows.
 * 
 * @return The result of adding all the values in the matrix
*/
int sum_matrix(int* matrix, int num_rows, int num_cols)
{
    int sum = 0;
    for(int i = 0; i < num_rows; i ++)
    {
        for(int j = 0; j < num_cols; j ++)
        {
            sum += *(matrix + i * num_cols + j);
        }
    }
    return sum;
}

/**
 * Sum of all values in a matrix by using a pointer (in a different way).
 * 
 * @param matrix Integer pointer to the desired matrix.
 * @param num_rows Integer number of the quantity of rows.
 * @param num_cols Integer number of the quantity of rows.
 * 
 * @return The result of adding all the values in the matrix
*/
int sum_opt_matrix(int* matrix, int num_rows, int num_cols)
{
    int sum = 0;
    for(int j = 0; j < num_cols; j++)
    {
        for(int i = 0; i < num_rows; i++)
        {
            sum += *(matrix + i * num_cols + j);
        }
    }
}