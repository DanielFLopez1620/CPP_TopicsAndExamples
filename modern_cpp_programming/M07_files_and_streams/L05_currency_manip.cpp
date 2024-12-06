// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You can also give format when working with money in a program. For this we
 * will take advantage of the locales regions configuration and the library
 * <iomanip>.
 * 
 * 
 */

#include <iomanip>
#include <locale>

int main(int argc, char* argv[])
{
    std::cout.imbue(std::locale("de_DE.utf8"));

    long double my_money_num = 1620.16;
    std::string my_money_str = "1620.16";

    std::cout << "Using certain country currency: " << std::endl 
              << "\tNumeric: " << std::showbase << std::put_money(my_money_num)
              << std::endl << "\tString: " << std::showbase 
              << std::put_money(my_money_str) << std::endl;

    return 0;
}