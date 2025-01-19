// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You can also give format when working with money in a program. For this we
 * will take advantage of the locales regions configuration and the library
 * <iomanip>.
 * 
 * The focus is oriented to 'put_money()' and 'get_money()' that uses the
 * 'std::money_put()' and 'std::money_get()' facets to parse monetary values
 * when the formatting is asked. They only work with 'long double' and
 * 'std::basic_string' types, but the types are stored as integers in the way
 * of the smallest denomitation of the currency defined in the certain locale,
 * for example, $100.00 is stored as 10000 because the minimum unit is the
 * cent.
 * 
 * When ready, you can compile and run this code with:
 * 
 *      g++ -std=c++17 L05_currency_manip.cpp -o cur_manip.out
 *      ./cur_manip.out
 */

// ---------------------------- REQUIRED LIBRARIES ---------------------------
#include <iomanip>  // I/O Stream Manipulators
#include <locale>   // Localization settings according a region.
#include <sstream>  // Related with string streams 

// ---------------------------- MAIN IMPLEMENTATION -------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 5: Currency stream manipulators...\n" << std::endl;

    // Info #1: You can display the format by considering a localization, then
    // using 'imbue' and 'std::put_money'. Something similar is present in the
    // previous lesson. 
    std::cout.imbue(std::locale("de_DE.utf8"));
    long double my_money_num = 1620.16;
    std::string my_money_str = "1620.16";
    std::cout << "Using certain country currency (Germany / Euro): " << std::endl
              << "\tNumeric: " << std::showbase << std::put_money(my_money_num)
              << std::endl << "\tString: " << std::showbase 
              << std::put_money(my_money_str) << std::endl << "\tGBP value:"
              << std::showbase << std::put_money(my_money_num, true)
              << std::endl;

    // Info #2: You can also read input streams with a monetary format, you
    // require to set the desired locale and then read the info.
    std::istringstream passed_currency("$162.10 162.10 USD");
    passed_currency.imbue(std::locale("en_US.utf8"));
    long double given_money_num;
    std::string given_money_str;
    passed_currency >> std::get_money(given_money_num) 
                    >> std::get_money(given_money_str);
    std::cout.imbue(std::locale("en_US.utf8"));
    std::cout << "Reading money from input streams: " << std::endl
              << "\tOriginal string: " << std::quoted(passed_currency.str())
              << std::endl << "\tValue 1: " << std::put_money(given_money_num) 
              << std::endl << "\tValue 2: " << std::put_money(given_money_str) 
              << std::endl;

    return 0;

} // main()