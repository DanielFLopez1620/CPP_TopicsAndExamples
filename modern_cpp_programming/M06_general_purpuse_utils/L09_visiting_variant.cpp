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
 * 
 */

#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <iomanip>
#include <chrono>
#include <algorithm>

// For this examples we will use the USB case where it can store a movie, a
// album music and a software. We will create three structs for trelated them.
enum class Genre {Drama, Action, Comedy, Horror};

struct Movie
{
    std::string name;
    std::chrono::minutes duration;
    std::vector<Genre> genre;
};

struct Song
{
    std::string name;
    std::chrono::seconds duration;
};

struct Album
{
    std::string name;
    std::string artist;
    std::vector<Song> songs;
};

struct Software
{
    std::string name;
    std::string company;
};

struct variant_visitor
{
    void operator()(Movie const &arg) const
    {
        std::cout << "Displaying info of movie: " << std::endl
                  << "\tName: " << arg.name << std::endl
                  << "\tDuration: " << arg.duration.count() << " minutes"
                  << std::endl;
    }

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

    void operator()(Software const & arg) const
    {
        std::cout << "Displaying info of Software:" << std::endl
                  << "\tName: " << arg.name << std::endl
                  << "\tCompany: " << arg.company << std::endl;
    }
};

using usb_device = std::variant<Movie, Album, Software>;
using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    std::vector<usb_device> usbs_list
    {
        Movie{ "Star Wars: A new Hop", 2h + 8min, {Genre::Action} },
        Album{ "Evolve", "Imagine Dragons", {{"Believer", 3min + 24s }, {"Thnder", 3min + 7s}}},
        Software{ "Matlab", "Mathworks"}
    };

    std::cout << "Displaying USB elements in store: " << std::endl;
    auto i = 1;
    for (auto const & usb : usbs_list)
    {
        std::cout << "\tElement #" << i << ": ";
        i++;
        std::visit([](auto&& variant)
            {std::cout << variant.name << std::endl; }, usb);
    }

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
                    std::cout << "Displaying info of album: " << std::endl
                              << "\tName:" << arg.name << std::endl
                              << "\tArtist: " << arg.artist << std::endl;
                    int i = 0;
                    for (auto const & song : arg.songs)
                    {
                        std::cout << "\tSong #" << i << std::endl
                                  << "\t\tName: " << song.name << std::endl
                                  << "\t\tDuration: "  << song.duration.count()
                                  << " seconds" << std::endl;
                    }
                }
                else if constexpr (std::is_same_v<T, Software>)
                {
                    std::cout << "Displaying info of Software: " << std::endl
                              << "\tName: " << arg.name << std::endl
                              << "\tCompany: " << arg.company << std::endl;
                }
            },
            usb);
    }

    return 0;
}




