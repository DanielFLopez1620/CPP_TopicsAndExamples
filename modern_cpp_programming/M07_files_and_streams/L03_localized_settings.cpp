// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * When writitng files you may encounter issues when you use time and settings
 * that depends on the region/nation you are. For this, the C++ I/O comes with
 * locales and facets for general-purpose mecahism for hadling international
 * features.
 * 
 * In this lesson, we are going to show them with std::cout. However, they
 * work with other I/O stream objects. Consider the next steps for the
 * formatting:
 * 
 * 1. Use std::locale to represent the localization settings. The default is
 *    the C locate program. But other options can be POSIX, en_US.utf8 and
 *    more according to your OS.
 *          
 *          auto localization = std::locale {"format"};
 * 
 * 2. Use imbue() method to change the current locale for an I/O stream:
 *          
 *          std::cout.imbue(localization)
 * 
 * Additional considerations:
 * 
 * - To change the default locale you can use:
 * 
 *          std::locale::global(localization)
 * 
 * But... what is a locale object... it is a heterogeneous container of facets,
 * where a facet is an object that defines the localization and
 * internationalization settings. It can has user-define facets but it mostly
 * base on the one that are already define, which considers facets from
 * std::collate<char> to std::message<wchar_t>.
 * 
 * Down below, you can check the usage for money and time facets, which
 * encapsulates all the format for this type of cases.
 * 
 * You can create a locale object from the overloaded constructor or with the
 * 'combine()' method. And you can check if a locale object has a certain facet
 * with the 'std::has_facet()' function.
 * 
 * To compile and execute this code, use:
 * 
 *      g++ -std=c++17 L03_localized_settings.cpp -o loc_sett.out
 *      ./loc_sett.out
 * 
 * NOTE 1: This code may be different if you use Unix system or Windows Systems,
 * for eample, in the case of german, in Unix you have de_DE.utf8 while in
 * Windows you have German_Germany.1252 .
 * 
 * NOTE 2: THis can work for other stream members like cin, cout, cerr and clog
 * (and also the wide versions).
 * 
 */

// --------------------------- REQUIRED LIBRARIES -----------------------------
#include <chrono>    // For time management with different precisions
#include <locale>    // Localization and formats according region
#include <algorithm> // General utility algorithms
#include <iomanip>   // Input/output formatting iwth manipulators

// -------------------------- MAIN IMPLEMENTATION -----------------------------
int main(int argc, char *argv[])
{
    std::cout << "Lesson 3: Use localization based formats" << std::endl;
    
    // Times for testing with appropiate conversion
    auto now = std::chrono::system_clock::now();
    auto system_time = std::chrono::system_clock::to_time_t(now);
    auto local_time = std::localtime(&system_time);
    
    // Vector with different formats
    std::vector<std::string> name_collection
        {"Dan", "Daniel", "Dæniel", "Daçiel", "Däniel"};
    
    // Lambda that considers the location comparison (based on accents)
    auto sort_and_display = [](std::vector<std::string> collection, 
        std::locale const & location)
    {
        std::sort(collection.begin(), collection.end(), location);
        std::cout << "Displaying sorted collection: ";
        for(auto const & name : collection)
        {
            std::cout << name << " ,";
        }
        std::cout << std::endl;
    };

    // Info #1: Using locale to display currency, time and accents in a certain
    // region. 
    auto location = std::locale("de_DE.utf8");
    std::cout.imbue(location);
    std::cout << "German location display settings:" << std::endl
              << "\tCurrency: " << std::put_money(216.20) << std::endl
              << "\tCurrent time: " << std::put_time(local_time, "%c")
              << std::endl << "\tNames: ";
    sort_and_display(name_collection, location);
    std::cout << std::endl;

    auto location2 = std::locale::classic();
    std::cout.imbue(location2);
    std::cout << "C Standard display settings:" << std::endl
              << "\tCurrency: " << std::put_money(216.20) << std::endl
              << "\tCurrent time: " << std::put_time(local_time, "%c")
              << std::endl << "\tNames: ";
    sort_and_display(name_collection, location);
    std::cout << std::endl;
    return 0;

} // main()