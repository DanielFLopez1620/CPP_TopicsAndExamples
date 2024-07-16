// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * Sorting operation are needed for present, analyse and study data. Moreover,
 * when you use search algorithms some of them use sorting algorithms. Here
 * we will check some alogirthms present in the standard library, and as we 
 * did before, we will mainly use std::vectors but the algorithms presented
 * here can be used with any standard container that is a sequence and has
 * random iterators available.
 * 
 * Before we introduce more topics, let's make clear something, the differences
 * between cbegin()/cend() and begin()/end() when using standard containers.
 * Both are ways for getting iterators to the beginning or the end of a standard
 * container (according the case), but the first ones are read-only iterators
 * while the second ones are mutable iterators, then in the first case you can
 * only read but in the second one you can read and modify them.
 * 
 * The algorithms presented below take random iterators as arguments to define
 * the range to be sorted, and they need the overload of the operator< for the 
 * comparison.
 * 
 * When you are ready, you can use the code with:
 * 
 *      g++ -std=c++20 L06_sort_a_range.cpp -o sort_range.out
 *      ./sort_range.out
 * 
 */

// --------------------------- REQUIRED LIBRARIES -----------------------------
#include <vector>     // For using dynamic containers 
#include <algorithm>  // Contains a collection of general purpose functions
#include <string>     // Related methdos and operations for strings

// ---------------------------- CLASSES AND STRUCT DEFINITIONS ----------------
/**
 * Simple structure oriented to rank the phase of a project.
 */
struct Phase
{
    int order;
    std::string category;
};

// -------------------------------- FUNCTION PROTOTYPES -----------------------

bool operator<(Phase const & lhs, Phase const & rhs);

bool operator>(Phase const & lhs, Phase const & rhs);

std::ostream& operator<<(std::ostream & os, Phase const & element);

template <typename T>
void display_content(std::vector<T> vector);

// -------------------------------- NAMESPACES TO CONSIDER --------------------

using namespace std::string_literals;


int main(int argc, char* argv[])
{
    std::cout << "Lesson 6: Sorting the elements in a range:\n" << std::endl;
    
    // Info #1: You can use std::sort for general sorting standard containers
    // where you can pass an additional argument for a sorting condition 
    // (ascendant or decendant). Then it allows an specified comparison.
    std::vector<int> vec_int1 { 58, 16, 30, 22, 7, 15};
    std::cout << "Base sort of a vector: " << std::endl
              << "\tOriginal vector: (";
    display_content(vec_int1);
    std::cout << ")" << std::endl << "\tSorted vector: (";
    std::sort(vec_int1.begin(), vec_int1.end());
    display_content(vec_int1);
    std::cout << ")" << std::endl << "\tSorted vector (greater): (";
    std::sort(vec_int1.begin(), vec_int1.end(), std::greater<>());
    display_content(vec_int1);
    std::cout << ")" << std::endl;

    // Info #2: If the sort needs to consider equal values and subvalues, you
    // can consider using std::stable_sort(), just remember that the struct
    // or class you use, have to implement the overload of the comparison if
    // it is non-trivial. Remember, the strenght of stable sort is that it
    // guarantees to preserver the original order of the elements that are
    // equal.
    std::vector <Phase> vec_phases
    {
        {5, "Category2"s}, {4, "Category3"s}, {5,"Category1"},
        {1, "Category5"s}, {3, "Category1"s}, {2, "Category2"}, 
    };
    std::cout << "Stable sort that considers equal elements: " << std::endl
              << "\tOriginal custom vector: [";
    display_content(vec_phases);
    std::cout << "]" << std::endl << "\tSorted vector: [";
    std::stable_sort(vec_phases.begin(), vec_phases.end());
    display_content(vec_phases);
    std::cout << "]" << std::endl << "\tSorted vector (greated): [";
    std::stable_sort(vec_phases.begin(), vec_phases.end(), 
        std::greater<>());
    display_content(vec_phases);
    std::cout << "]" << std::endl;

    // Info #3: If it appears the case, where you just need to order a
    // subrange present in a range, you can consider std::partial_sort()
    // if you want to keep the subrange sorted in the original array and
    // std::partial_sort_copy() if you want the sorted subrange copied
    // in another array. This algorithm's args works like the beginning,
    // middle and end of the range, but the middle can be anything. 
    std::vector<int> vec_int2 {20, 22, 15, 17, 16, 30, 1, 10};
    std::cout << "Sorting subranges: " << std::endl << "\tOriginal array: (";
    display_content(vec_int2);
    std::cout << ")" << std::endl << "\tSorted subrange (0 - 4): (";
    std::partial_sort(vec_int2.begin(), vec_int2.begin() + 4, vec_int2.end());
    display_content(vec_int2);
    std::vector<int> vec_int3(vec_int2.size());
    std::partial_sort_copy(vec_int2.begin(), vec_int2.end(), vec_int3.begin(),
        vec_int3.end(), std::greater<>());

    // Info #4: There is a curious way for sorting a n element in the range
    // that ensures it will be the n element ordered while the previous values
    // are less and the later are greater without ensuring they are sorted. It
    // works like a selection algorithm for finding the n^th smallest element.
    std::vector<int> vec_int4 {9, 8, 5, 6, 2, 3, 10};
    std::cout << "Nth element sort: " << std::endl << "\tOriginal vector: (";
    display_content(vec_int4);
    std::cout << ")" << std::endl << "\t2nd Sorted: (";
    std::nth_element(vec_int4.begin(), vec_int4.begin() + 2,vec_int4.end());
    display_content(vec_int4);
    std::cout << ")" << std::endl;

    // Info #5: You can check if an array is sorted (completely or partially) 
    // with std::is_sorted and std::is_sorted_until:
    std::cout << "Checking if the arrays are organized: " << std::endl
              << "\tIs the array ( ";
    display_content(vec_int1);
    std::cout << ") organized ascendent? : " 
              << std::is_sorted(vec_int1.cbegin(), vec_int1.cend()) 
              << std::endl << "\tIs the array (";
    display_content(vec_int2);
    std::cout << ") organized until index?: ";
    auto iter = std::is_sorted_until(vec_int2.cbegin(), vec_int2.cend());
    std::cout << std::distance(vec_int2.cbegin(), iter) << std::endl;

    return 0;

} // main

// ------------------------------- FUNCTION DEFINITIONS -----------------------

/**
 * Overload of comparison less for using sorting algorithms
 * 
 * @param lhs Left element of the comparison
 * @param rhs Right element of the comparison
 * 
 * @return True if the left element is less than the right one, False 
 *         otherwise.
 */
bool operator<(Phase const & lhs, Phase const & rhs)
{
    return lhs.order < rhs.order;
}

/**
 * Overload of comparison greater for using sorting algorithms
 * 
 * @param lhs Left element of the comparison
 * @param rhs Right element of the comparison
 * 
 * @return True if the left element is greater than the right one, False 
 *         otherwise.
 */
bool operator>(Phase const & lhs, Phase const & rhs)
{
    return lhs.order > rhs.order;
}

/**
 * Definition of the operator to display content on the terminal
 * 
 * @param os Ostream configuration to consider
 * @param element Object to display info of attributes
 * 
 * @return Ostream with the content to display
 */
std::ostream& operator<<(std::ostream & os, Phase const & element)
{
    os << "(" << element.order << ", " << element.category << ")";
    return os;
}

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