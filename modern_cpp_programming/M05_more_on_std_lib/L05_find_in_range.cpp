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
#include <string>

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

using namespace std::string_literals;

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
    // search by considering std::find_if(), also, you can consider the first
    // value that doesn't meet a condition by implementing std::find_if_not().
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
    std::cout << ")" << std::endl << "\tSearch it inside: (";
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

    // Info #4: There is another option of searching in case multiple
    // ocurrences happens, and you need to know the last or more recent one, 
    // for this purpose you can use std::find_end(), applicable for subranges.
    std::vector<char> vec_chr3 {'d', 'x', 'e', 'f', 'd', 'x'};
    std::vector<char> vec_chr4 {'d', 'x'};
    auto iter4 = std::find_end(vec_chr3.cbegin(), vec_chr3.cend(),
        vec_chr4.cbegin(), vec_chr4.cend());
    std::cout << "Searching for last ocurrence of subrange: " << std::endl
              << "\tSequence to search: (";
    display_content(vec_chr3);
    std::cout << ")" << std::endl << "\tSearch it inside: (";
    display_content(vec_chr4);
    std::cout << ")" << std::endl << "\tFound sequence: ";
    if(iter4 != vec_chr3.cend())
    {
        std::cout << *iter4 << "at index: " 
                  << std::distance(vec_chr3.cbegin(), iter4) << std::endl;
    }
    else
    {
        std::cout << "False, not found." << std::endl;
    }

    // Info #5: You can use std::search for searching the first occurrence
    // of a subrange in range. Also, you can use and overload for include
    // searching algorithms, both usages are showcased below:
    auto str1 = "Dan is creating a C++ code"s;
    auto str2 = "C++"s;
    auto iter5 = std::search(str1.cbegin(), str1.cend(),
        str2.cbegin(), str2.cend());
    std::cout << "Searching subranges with std::search" << std::endl
              << "\tOriginal text: " << str1 << std::endl
              << "\tSearching pattern: " << str2 << std::endl
              << "\tPattern found: ";
    if(iter5 != str1.cend())
    {
        std::cout << str2 << " at index " 
                  << std::distance(str1.cbegin(), iter5) << std::endl;
    }
    else
    {
        std::cout << "False, pattern not found." << std::endl;
    }
    std::cout << "\tPattern found with Boyer Moore: ";
    auto iter6 = std::search(str1.cbegin(), str1.cend(), 
        std::boyer_moore_searcher(str2.cbegin(), str2.cend()));
    if(iter6 != str2.cend())
    {
        std::cout << str2 << " at index "
                  << std::distance(str1.cbegin(), iter6) << std::endl;
    }
    else
    {
        std::cout << "False, pattern not found." << std::endl;
    }
    
    // Info #6: If you want to search for adjacent elements that are equal or
    // satisfy the same condition, you can use std::adjacent_find(), if you 
    // do not pass a third arg, it will just search for equal adjacent
    // elements.
    std::vector<int> vec_int2{14, 15, 16, 17, 14, 28, 34, 32, 30, 28};
    auto iter7 = std::adjacent_find(vec_int2.cbegin(), vec_int2.cend(),
        [](int const n1, int const n2){ return n1 % 7 == 0 && n2 % 7 == 0;} );
    
    std::cout << "Searching for equal adjacent elements: " << std::endl
              << "\tSequence to search: (";
    display_content(vec_int2);
    std::cout << ")" << std::endl << "\tFound adjacent factor of 7: ";
    if(iter7 != vec_int2.cend())
    {
        std::cout << *iter7 << " and " << *(iter7+1) << " at index: " 
                  << std::distance(vec_int2.cbegin(), iter7) << std::endl;
    }
    else
    {
        std::cout << "False, not found." << std::endl;
    }
    
    
    return 0;
}