// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * MAKE: Works with 'Makefiels' which is a text file named as mentioned before (with no extensions)
 * that is located in the source directory and contains the build targets and commands to build the
 * project. 
 * 
 * You will usually have a structure like this for a project:
 * 
 *      project_folder/
 *      |--- impl
 *      |    |---- impl_1.c
 *      |    |---- impl_2.c
 *      ---- exec
 *          |----- main.c
 * 
 * When searching to build the project, you should create a folder for the output files (mostly 
 * called 'out', then compile and get the .o files and put them in the 'out' directory, and finally
 * create the executable (.out) with all the info you want, in our example could be:
 * 
 *      mkdir - out
 *      gcc -c impl/impl1.c -o out/impl1.o
 *      gcc -c impl/impl2.c -o out/impl2.o
 *      ar rcs out/libimpl.a out/impl1.o out/impl2.o
 *      gcc -c -Iimpl.a exec.main.c - out/main.o
 *      gcc -Lout -limpl out/main.o -o out/exec_impl.out
 * 
 * NOTE: Remember:
 *      gcc -c <file.c> -o <file.o>  # Compile code 
 *      gcc <files.o> -o <exe.out>   # Get executable
 *      ar rcs <library.a> <files.o> # Create library 
 * 
 * But, when a lot of files appear, it will get complicated, and you also have to make some
 * considerations, like: 
 * 
 *  - Is everything going to run in the same platforms?
 *  - What if a new dir is added?
 *  - What happens if a new script is added?
 * 
 * And you can mention more, but this can be solved with a good build system, following our example
 * is:
 * 
 *      build:
 *          mkdir - out
 *          gcc -c impl/impl1.c -o out/impl1.o
 *          gcc -c impl/impl2.c -o out/impl2.o
 *          ar rcs out/libimpl.a out/impl1.o out/impl2.o
 *          gcc -c -Iimpl.a exec.main.c - out/main.o
 *          gcc -Lout -limpl out/main.o -o out/exec_impl.out
 *      clean:
 *          rm -rfv out
 * 
 * The location of the file must be:
 * 
 *      project_folder/
 *      |--- Makefile
 *      |--- impl
 *      |    |---- impl_1.c
 *      |    |---- impl_2.c
 *      ---- exec
 *          |----- main.c
 * 
 * After you have made the file, you can go to your directory and run 'make', it will execute and
 * build everything you need.
 * 
 * But what if I told you the way presented is the old one? As you should have noticed that it is
 * almost the same that a .sh file. Now, let's move to a better and more recent implementation:
 * 
 *      
 * 
*/