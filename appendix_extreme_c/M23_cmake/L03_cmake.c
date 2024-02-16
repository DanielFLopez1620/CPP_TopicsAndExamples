// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * CMake isn't a build system but it is a generator for other tools like Make and Ninja, as you may
 * have noticed writing a effective Makefile is difficult, so the solution is CMake and Autotools.
 * 
 * Another important feature is the 'dependency management' which is in charge of checking installed
 * dependencies and won't continue if a dependency is missing. Also, it supports nested modules,
 * which means you can generate CMakeLists.txt files thorugh your project and it will execute 
 * each one if you use 'cmake' in the base of your project, something like this:
 * 
 * project_folder/
 *      |--- impl
 *      |--- CMmakeLists.txt
 *      |    |---- impl_1.c
 *      |    |---- impl_2.c
 *      |    |---- CMmakeLists.txt
 *      ---- exec
 *          |----- main.c
 *          |----- CMmakeLists.txt
 * 
 * The structure of a CMakeList that cachieves something similar to our last proposal of Make, is 
 * shown below:
 * 
 *      cmake_minimum_required(VERSION 3.8)
 *      
 *      include_directories(impl)  # Include base directory
 * 
 *      add_subdirectory(impl)     # Add subdirectories (which can contain src code or other Cmake)
 *      add_subdirectory(exec)
 * 
 *      add_library(impl STATIC    # Simple target declaration for a static library
 *          impl1.c
 *          impl2.c
 *      )
 * 
 *      add_executable(impl_exe.out
 *          main.c
 *      )
 * 
 *      target_link_libraries(impl_exe.out
 *          impl
 *      ) 
 *  
 * Note taht for using CMake, you will need a /build directory (which you can ignore if using git
 * or any other source control management system), do not forget the key command:
 *  
 *      cmake .
 *      # After completation, a Makefile should appear
 *      make
 *      # And you will be done for your project
 *      
*/

int main(int argc, char** argv)
{
    printf("If you want to learn more of CMake, go to:\n");
    printf("\t- https://cmake.org/cmake/help/latest/index.html\n");
}