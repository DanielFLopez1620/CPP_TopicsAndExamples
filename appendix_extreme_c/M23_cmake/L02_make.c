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
 *      CC = gcc
 * 
 *      build: prereq out/main.o out/libimpl.a
 *         ${CC} -Lout -lcalc out/main.o -o out/exec_impl.out
 *      
 *      prereq: 
 *          mkdir -p out
 *      
 *      out/libimpl.a: out/impl1.o out/impl2.o
 *          ar rcs out/libimpl.a out/impl1.o out/impl2.o
 *      
 *      out/main.o: exec/main.c
 *          ${CC} -c -Iimpl exec/main.c -o out/main.out
 * 
 *      out/impl1.o: impl/impl1.c
 *          ${gcc} -c impl/impl1.c -o out/impl1.o
 * 
 *      out/impl2.o: impl/impl2.c
 *          ${gcc} -c impl/impl2.c -o out/impl2.o
 *      
 *      clear: out
 *          rm -rf out
 * 
 * As you just C, you can declare variables, like 'CC', so variables with conditions allow us
 * to write flexible build intructions, and it also allows to include other Makefiles.
 * 
 * The Makefile is made of several targets ('name' + :), and the tabulations are needed to make the
 * program work, and it also allow a custom flow that cannot be achieved with shell and terminal. 
 * Another important feature is that it checks if changes have been made, if no change is detected
 * and the process is done again, it doesn't repeat unmodified targets. Also, you can add the
 * location of the headers to improve the process so they no longer have to be in the same folder.
 * 
 * Now, what if I told you, that the make file provided is still too verbose, so let's move to a
 * a better implementation that takes benefit from 'pattern matching' (NOTE: Makefiles can improve
 * a lot, here we only provide ilustrative examples).
 * 
 *      BUILD_DIR = out
 *      OBJ = ${BUILD}/impl/impl1.o \ 
 *            ${BUILD}/impl/impl2.o \
 *            ${BUILD}/exec/main.o
 *      CC = gcc
 *      HEADER_DIRS = -Iimpl
 *      LIBNAME = impl
 *      LIB = ${BUILD_DIR}/lib${LIBNAME}.a
 *      EXEC = ${BUILD_DIR}exec_impl.out
 * 
 *      build: prereq ${BUILD_DIR}/exec/main.o ${LIB}
 *          ${CC} -L${BUILD_DIR} -l${LIBNAME} ${BUILD_DIR}/exec/main.o -o ${EXEC}
 * 
 *      prereq:
 *          mkdir -p ${BUILD_DIR}
 *          mkdir -p ${BUILD_DIR}/impl
 *          mkdir -p ${BUILD_DIR}/exec
 * 
 *      ${LIB}: ${OBJ}
 *          ar rcs ${LIB} ${OBJ}
 * 
 *      ${BUILD_DIR}/impl/%.o: impl/%.c
 *          ${CC} -c ${HEADER_DIRS} $< -o $@
 * 
 *      ${BUILD_DIR}/impl/%.o: impl/%.c
 *          ${CC} -c ${HEADER_DIRS} $< -o $@
 * 
 *      clean: ${BUILD_DIR}
 *          rm -rf ${BUILD_DIR}
 * 
*/