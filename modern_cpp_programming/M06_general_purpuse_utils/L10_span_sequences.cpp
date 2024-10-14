// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * In the module 2 we explored about std::string_view as an option for 
 * considering a string based on the contiguous sequences of characters,
 * this was added in C++17. But it is just one of the cases that could be used
 * with contiguous sequences, and that is the reason why C++20 came with
 * std::span as it allows to acess contiguous sequences of objects.
 * 
 * You will require the <span> header.
 * 
 * This aims to change the C-like interfaces of:
 *      
 *      void func(int* buffer, size_t length) { ... }
 *
 * With the option below:
 * 
 *      void func(std::span<int> buffer) { ... }
 * 
 * Do not mix up that std::span is a containter of objects, rather a 
 * lightweight wrapper that defines a view of a contiguous sequence of objects.
 * It can be used with std::vector, std::array, T[] or T*, but not with
 * std::list, std::map and std::set.
 *  
 * It size can be defined at run-time or compile-time, therefore having dynamic
 * or static extents. And they have the following members.
 * 
 * - begin(), end(), cbegin(), cend() : Access first and last one iterators.
 * - rbegin(), rend(), crbegin(), crend() : Reverse access iterators.
 * - front(), back() :  Accesses the first and last elements.
 * - data() : Return a pointer to the beginning of the sequence.
 * - operator[] : Access the element in the given index.
 * - size(): Return the number of elements in the sequence.
 * - size_bytes() : Return the size in bytes of the sequences.
 * - empyt() : Check if the sequence is empty
 * - first() : To obtain a subspan from the first element to the specified one.
 * - last(): To obtain a subspan from n element to the last.
 * - subspan(): to retrieve a subspan from the n element, to the n + t element.
 * 
 * The objective of a span is to build/create better interfaces that the C-like
 * ones where pointers and sizes where used.
 * 
 * When you are ready, read the code and run it with:
 * 
 *      g++ -std=c++20 L10_span_sequence.cpp -o span.out
 *      ./span.out
 */

// ----------------------- REQUIRED LIBRERIES --------------------------------
#include <span> // Wrapper for memory contiguos structures or containers

// ----------------------- FUNCTION PROTOTYPES --------------------------------
void span_display(std::span<float> buffer);

// ------------------------ MAIN IMPLEMENTATIONS ------------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 10: Usin span for contiguous sequences:\n"
              << std::endl;
    
    // Info #1: You can declare an span based on a vector/array/container
    // in a static way (defined size in compile time) or dynamic way (size is
    // obtained in runtime).
    float num_array[] = { 16.0 , 20.0, 16.20, 20.16};
    std::span <float, 4> stc_extent {num_array};
    std::span <float> dyn_extent {num_array};

    // Info #2: You can combine boht static and dynamic extent span and
    // use then with a for each.
    std::cout << "Using span with for each: " << std::endl
              << "\tStatic extent: (";
    for(auto const n : stc_extent)
    {
        std::cout << n << ", ";
    } 
    std::cout << ")" << std::endl;
    std::cout << "\tdynamic extent: (";
    for(auto const n : dyn_extent)
    {
        std::cout << n << ", ";
    }
    std::cout << ")" << std::endl;

    // Info #3: For accessing the element of a span you can use operator[] (as
    // usual), or the methods front(), back(), data().
    std::cout << "Accessing elements of a span: " << std::endl
              << "\tFirst element: " << stc_extent.front() << std::endl
              << "\tLast element: " << stc_extent.back() << std::endl
              << "\tThird element: " << stc_extent[2] << std::endl;

    // Info #4: You can obtain sub spans when using first(), last() or 
    // subspan() methods.
    std::span<float> first_2 = stc_extent.first(2);
    std::span<float> last_2 = stc_extent.last(2);
    std::span<float> mid_2 = stc_extent.subspan(1,2);
    std::cout << "Displaying subspans: " << std::endl
              << "\tFirst two elements: (";
    span_display(first_2);
    std::cout << ")" << std::endl << "\tLast two elements: (";
    span_display(last_2);
    std::cout << ")" << std::endl << "\tTwo elements from position 1: (";
    span_display(mid_2);
    std::cout << ")" << std::endl; 

    return 0;

} // main()

// -------------------------------- FUNCTION DEFINITIONS ----------------------

/**
 * Displayer based on a for each for span sequences of float type.
 * 
 * @param container Name of span sequences
 */
void span_display(std::span<float> container)
{
   for(auto const element : container)
   {
      std::cout << element << ", ";
   }
} // span_display()