// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Have you worked with data? Then, should know that searching and finding
 * certain info is a common task, for this reason, the standard library
 * provides many generic algortihms for searching in containers. In this 
 * lesson we will illustrate some of them for any range defined by a begin and
 * past-the-end structured.
 * 
 * Do not forget to import the <algorithm> header.
 */

#include <algorithm>
#include <vector>

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

int main(int argc, char* argv[])
{
    // Info #1: Using std::find for getting an iterator with the value of
    // interest.
    std::vector<float> vec_flt1 {16.20, 20.16, 1.6, 2.0};
    auto iter1 = std::find(vec_flt1.cbegin(), vec_flt1.cend(), 2);
    std::cout << "Using std::find with a floating sequence: " << std::endl
              << "\tSequence: (";
    display_content(vec_flt1);
    std::cout << ")" << std::endl << "\tDesired element found: ";
    if(iter1 != vec_flt1.cend())
    {
        std::cout << *iter1 << std::endl;
    }
    else
    {
        std::cout << "False, not found." << std::endl;
    }

    // Info #2: There is also an option for using lambdas or predicates for the
    // search by considering std::find_if():
    std::vector<int> vec_int1 {26, 27, 28, 29, 30, 31};
    auto iter2 = std::find_if(vec_int1.cbegin(), vec_int1.cend(),
        [](int const n) {return n % 7 == 0; });
    std::cout << "Using a factor with std::find_if: " << std::endl
              << "\tSequence: (";
    display_content(vec_int1);
    std::cout << ")" << std::endl << "\tFactor of seven found: ";
    if(iter2 != vec_int1.cend())
    {
        std::cout << *iter2 << std::endl;
    }
    else
    {
        std::cout << "False, not found." << std::endl;
    }

    // Info #3: You can search for patterns and occurrences with 
    // std::find_first_of(), also you can used std::distance, for better
    // understanding of the index where it was found the coincidence by the
    // iterator:
    std::vector<char> vec_chr1 {'a', 'b', 'c'};
    std::vector<char> vec_chr2 {'b', 'a', 'c', 'a', 'b', 'c', 'd', 'e'};
    auto iter3 = std::find_first_of(vec_chr2.cbegin(), vec_chr2.cend(),
        vec_chr1.cbegin(), vec_chr1.cend());
    std::cout << "Searching for sequences inside a sequence: " << std::endl
              << "\tSequence to search: (";
    display_content(vec_chr1);
    std::cout << ")" << std::endl << "Search it inside: (";
    display_content(vec_chr2);
    std::cout << ")" << std::endl << "\tFound sequence: ";
    if(iter3 != vec_chr2.cend())
    {
        std::cout << *iter3 << "at index: " 
                  << std::distance(vec_chr2.cbegin(), iter3) << std::endl;
    }
    else
    {
        std::cout << "False, not found." << std::endl;
    }

    return 0;
}