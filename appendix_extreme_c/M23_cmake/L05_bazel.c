// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * Bazel (developed by Google) is oriented to multiple languages like C, C++, Java, Go and
 * Objective-C and can be used in iOS projects. It is written in Java, and it is well-known for it
 * parallel and scalable builds, it also allow build of Make and Ninja (with flag -j).
 * 
 * It works a little bit different from the ones mentioned before, you need two files WORKSPACE and
 * BUILD, the first one in the root dir, and the second one should be on the modules part. For the 
 * WORKSPACE you need:
 * 
 *      c_library(
 *          name = "impl",
 *          srcs = ["impl1.c", impl2.c],
 *          hdrs = ["impl.h"],
 *          linkstatic = True,
 *          visibility = ["//exec:__pkg___"]
 *      )
 * 
 * The BUILD directory in the directory 'exec', should be:
 * 
 *      cc_binary(
 *          name = "impl_exe.out",
 *          srcs = ["main.c"],
 *          deps = [
 *              "//impl:impl"
 *          ],
 *          copts = ["-Icalc"]
 *      )
*/

int main(int argc, char** argv)
{
    printf("If you want to learn more about Bazel, you can go to:\n");
    printf("\t - https://docs.bazel.build/versions/master/bazeloverview.html");
}