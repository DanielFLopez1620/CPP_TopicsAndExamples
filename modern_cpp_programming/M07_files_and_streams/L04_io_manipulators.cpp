// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * You know that the operators >> and << allow input/output streams by
 * considering strings. However, they are not limited to this and can use
 * manipulators to format the output to the console.
 * 
 * The manipulators can affect a field (like setw) or a full stream, by
 * considering arguments (width, setprecision...) or not (like boolapha, dec,
 * hex, oct...) that are possible as the operator<< has overloads with 
 * pointers to these functions.
 * 
 * They can be combined to generate more complex output formats,for example,
 * when you want to achieve a index from a book in a ordered way.
 */


// --------------------- REQUIERED LIBRARIES ----------------------------------
#include <ios>      // Input/Output stream library
#include <iomanip>  // Input/output stream manipulators
#include <vector>   // 

// -------------------- STRUCTS CONSIDERED -----------------------------------
struct Element
{
    int id;
    std::string name;
    int minutes;
};

struct Group
{
    std::string name;
    std::vector<Element> elements;
};

struct DisplayGroup
{
    std::string name;
    std::vector<Group> groups;
};

// ------------------------- FUNCTION PROTOTYPES ------------------------------
void display_organized_group(DisplayGroup display_group);

// --------------------- MAIN IMPLEMENTATION ----------------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 4: String and stream manipulators...\n " << std::endl;

    // Info #1: Tired of using the ternary operator to display 'false' or 
    // 'true' when using booleans, say no more to that and start using
    // 'std::boolalpha' and 'std::noboolalpha'.
    std::cout << "Testing boolalpha for diplaying booleans: " << std::endl
              << std::boolalpha << "\tIs Pluto a planet? " << false << std::endl
              << std::noboolalpha << "\tIs Pluto a planet? " << false 
              << std::endl;
    
    // Info #2: You can use alligment 'left', 'right' and 'internal' to affect
    // the filling of the characters. Where std::setw changes the width of the
    // input or field (default is 0) and width refers to the witd.
    std::cout << "Using aligment with left/right (width of 20): " << std::endl;
    std::cout.width(20); std::cout<< std::right << "  On your right" << std::endl;
    std::cout.width(20); std::cout << std::left << std::setw(20) << 
        "  On your left" << std::endl;

    // Info #3: You can also modify the numeric format to adapt it in a fixed,
    // scientific or hexfloat format.
    float dan_flt = 1.62;
    std::cout << "Testing number formats for floats: " << std::endl
              << "\tFixed: " << std::fixed << dan_flt << std::endl
              << "\tScientific: " << std::scientific << dan_flt << std::endl
              << "\tHexfloat: " << std::hexfloat << dan_flt << std::endl
              << "\tDefault: " << std::defaultfloat << dan_flt << std::endl;
    
    // Info #4: You can also control the integer type for display
    int dan_int = 1620;
    std::cout << "Testing integer types for display: " << std::endl
              << "\tOct:"  << std::oct << dan_int << std::endl
              << "\tHex: " << std::hex << dan_int << std::endl
              << "\tDec: " << std::dec << dan_int << std::endl;
    
    // Info #5: You can make indexes and patterns to fill a word if it is
    // not long enough, with points or the character of your preference.
    std::cout << "Filling content and make spaces: " << std::endl
              << "\t" << std::right << std::setfill('-') << std::setw(20)
              << "Fill right" << std::endl;

    // Info #6: If you want a certain precision (number of decimal units)
    // you can use std::setprecision().
    std::cout << "Using different precisions with floats: " << std::endl
              << "\tNumber: " << dan_flt << std::endl << "\t2 precision: "
              << std::fixed << std::setprecision(dan_flt) << std::endl;
    
    // Info #7: A Display example
    std::cout << "\nLet's check a formatted example" << std::endl;

    auto starwars_group = DisplayGroup
    {
        "Star Wars Collection",
        {
            {
                "Movies",
                {
                    {1, "The Phantom Menace", 2 * 60 + 17},
                    {2, "Attack of the Clones", 2 * 60 + 23},
                    {3, "Revenge of the Sith", 2 * 60 + 21},
                    {4, "A New Hope", 2 * 60 + 5},
                    {5, "The Empires Strike Back", 2 * 60 + 8},
                    {6, "The Return of the Jedi", 2 * 60 + 16},
                },
            },
            {
                "Series",
                {
                    {1, "Star Wars: The Clone Wars", 54 * 60 + 21},
                    {2, "Star Wars: Rebels", 28 * 60 + 21},
                    {3, "The Mandalorian", 16 * 60 + 39},
                    {4, "The Bad Batch", 14 * 60 + 53},
                    {5, "Ahsoka", 5 * 60 + 53},
                    {6, "The Book of Boba Fett", 5 * 60 + 28},
                }
            }
        }
    };
    display_organized_group(starwars_group);

    return 0;

} // main()

// ------------------------------- FUNCTION DEFINITIONS -----------------------
/**
 * Display format for a collection of elements that has a duration and are
 * correlated.
 * 
 * @param display_group Custom struct with general group, groups and elements.
 */
void display_organized_group(DisplayGroup display_group)
{
    std::cout << "Section: " << display_group.name << std::endl;
    for (auto const & group : display_group.groups)
    {
        std::cout << std::left << std::setw(15) << std::setfill(' ')
                  << group.name << std::endl;
        std::cout << std::left << std::setw(15) << std::setfill('-')
                  << "-" << std::endl;

        for(auto const & element : group.elements)
        {
            std::cout << std::right << std::setw(4) << std::setfill(' ')
                      << element.id << " ";
            std::cout << std::left << std::setw(35) << std::setfill('_')
                      << element.name;
            std::cout << std::right << std::setw(8) << std::setfill('_')
                      << element.minutes << " min." << std::endl;
        }
    }
}