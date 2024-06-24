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
 */

#include <vector>
#include <list>

template <typename T>
void display_content(std::vector<T> vector)
{
    for( const auto& element : vector )
    {
        std::cout << element << ", ";
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Lesson 1: Vecotr as the default container...\n" << std::endl;
    
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
    std::cout << ")" << std::endl;

    return 0;
}