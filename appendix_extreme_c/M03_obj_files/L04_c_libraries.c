// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>

/**
 * STATIC LIBRARIES: It is an archive made of relocatable object files, so it can be linked with
 * other files to create an executable object file, see it more like a container created by the 'ar'
 * utility. The way to create a static library is from multipl obj files is:
 * 
 *        ar crs <name_lib>.a <relocatable_object_files...>
 *        mkdir -p /opt/<library_dir>
 *        mv <name_lib>.a /opt/<library_dir>
 * 
 * If you want to see the content (relocatable object files) of a library, you can run:
 *        
 *        ar t /opt/<library_dir>/<name_lib>.a
 * 
 * To use this library, we need to make it public, the goal is to make a 'public interface' (API of 
 * the library), so you can import the header and use the content. So when you compile it is able to
 * find the dependencies. The link is made with:
 * 
 *        gcc <main.o> -L/opt/<library_dir> -l<name> -lm -o <output>.out
 * 
 * Here -L tells to consider the path for static and shared libraries. Next, -l tells to look
 * for the file (remember that a goog practice to call the libraries lib<name>, so you only add -l<name>), 
 * -lm indicates to search for another file (libm.a which contains math functions). After this process, all
 * definitions will be "embedded" in tht exectuable.
 * 
 * 
 * The flags come from c (create the archive), r (insert file members) and s (write obj file index).
 * 
 * 
 * 
 * 
 * 
 * NOTE: A linker uses the library to try to extract the relocatable object file, then it will look
 * for missing parts and try to resolve them.
 */

int main(int argc, char const **argv)
{
    printf("Do not forget to read the comments to know more about libraries...\n");
    printf("Useful resources:\n");
    printf("- https://stackoverflow.com/questions/29714300/what-does-the-rcs-option-in-ar-do\n");
    return 0;
}
