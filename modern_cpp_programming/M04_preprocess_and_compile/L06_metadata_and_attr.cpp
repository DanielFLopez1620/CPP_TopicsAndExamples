// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasn't tested, oriented C++20.

#include <iostream>

/**
 * C++ is very deficient in the case of intrspection (for language extensions).
 * Then, the compilers have their own way to have extensions, but in C++11
 * the attributes were introduced, and they tell the compiler how to implement
 * certain extensions.
*/

// Info #1: If you want to make sure a return value isn't discarded, you can use
// [[nodiscard]] attribut. Or even, [[nodiscard(text)]] after C++20 when it comes
// to use a message for better understanding.
[[nodiscard]] int get_letter()
{
    return 'd';
}

// Info #2: Another usage of [[nodiscard]] is related with the case of do not
// ignore certain types of classes or enumerations.
enum class [[nodiscard]] ErrorCode { Success, FileNotFound, InvalidInput };
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
[[deprecated("Use another getter")]] int old_getter()
{
    return 0;
}


int main(int argc, char* argv[])
{
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

    return 0;
}