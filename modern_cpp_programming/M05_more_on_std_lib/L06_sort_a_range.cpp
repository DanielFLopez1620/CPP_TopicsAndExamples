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
 */

#include <vector>
#include <algorithm>
#include <string>

struct Phase
{
    int order;
    std::string category;
};

bool operator<(Phase const & lhs, Phase const & rhs)
{
    return lhs.order < rhs.order;
}

bool operator>(Phase const & lhs, Phase const & rhs)
{
    return lhs.order > rhs.order;
}


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

using namespace std::string_literals;

int main(int argc, char* argv[])
{
    // Info #1: You can use std::sort for general sorting standard containers
    // where you can pass an additional argument for a sorting condition 
    // (ascendant or decendant).
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
    // it is non-trivial.
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
    // in another array.
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
    // are less and the later are greater without ensuring they are sorted.
    std::vector<int> vec_int4 {9, 8, 5, 6, 2, 3, 10};
    std::cout << "Nth element sort: " << std::endl << "\tOriginal vector: (";
    display_content(vec_int4);
    std::cout << ")" << std::endl << "\t2nd Sorted: (";
    std::nth_element(vec_int4.begin(), vec_int4.begin() + 2,vec_int4.end());
    display_content(vec_int4);
    std::cout << ")" << std::endl;




    
    

    return 0;
}