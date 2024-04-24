// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ and clang in C++17

#include <iostream>

/**
 * Compilation is the process where your code is transformed in instructions
 * that the computer can understand, the compiler works over a file sent by the
 * preprocessor.
 * 
 * The first lesson for this process is oriented to conditional compilation,
 * which allows to mantain a single code base but produce different results
 * according the conditions set and the OS. This can be achieved with the 
 * directives: #if, #ifdef, #ifndef, #elif, #else and #endif, which allow to
 * set conditions that will be considered by the preprocessor.
 * 
 * To fully explore this lesson, try with the next commands:
 * 
 *      g++ L01_conditional_compile.cpp -DDEBUG -o cond_comp.out
 *      ./cond_comp.out
 * 
 *      g++ L01_conditional_compile.cpp -DFEATURE -o cond_comp.out
 *      ./cond_comp.out
 * 
 *      clang++ L01_conditional_compile.cpp -DFEATURE -o cond_comp.out
 *      ./cond_comp.out
 * 
 *      clang++ L01_conditional_compile.cpp -DUNIQUE_PRINT -o cond_comp.out
 *      ./cond_comp.out
 * 
 * To better understanding keep in mind the next:
 * 
 * - #if, #ifdef and #ifndef must be completed with a #endif
 * - As the if in your programming experiences, you can use #if with plenty of
 *   #elif, but only one #else.
 * - Conditionals can be nested, but do not forget the constant expression or
 *   definition when using them.
 * - 'defined (<identifier>) cna be used to check if a identifier is defined.
 * - When you provide the flag -D plus the a name, you are creating a definition
 *   that will be cosnidered by the preprocessor.
 * 
 * NOTE: The debug example is only ilustrative, when you want to debug, you
 * will need to proivde the -g flag. But you can indeed add _DEBUG statements
 * to improve the debugging of your code, thatn can be ignored in normal 
 * compilation.
*/

// Info #1: You can include directive definitions, that can be changed with the
// bash that will be replaced for the preprocessor
#define IMPORTANT_DEFINITION
#define ASSIGN_VALUE 2           // cl /DASSIGN_VALUE=2

int main()
{
    // Info #2: Conditional compilations that can be managed with flags in the 
    // call of the compiler, by adding -D + the name of the conditional defintion
    #ifdef DEBUG    // g++ -DDEBUG
        std::cout << "Debugging activated but not implemented..." << std::endl;
    #endif

    // Info #3: You can also use them to create feature flags that are linked with
    // compiler options.
    #ifdef FEATURE  // clang++ -DFEATURE
        std::cout << "Feature was activated... " << std::endl;
    #endif

    // Info #4: Another useful usage is to prevent duplicated definitions (it
    // can also be used).
    #ifndef UNIQUE_PRINT
    #define UNIQUE_PRINT
        std::cout << "Here a unique print..." << std::endl;
    #endif

    // Info #5: You can access the compiler instructions and configure special
    // commands depending on the compiler.
    #if defined _MSC_VER
        std::cout << "You are using visual..." << std::endl;
    #elif defined __clang__
        std::cout << "You are using clang...." << std::endl;
    #elif defined __GNUG__
        std::cout << "You are using gcc......" << std::endl;
    #else
        std::cout << "What compiler are you using for this?" << std::endl;
    #endif

    // Info #6: Even you can access the architecture where you are mounted
    #if defined _M_X64
        std::cout << "Your architecture is AMD64" << std::endl;
    #elif defined _M_IX86
        std::cout << "Your architecture is Intel x86" << std::endl;
    #elif defined _M_ARM
        std::cout << "Your are using ARM" << std::endl;
    #else 
        std::cout << "What architecture are you using then?" << std::endl;
    #endif
    
    return 0;
}  


