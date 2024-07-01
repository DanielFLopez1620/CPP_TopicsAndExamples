// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * The std library have differnt types of containers that can be used in
 * different situations, we have sequence containters like 'vector', 'arays'
 * and 'list',, orderder and unordered containers like 'set' and 'map', and 
 * adapted sequence containers such as 'stack' and 'queue'.
 * 
 * Here we will check more about vector and why it is the most common
 * implementation for containers.
 * 
 * For more info on vector methods, checkout the docs:
 *      https://cplusplus.com/reference/vector/vector/ 
 * 
 * The std::vector is the most similar container to and inter-operable with
 * arrays, it is a variable-sized sequence of element that has a guarantee
 * of storage in contiguous memory whihc allow sa better pass to functions,
 * some of its benefits over arrays are:
 * 
 * - No memory management is required.
 * - Can modify its size.
 * - Allow concatenation and compasison between vectors.
 * - It is compatible with arrays and C-like APIs.
 * - It has faster acccess to the elements (except from std::array).
 * - Has no per-element memory overhead.
 * 
 * As it was mentioned, it has a variable size, this property is defined by
 * the capacity (number of elements that can be accommodate without performing
 * additional memory reallocations) and the size (actual number of elements).
 * In this case, teh sie must be smaller or equal to the capacity, and in case
 * they are equal, some modifications may need to be implemented with the
 * array.
 * 
 * In case you need to free additional reserved memory, consider using the 
 * 'shrink_to_fit' method.
 * 
 * 
 * NOTE: It is not a good idea to store raw pointers in a vector, as it focus
 * aims to store object instance, rather prefer smart pointers.
 * 
 * When ready, you can compile by using:
 *      
 *      g++ - std=c++20 L01_vector_as_dfl.cpp -o vector_dfl.out
 *      ./vector_dfl.out
 *
 */

// --------------------------- REQUIRED HEADERS -------------------------------
#include <vector>  // For using dynamic and improved arrays.
#include <list>    // For using organized lists.

// ---------------------------- FUNCTION DEFINITIONS --------------------------
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

// ---------------------------- MAIN IMPLEMENTATION ---------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 1: Vector as the default container...\n" << std::endl;
    
    // Info #1: Remember that we can have statically or dynamically allocated
    // arrays 
    double sta_d_array[5];             // Statically allocated
    float* dyn_f_array = new float[5]; // Dynamically allocated

    // Info #2: Base definition and initialization of a vector.
    std::cout << "Base initialization of a vector:\n\t (";
    std::vector<double> num_vec1 { 16.20, 20.16, 62.10 };
    for (auto num : num_vec1)
    {
        std::cout << num << ", ";
    }
    std::cout << ")\n" << std::endl;

    // Info #3: You can initialize a vector from an array by considering memory
    // increments or positions:
    std::cout << "Vector from array: " << std::endl;
    char letter_array[] = { 'D', 'a', 'n', '!'};
    std::vector<char> letter_vector1(letter_array, letter_array + 4);
    std::vector<char> letter_vector2(letter_array + 1, letter_array + 3);
    std::cout << "\tBase Char array: ";
    for (auto letter : letter_array)
    {
        std::cout << letter << ", ";
    }
    std::cout << ")\n\tVector initialized with array: (";
    display_content(letter_vector1);
    std::cout << "),\n\tVector initialized with sliced array: (";
    display_content(letter_vector2);
    std::cout << ")" << std::endl;

    // Info #4: You can initialize a vector based on a list, by considering
    // the beginning and the end of that list for creating a sort of a range.
    std::cout << "\nVector from list:\n\tInteger list based: ("; 
    std::list<int> num_list {16, 20, 0, 1620};
    std::vector<int> num_vec2(num_list.begin(), num_list.end());
    display_content(num_vec2);
    std::cout << ")" << std::endl;

    // Info #5: Vectors allow add, remove, insert and related operations
    // for a more dynamic management of them. Consider the next methods:
    // - push_back(a); -> Adds 'a' at the end of the vector.
    // - pop_back() -> Remove the last element of the vector.
    // - insert(a, <init>, <end>) -> Insert anywhere a given slice.
    // - emplace_back(<struct_attr>) -> Add an object at the end of the vector.
    // - emplace(<struct_attr>) -> Add an object anywhere in the vector.
    std::vector<int> num_vec3(5, 1);
    std::cout << "\nVector operations:\n\tOriginal vector: (";
    display_content(num_vec3);
    num_vec3.push_back(16);
    std::cout << ")\n\tVector after pushing back: (";
    display_content(num_vec3);
    num_vec3.pop_back();
    std::cout << ")\n\tVector after poping back: (";
    display_content(num_vec3);
    std::vector<int>::iterator iter;
    iter = num_vec3.begin();
    iter = num_vec3.insert(iter, 32);
    std::cout << ")\n\tVector after insert: (";
    display_content(num_vec3);
    std::cout << ")" << std::endl;

    // Info #6: For modification you can use methods like the operator=,
    // assign(), swap(), clear(), erase(), and many more.
    std::cout << "\nModifying arrays:\n\tOperator=: (";
    std::vector <int> num_vec4 = num_vec3;
    display_content(num_vec4);
    std::cout << ")\n\tAssign: (";
    int num_array[] = {10, 9, 8 , 7};
    std::vector<int> num_vec5;
    num_vec5.assign(num_array, num_array+4);
    display_content(num_vec5);
    std::cout << ")\n\tErase (at 2°): (";
    num_vec5.erase(num_vec5.begin() + 2);
    display_content(num_vec5);
    std::cout << ")\n\tClear: (";
    display_content(num_vec5);
    std::cout << " )" << std::endl;

    // Info #7: You can use pointers with vectors to, for that, you can use
    // the methods for data(), use the ampersand with the front() or begin()
    // method, or use the old but still valid direction of the first element.
    // Check the proper implementations down below:
    int const * ptr2vec1 = num_vec5.data();
    int const * ptr2vec2 = &num_vec5[0];
    int const * ptr2vec3 = &num_vec5.front();
    int const * ptr2vec4 = &*num_vec5.begin();
    std::cout << "\nPointers to num_vec5 checker: " << std::endl
              << "\t1° Pointer: " << ptr2vec1 << std::endl
              << "\t2° Pointer: " << ptr2vec2 << std::endl
              << "\t3° Pointer: " << ptr2vec3 << std::endl
              << "\t4° Pointer: " << ptr2vec4 << std::endl;


    return 0;
}