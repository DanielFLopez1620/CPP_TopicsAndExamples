// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * std::variant was based on the boost.variant library and aims for a type-safe
 * union that holds the value of one of its alternatives.
 * 
 * Previously we used the std::variant with POD-types, but they were created
 * for more, then, here our focus will be to use non-polymorphic and non-POD 
 * types to check more complex, real examples.
 * 
 * Do not forget to include the <variant> header.
 * 
 * In this case, we will use visitors which are callable objects (functions,
 * lambdas or function objects) that acepts every type present in a previously
 * defined variant. In the last lesson, we used briefly the std::visit()
 * function, but here we want to showcase more practical examples.
 * 
 * When you visit a variant, keep in mind that the object is invoked with the 
 * current object, then if there is no match the program is ill-formed; a
 * related note here is that if you visit a function object then it must
 * overload its call operator for all the possible alternatives types of the
 * variant, and in the case it is a lamda, the lambda have to be generic. These
 * situations are illustrated in the codes below.
 * 
 * When you are ready, you can compile and run this code with:
 * 
 *      g++ -std=c++20 /L09_visiting_variant.cpp -o vis_var.out
 *      ./vis_var.out
 * 
 */

// -------------------------- REQUIRED HEADERS --------------------------------

#include <variant>     // Required for using type-safe unions
#include <string>      // For string operations and methods
#include <vector>      // Related with dynamic arrays
#include <type_traits> // Related with compile-time information about type
#include <iomanip>     // I/O Manipulatros for customize strings
#include <chrono>      // For time management operation
#include <algorithm>   // General utility algorithms

// ------------------------- STRUCT AND CLASS DEFINITIONS ---------------------

// For this examples we will use the USB case where it can store a movie, a
// album music and a software. We will create three structs for trelated them.
enum class Genre {Drama, Action, Comedy, Horror};

// Movie definition oriented to name, time and vector of genres
struct Movie
{
    std::string name;
    std::chrono::minutes duration;
    std::vector<Genre> genre;
};

// Song definition that considers name and time
struct Song
{
    std::string name;
    std::chrono::seconds duration;
};

// Album definition that considers a name, artist and a collection of songs
struct Album
{
    std::string name;
    std::string artist;
    std::vector<Song> songs;
};

// Software definition that considers name and provider
struct Software
{
    std::string name;
    std::string company;
};

/**
 * Struct definition oriented to assign and discover the type of a given
 * type-safe union (variant) to display the details, by considering the
 * overwrite of the operator().
 */
struct variant_visitor
{
    /**
     * Overwrite operator() that considers a movie passed as an argument
     * to display info of name and duration.
     * 
     * @param arg Movie passed as the value stored by a variant.
     */
    void operator()(Movie const &arg) const
    {
        std::cout << "Displaying info of movie: " << std::endl
                  << "\tName: " << arg.name << std::endl
                  << "\tDuration: " << arg.duration.count() << " minutes"
                  << std::endl;
    }

    /**
     * Overwrite operator() that considers an album passed as an argument
     * to display the name, the artist and the subsequent info of the songs.
     * 
     * @param arg Album passed as the value stored by a variant.
     */
    void operator()(Album const &arg) const
    {
        std::cout << "Displaying info of album: " << std::endl
                  << "\tName: " << arg.name << std::endl
                  << "\tArtist: " << arg.artist << std::endl
                  << "\tList of songs: " << std::endl;
        int i = 1;
        for(auto const & song : arg.songs)
        {
            std::cout << "\t Song #" << i << ":" << std::endl
                      << "\t\tName: " << song.name << std::endl
                      << "\t\tDuration: " << song.duration.count()
                      << std::endl;
        }
    }

    /**
     * Overwrite operator() that considers a software passed as an argument
     * to display the name and its vendor.
     * 
     * @param arg Software passed as the value stored by a variant.
     * 
     */
    void operator()(Software const & arg) const
    {
        std::cout << "Displaying info of Software:" << std::endl
                  << "\tName: " << arg.name << std::endl
                  << "\tCompany: " << arg.company << std::endl;
    }
}; // struct variant_visitor

// ------------------------- NAMESPACE CONSIDERATIONS --------------------------

using usb_device = std::variant<Movie, Album, Software>;
using namespace std::chrono_literals;

// ------------------------- MAIN IMPLEMENTATION ------------------------------
int main(int argc, char* argv[])
{
    // Info #1: Defining a std::vector of variants, each one storing a
    // different type, this is intended to make more trials later on.
    std::vector<usb_device> usbs_list
    {
        Movie{ "Star Wars: A new Hop", 2h + 8min, {Genre::Action} },
        Album{ "Evolve", "Imagine Dragons", 
            {{"Believer", 3min + 24s }, {"Thnder", 3min + 7s}}},
        Software{ "Matlab", "Mathworks"}
    };

    // Info #2: Using the generic lambda with a generic for each to display
    // just the name of the variant elements.
    std::cout << "Displaying USB elements in store: " << std::endl;
    auto i = 1;
    for (auto const & usb : usbs_list)
    {
        std::cout << "\tElement #" << i << ": ";
        i++;
        std::visit([](auto&& variant)
            {std::cout << variant.name << std::endl; }, usb);
    }

    // Info #3: Using a for eah with a generic lambda to obtain the name, but
    // also to convert it to upper case.
    for(auto const & usb : usbs_list)   
    {
        usb_device obtained = std::visit(
            [](auto && arg) -> usb_device 
            {
                auto aux {arg};
                std::transform(aux.name.begin(), aux.name.end(), 
                    aux.name.begin(), [](unsigned char l)
                        {return std::toupper(l); });
                return aux;
            },
            usb);
        std::visit (
            [](auto&& arg) 
            {
                std::cout << arg.name << std::endl;
            },
            obtained);
    }

    // Info #4: Creating a for each for visiting a generic lambda that
    // considers the type of the type-safe union to display the content
    // properly.
    for (auto const & usb : usbs_list)
    {
        std::visit([](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Movie>)
                {
                    std::cout << "Displaying info of movie: " << std::endl
                              << "\tName: " << arg.name << std::endl    
                              << "\tDuration: " << arg.duration.count()
                              <<  " minutes" <<std::endl;
                }
                else if constexpr (std::is_same_v<T,Album>)
                {
                    std::cout << "\tDisplaying info of album: " << std::endl
                              << "\t\tName:" << arg.name << std::endl
                              << "\t\tArtist: " << arg.artist << std::endl;
                    int i = 1;
                    for (auto const & song : arg.songs)
                    {
                        std::cout << "\tSong #" << i << std::endl
                                  << "\t\tName: " << song.name << std::endl
                                  << "\t\tDuration: "  << song.duration.count()
                                  << " seconds" << std::endl;
                        i++;
                    }
                }
                else if constexpr (std::is_same_v<T, Software>)
                {
                    std::cout << "\tDisplaying info of Software: " << std::endl
                              << "\t\tName: " << arg.name << std::endl
                              << "\t\tCompany: " << arg.company << std::endl;
                }
            },
            usb);
    }

    return 0;
} // main()




