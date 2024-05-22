// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * The for each implementation requires a structure that has the presence of a
 * begin() and end() function (as a member or free funcition), then we can
 * create custom types that can be iterated in a for each loop. 
 * 
 * To enable a custom type for using range based loops, the implementation of
 * your type should consider:
 * 
 *  - operator++: Both prefix and suffix for incrementation of iterator.
 *  - operator*: Deferencing and access by using pointers.
 *  - operator!=: Comparation of inequality, in case of end check.
 *  - Also, you must provide free begin and end functions types.
*/

template <typename T, size_t const Size>
class demo_array
{
    T data[Size] = {};
public:
    T const & GetAt(size_t const idx) const
    {
        if (idx < Size) return data[idx];
        throw std::out_of_range("Index is out of range");
    }

    void setAt(size_t const idx, T const & value)
    {
        if(idx < Size) data[idx] = value;
        else throw std::out_of_range("Index is out of range");
    }
    size_t GetSize() const { return Size; }
};  

int main(int argc, char* argv[])
{
    demo_array<float, 4> custom_array;
    custom_array.setAt(0, 1.6);
    custom_array.setAt(1, 2.0);
    custom_array.setAt(2, 6.2);
    custom_array.setAt(3, 0.0);

    std::cout << "Elements of custom array: ";
    for(auto && element : custom_array)
    {
        std::cout << element << " ,";
    }
    std::endl;
    return 0;
}