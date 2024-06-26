// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * To give more details, the '#' symbol we used for the defintions and
 * conditions presented in the previous lesson, is called 'stringizing
 * operator'. But we have the operand '##' too, that is called 'token-pasting',
 * 'merging' or 'concatenating operator'. 
 * 
 * Here we will check more forms of definitions that can be considered with
 * the preprocesor.
 * 
 * You can execute the code with:
 * 
 *      g++ -std=c++17 L02_indirection_pattern.cpp -o ind_pat.out
 *      ./ind_pat.out
 * 
*/

// ------------------- MACROS AND DEFINITIONS ---------------------------------

// Info #1: Here we define a macro that expands with the stringizing operator,
// then we expands it with a macro helper:
#define MAKE_WORD2(w)   #w
#define MAKE_WORD(w)    MAKE_WORD2(w)

// Info #2: Here we concatenate two identfiers together, first with a macro
// helper and using it with another macro:
#define CONCATENATE2(x, y)  x##y
#define CONCATENATE(x,y)    CONCATENATE2(x,y)

// Info #3: You can also use the token-pasting operator in macros that factor
// repetitive code, so you can avoid writing the same multiple times. 
#define TYPE_CREATE(x)  TYPE_CREATE2(x)
#define TYPE_CREATE2(x)     x* make##_##x() { \
    std::cout << "Creating new type" << std::endl; \
    return new x(); \
    }
    
// ------------------------ STRUCT AND CLASSES DEFINTIIONS --------------------

struct custom_t1 {};
TYPE_CREATE(custom_t1)

// ------------------------ MAIN IMPLEMENTATION -------------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 2: Indirection patterns for compilation...\n"
              << std::endl;

    // Info #4: Applying stringizing operator with our implementation of
    // MAKE_WORD and MAKE_WORD2
    std::cout << "Using stringizing operator when no string is provided "
              << std::endl;

    std::string text1 { MAKE_WORD(no_string_provieded) };
    std::string text2 { MAKE_WORD2(no_string_provieded) };

    std::cout << "MAKE_WORD: " << text1 << "\nMAKE_WORD2: " << text2 
              << std::endl << "Now let's take a look with a ID defined (1620):" 
              << std::endl;

    #define ID 1620
    std::string text3 { MAKE_WORD(ID) };
    std::string text4 { MAKE_WORD2(ID) };

    std::cout << "MAKE_WORD: " << text3 << "\nMAKE_WORD2: " << text4 << std::endl;

    // Info #5: Applying concatenation operator previously defined
    std::string text5 { CONCATENATE2(1,2) };
    std::cout << std::endl << "Concatenating macro of undefined 1 and 2: " 
              << text5 << std::endl << std::endl;

    // Avoiding repetitive code
    auto cust1 = make_custom_t1();
    delete cust1;

    return 0;

} // main