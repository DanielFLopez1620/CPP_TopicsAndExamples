#include <stdio.h>

#include "L02_fibonacci.h"

/**
 * In the case of unit testing, you will need to isolate the function for test them, we will
 * illustrate the situation with the code from the 'L02_fibonacci.h' and 'L02_fibonacci.c' to make
 * the corresponding test, here in the main, you will find info of the execution of them
 * and also how the tests works.
 * 
 * First, for executing this code, you can use:
 *      gcc -c L02_fibonacci.c -o impl.o
 *      gcc -c L02_main_fib.c -o main.o
 *      gcc impl.o main.o -o fib.out
 * 
 * As our fibonacci code has two function, we will need two independent test files, we have
 * implemented them in the files: "L02_test_fib.c" and "L02_test_next_num.c" each one implements
 * a set of functions that begins with "TESTCASE" which is used as a convention to indicate a test,
 * followed by the name of the original function and last a indication of the situation to test.
 * In the case of next_num we only have a test case, but in the case of fib we have a test suite
 * (in other words, a collecction of test cases).
 * 
 * But for making our tests work, we will need another main, that will load and call the test calls,
 * so if something goes wrong we can know it. And the file is 'L02_tests.c". You can run the test with:
 * 
 *      gcc -g -c L02_fibonacci.c -o impl.o
 *      gcc -g -c L02_test_nex_num.c -o test1.o
 *      gcc -g -c L02_test_fib.c -o test2.o
 *      gcc -g -c L02_tests.c -o main.o
 *      gcc impl.o test1.o test2.o main.o testing.out
 *      ./testing.out
 * 
 * Everything should be right, but you can experiment with th efib function, for example, by adding
 * one to the result, and the test are gointg to fail... but.... you may not sure where or what
 * the test is failing. For that cases C/C++ provides libraries for making the tests better, in the 
 * next lesson we will talk about them.
 * 
 * 
*/

int main(int argc, char** argv)
{
    for(int i = 0; i < 10; i++)
    {
        printf("Fibonacci of %d is %d.\n", i, fibonaci(i));
    }

    printf("If you want to learn more of tests, you can check:\n");
    printf("\t- https://www.testrail.com/blog/highly-testable-code/\n");
    printf("\t- https://en.wikipedia.org/wiki/Test_double\n");
    printf("\t- https://www.testrail.com/blog/highly-testable-code/\n");
    printf("\t- https://www.testrail.com/blog/highly-testable-code/\n");
    return 0;
}