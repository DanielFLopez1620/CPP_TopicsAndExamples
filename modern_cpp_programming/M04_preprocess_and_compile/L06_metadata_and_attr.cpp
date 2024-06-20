// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested, oriented C++20.

#include <iostream>

/**
 * C++ is very deficient in the case of intrspection (for language extensions).
 * Then, the compilers have their own way to have extensions, but in C++11
 * the attributes were introduced, and they tell the compiler how to implement
 * certain extensions.
 * 
 * Some of the ones you can find are:
 * 
 * - deprecated: For those caes when an implementation is getting old
 * - nodiscard: To prevent discards of returns
 * - maybe_unused: Just to indicate that it may not be used.
 * - noreturn: A function that doesn't return
 * - carries_depedency: std::memroy_order propagetes in and out the func.
 * - likely: More likely to be executed.
 * - unlikely: Less likely to be executed.
 * - no unique_adress:  Save spece if no type, or resue any padding otherwise.
*/

// Info #1: If you want to make sure a return value isn't discarded, you can use
// [[nodiscard]] attribut. Or even, [[nodiscard(text)]] after C++20 when it comes
// to use a message for better understanding.
/**
 * Non discard result for a getter of a letter.
 * 
 * @return 'd'
 */
[[nodiscard]] int get_letter()
{
    return 'd';
}

// Info #2: Another usage of [[nodiscard]] is related with the case of do not
// ignore certain types of classes or enumerations.
enum class [[nodiscard]] ErrorCode { Success, FileNotFound, InvalidInput };

/**
 * Function that returns error code in case of problems.
 * 
 * @param input Error code to process
 * 
 * @return Equivalent error.
 */
ErrorCode processRead(int input)
{
    if (input < 0)
    {
        std::cout << "Error recieved: Invalid Key..." << std::endl;
        return ErrorCode::InvalidInput;
    }
    return ErrorCode::Success;
}

// Info #3: Have you seen a code get [deprecated]? Well, now you can use the
// attribute and implement it (wisely) in your code when the functionalities
// are going to change in the future. It can be applied to funcs and classes.
/**
 * Deprecated function for getting a zero.
 */
[[deprecated("Use another getter")]] int old_getter()
{
    return 0;
}

// Info #4: You can use [[maybe_unused]] so the compiler doesn't emit a
// warning when a variable isn't used. 
/**
 * Function with three args, but just two are used, then it has an
 * attribute of [maybe_unused].
 */
void strange_display(int a, float b, [[maybe_unused]] char c)
{
    std::cout << "Int: " << a << std::endl
              << "Float: " << b << std::endl
              << "Char: Unused" << std::endl;
}

// Info #5: In case you need to "fall" of a case in a switch, you can use
// [[fallthroug]], to indicate the intentionality of do not break.
/**
 * Void function that consider a switch that has a fallthrog. The swtich
 * only intends to print messages according the integer provided (up to 3).
 * 
 * @param a Option considered
 */
void strange_switch(int a)
{
    switch (a)
    {
    case 1:
        std::cout << "Printing one..." << std::endl;
        [[fallthroug]]
    case 2:
        std::cout << "Printing two..." << std::endl;
        break;
    case 3:
        std::cout << "Printing three..." << std::endl;
        break;
    
    default:
        break;
    }
}


int main(int argc, char* argv[])
{
    std::cout << "Lesson 6: Usage of metadata and attributes for compilation\n"
              << std::endl;
    // No discard instrucction
    std::cout << std::endl << "NO DISCARD ATTRIBUTE: " << std::endl
              << "If you discard the result of the getter, you will have a "
              << " warning, do not forget to experiment with the code."
              << std::endl;
    auto letter = get_letter();
    // get_letter(); // Will return: Ignoring return value declared with
                     // no discard.

    // Usage of certain variables with no discard instruction
    std::cout << std::endl << "ENUMS AND NO DISCARD ATTRIBUTE: " << std::endl
              << "Here the no-dicard is attached directly to the class,"
              << " and it can serve a similar usage to the ones in funcs but"
              << " with results that can be expanded to all the escenarios."
              << "of the class. Now watch, the invalid key case no discarded..." 
              << std::endl;
    auto status = processRead(-1);
    // processRead(-1);

    // Warning of deprecation
    std::cout << std::endl << "DEPRECATION: " << std::endl
              << "Uncomment the function below to watch a warn of a old func"
              << std::endl;
    auto old_num = old_getter();

    // Just not use certain variables
    std::cout << std::endl << "You can prevent a warn of unused variables,"
              << "with attributes. Check the two lines below, as they are"
              << "unused, we can't (well... we shouldn't use them.)"
              << std::endl; 
    [[maybe_unused]] auto word = "Am I ignored?";
    strange_display(1620, 16.20, '1');

    // Falling through a case...
    std::cout << std::endl << "FALLTRHOUGH" << std::endl
              << "In case you have asked, yes, you can use two cases of the"
              << " switch, then use the fallthrough. Check the example: (1)"
              << std::endl;
    strange_switch(1);


    return 0;
}