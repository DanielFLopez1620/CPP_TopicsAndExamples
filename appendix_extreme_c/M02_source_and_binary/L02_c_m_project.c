// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc and clang

#include <stdio.h>
#include "L02_c_project.h"

/**
 * INSTRUCTION FOR PROJECT COMPILATION:
 * - PREPROCESING: Here some directives must be resolved, those preprocessing directives
 *                 begin with '#' in C and C++. The command related is:
 *                       gcc -E <c_file>.c
 *                       clang -E <c_file>.c
 *                 It deletes the comments and copies the declarations present in the header.
 * - COMPILATION: Once the traslation unit completed its task, it is necessary to obtain the
 *                assembly code. The flag is -S:
 *                       gcc -S  <c_file>.c
 *                This will create a .s file, with the code for a machine, but needs more 
 *                processing.
 * - ASSEMBLY: Here it's need to transform the code into machine-level instructions, usually to
 *             an object file, which can be a synonum of binary. The command is:
 *                        as <s_code>.s -o <final_file>.o
 *             But there is a better option that includes the above:
 *                        gcc -c <file.c>
 *             Here you can add a destiny file, but sometimes it's not recommended. But you can do:
 *                        gcc -c <c_file>.c -o <file>.o
 * 
 *  - LINKING: It refers to the combination ob the relocatable objects. But it depends on the arch
 *             of the processor, although it is possible to make the traslation if the
 *             assembly language is known and the assempbler tool is available.
 *             The default linker in Unix is 'ld', but you cannot simply link two files, you have
 *             to consider the dependencies of the file, so this a work for gcc and clang:
 *             gcc <file1>.o <file1>.o
 *             The default output will be 'a.out'
 * 
 *  - PREPROCESSOR: It has a parser that works for sustitutions of certain key words, and it 
 *                  allows different options, for example, CPP (C Pre-Processor):
 *                           cpp <file.c>
 *                  Also, do not pass, .i file to preprocessing as it is supposed to be already 
 *                  preprocessed.
 *  - COMPILER: Accepts the traslation of the preprocessor, which is passed to assembly instructions. 
 *              This can be difficult becuase it needs to be accurate and work with the present
 *              architecture. The compiler can be divided in frontend and backend.
 * 
 *              * Abstract Syntax Tree: The frontend part should parse the traslation and create an
 *                intermediate data structure, this is achieved by checking the C gramar and storing 
 *                it in a tree. It can be showed with:
 *                            clang -Xclang -ast-dump -fsyntax-only <c_file>.c
 *                         
 *  - ASSEMBLER: In Unix it is called by using 'as' utility. And remember two operating systems, maybe
 *               do not produce the same object file.
 * 
 *  - LINKER: Which result in the final product of a C Project, the extension can be .out or .exe for 
 *            executable files, .a or .lib for static libraries, or .so or .dll for dynamic
 *            libraries. Remember, it gathers all the symbols in a single file, but make sure to pass
 *            all the dependencies/definitions to make a valid object file.
 * 
 *  - OTHER ASPECTS: If you are interested in watching the symbols of an object file, you can run:
 *                         nm <obj_file>.o
 *                   Which print the names of the objects (or functions) present in the file. Another
 *                   similar function is 'readelf' utility:
 *                         readelf -s <obj_file>.o
 *                   This put the symbols it a table with it´s size, visual and name.
 *                   
 *                    If you are interested in disassembly a machine code, you are searching for
 *                    'objdump' tool:
 *                         objdump -d <obj_file>.o
 * 
 *  NOTE OF C++: As the compilation process is needed it differs because of different compiler tools,
 *  for instance, the change of gcc to g++
*/  


int main(int argc, char** argv)
{
    int data[5] = {2, 4, 8, 1, 10};
    int sum_all = sum(data, 5);
    sum_type_t data_type = type_sum(sum);

    return 0;
}