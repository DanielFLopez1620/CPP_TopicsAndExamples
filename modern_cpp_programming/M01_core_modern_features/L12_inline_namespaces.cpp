// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * The 'inline' command introduced a new type of namespace that makes 
 * declarations from a nested namespace look and act as if they were
 * part of the sorrounding namespace.
 * 
 * When ready, you can compile and run this code with:
 * 
 *      g++ -std=c++20 L12_inline_namespaces.cpp -o inline.out
 *      ./inline.out
*/

// ------------------------- CLASS AND STRUCTS DECLARATION --------------------


// Info #1: Using inline members allow to use nested namespaces that
// are available automatically as if the were mebers of the enclosing
// namespace. It structure is simple:
//
//      namespace outer {
//          inline namespace inner {
//              // Declarations
//          }
//      }
// It can be used for library versioning.
// Let's see an example with a simple library that displays the version:
namespace custom_library
{
    // First inner definition
    #ifndef LIB_V1
    inline namespace v_1
    {
        template<typename T>
        std::string version(T value) { return "v_1"; }
    } // namespace v_1
    #endif

    // Second inner definition
    #ifndef LIB_V1
    inline namespace v_2
    {
        template<typename T>
        std::string version(T value) { return "v_2"; }
    } // namespace v_2
    #endif
    
} // namespace custom_library

// Info #2: Bu tit can be also used to leave a default version of a library,
// as follows:
namespace my_geo
{
    inline namespace two_d
    {
        struct Point
        {
            float x;
            float y;
        };

        void display_point(const Point& point)
        {
            std::cout << "2D point ( " << point.x <<" ," << point.y << ") "
                      << std::endl; 
        }
    }
    
    namespace three_d
    {
        struct Point
        {
            float x;
            float y;
            float z;
        };

        void display_point(const Point& point)
        {
            std::cout << "3D point ( " << point.x <<" ," << point.y << " , "
                      << point.z << " ) " << std::endl; 
        }
    }
}// my_geo


// -------------------- MAIN IMPLEMENTATION -----------------------------------
int main(int argc, char* argv[])
{
    // Testing custom library
    std::cout << "Let's try to print the versions of the custom library using"
              << "the namespaces required." << std::endl
              << "\t custom_library::version(): Improper, there are 2 inlines." 
              << std::endl << "\t custom_library::v_1::version(): " 
              << custom_library::v_1::version(1) << std::endl
              << "\t custom_library::v_2::version(): "
              << custom_library::v_2::version(1) << std::endl;

    // Testing point library
    my_geo::Point first_point;
    first_point.x = 1.0;
    first_point.y = 0.5;
    my_geo::three_d::Point second_point;
    second_point.x = 1.6;
    second_point.y = 0.5;
    second_point.z = 2.0;
    std::cout << std::endl << "Testing points: " << std::endl << "\t1° Point: ";
    my_geo::display_point(first_point);
    std::cout << "\t2° Point: ";
    my_geo::three_d::display_point(second_point);


    

    return 0;

} // main