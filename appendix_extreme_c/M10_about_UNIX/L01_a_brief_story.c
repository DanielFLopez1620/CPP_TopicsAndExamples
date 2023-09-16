// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Unix is (or was) the first Operating System (OS) implemented with a high-level programmin language, in that moment, C. It
 * was developed at Bell Labs, and in terms of one of the creators of C:
 * 
 *   "Doubtless, the success of Unix itself was the most important factor; it made the language available to hundreds of thousands 
 *   of people. Conversely, of course, Unix's use of C and its consequent portability to a wide variety of machines was important
 *   in the system's success." Dennis M. Ritchie – The Development of the C Language.
 * 
 * The precessor of Unix was Multics OS (developed by he MIT, General Eletric and Bell Labs) which was the introduction
 * of a secure OS. But some people at Bell Labs gave up on the project and started thinking in the idea of a
 * simpler and more efficient OS. So the idea of Unix started as a project.
 * 
 * But what are the differences? Both of them have onion arch mainly kernell and shell rings, this allowed programmers to
 * create theour own levels and they have the utilities of 'ls' and 'pwd'. However, Multics was expensive in the usage of 
 * resources, was complex by design.
 * 
 * Take into account something, Unix was first written in assembly (C didn't exist yet), but the version 4 was developed using
 * C in 1973.
 * 
 * For developing OS, BCPL was an option. It was a programming language developed by Marin Richards and was used for the 
 * Multics project. But this option didn't like to Bell Labs, even they preffered to start testing with assembly. Another reason
 * of the failure of BCPL was that it wasn't possible to implement in all the machines so they tried to correct this with 'B' (yeah, 
 * plan B of programming language).
 * 
 * As you may suppose, B was not a huge success, as it has type problems (only worked with WORD) and had problems
 * where the machines weren't able to process the same word lenght. The next generation was NB (New B, which is an example of
 * the enginering creativity), but is still had some feartures missing.
*/

int main(int argc, char const *argv[])
{
    printf("Here you can find some ineresting resources:\n");
    printf("\t* https://www.bell-labs.com/usr/dmr/www/chist.html\n");
    printf("\t* https://multicians.org/history.html\n");
    printf("\t* https://en.wikipedia.org/wiki/B_(programming_language)\n");
    
    return 0;
}
