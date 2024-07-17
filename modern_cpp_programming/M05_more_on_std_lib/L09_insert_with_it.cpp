// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * We have checked insert operations at the beginning and at the end, but you
 * haven't realized that we used iterators. But, be careful when using iterators
 * directly as you  cannot use a simple iterator like the one you obtain with 
 * begin(), as you want because you can will overwrite some of the elements 
 * when you want to insert the elements. 
 * 
 * For this purpose, we will check the utilities provided by the <iterator>
 * and <algorithm> header. Keep in mind, that when you include <algorithm> you
 * are also including <iterator>.
 */

// -------------------------------- REQUIRED HEADERS --------------------------

#include <vector>     // For using dynamic arrays (containers)
#include <list> 
#include <algorithm>  // Collection of general purpose functionalities

// -------------------------------- FUNCTION PROTOTYPES -----------------------
template <typename T>
void display_content(std::vector<T> vector);

int main(int argc, char* argv[])
{
    std::cout << "Lesson 9: Inserting element in a range:\n" << std::endl;
    
    // Info #1: You can use std::back_inserter() to insert elements at the end,
    // it is possible to combine it with other forms of filling like what we 
    // saw in the Lesson 7 and Lesson 8.
    std::vector<float> vec_flt1 {16.20, 20.16};
    std::cout << "Inserting elements at the end: " << std::endl
              << "\tOriginal vector: (";
    display_content(vec_flt1);
    std::cout << ")" << std::endl << "Modified vector: (";
    std::fill_n(std::back_inserter(vec_flt1), 2, 3.1416);

    
    // Info #2: As you can suppose, if you can insert at the back... you can
    // insert at the front, this is possible with std::front inserter.
    std::list<float> list_flt2 {3.4, 4.5, 5.6};
    std::cout << "Inserting elements at the end: " << std::endl
              << "\tOriginal list: (";
    // display_content(list_flt2);
    std::cout << ")" << std::endl << "Modified vector: (";
    std::fill_n(std::front_inserter(list_flt2), 2, 2.3);
    

    // Info #3: If you want to insert in a different position of the end
    // or the beginning, you can simply use std::inserter() and specify the
    // position of interest. 
    std::vector<float> vec_flt3 {3.1416, 2.71, 1.664, 1.5716};
    std::cout << "Inserting elements at the end: " << std::endl
              << "\tOriginal vector: (";
    display_content(vec_flt3);
    std::cout << ")" << std::endl << "Modified vector: (";
    std::fill_n(std::inserter(vec_flt3, vec_flt3.begin() + 2), 2, 0);
    

    return 0;
}

// ------------------------------- FUNCTION DEFINITION ------------------------

/**
 * Generic displayer of the elements of the given container. 
 * 
 * @param vector Generic vector of interest
 */
template <typename T>
void display_content(std::vector<T> vector)
{
    for( const auto& element : vector )
    {
        std::cout << element << ", ";
    }
} // display_content