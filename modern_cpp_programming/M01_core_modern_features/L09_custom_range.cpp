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
 * 
 * Check the multiple implementations required, and when you are ready, you can
 * execute and run the code with: 
 * 
 *      g++ -std=c++20 L09_custom_range.cpp -o cus_ran.out
 *      ./cus_ran.out
 *      
*/

// Info #1: First, we need to create our iterable class, it can be an array,
// a vector, a map, or any similar, but it must have a getter of the element at
// the given position, a seter of the element at the given position and a
// getter of the size.

/**
 * Demo array for implementing an iteration with a for each loop in C++.
*/
template <typename T, size_t const Size>
class demo_array
{
    // Base declaration of array with fixed size
    T data[Size] = {};

public:
    /**
     * Getter of the element at the given position.
     * 
     * @param idx Position of the element of interest.
    */
    T const & GetAt(size_t const idx) const
    {
        // Return element if it is in the range, otherwise an exception
        if (idx < Size) return data[idx];
        throw std::out_of_range("Index is out of range");
    }

    /**
     * Setter of the element at the given position.
     * 
     * @param idx Position to set the element.
     * @param value Value to change.
    */
    void setAt(size_t const idx, T const & value)
    {
        if(idx < Size) data[idx] = value;
        else throw std::out_of_range("Index is out of range");
    }

    /**
     * Getter of the size of the array.
    */
    size_t GetSize() const { return Size; }
};

// Info #2: Then we will have to create a iterator base class (later we will
// define a mutable and a constant types), that has an implementation of the 
// required operators (++ increasing one, * deferencing and != inequality).

/**
 * Demo iterator types template for the demo array.
*/
template <typename T, typename C, size_t const Size>
class demo_array_iterator_type
{
public:
    // Type constructor that considers an element and an index.
    demo_array_iterator_type(C& collection, size_t const index) :
        index(index), collection(collection) { }
    
    /**
     * Inequality operator to check end of iteration.
     * 
     * @param other Pointer to other element to check if they are different.
    */
    bool operator!= (demo_array_iterator_type const & other) const
    {
        return index != other.index;
    }

    /**
     * Pointer to define and consider elements at the current index.
     * 
     * @return Pointer to directo of the current element.
    */
    T const & operator* () const
    {
        return collection.GetAt(index);
    }

    /**
     * Sum to increment index of element and iterate.
     * 
     * @return Element of the incremented index.
    */
    demo_array_iterator_type& operator++()
    {
        ++index;
        return *this;
    }

    /**
     * Sum to increment current element.
     * 
     * @return Increment of 2 of the element stored in the position
    */
    demo_array_iterator_type operator++(int)
    {
        auto temp = *this;
        ++*temp;
        return temp;
    }
private:
    // Current index
    size_t index;

    // Demo array iterator type
    C& collection;
};

// Info #3: Defining the mutable and const iterators for the range 
// implementations.

/**
 * Definition of variable iterator for a demo array
*/
template <typename T, size_t const Size>
using demo_array_iterator = demo_array_iterator_type<T, 
    demo_array<T, Size>, Size>;

/**
 * Definition of a constant iterator for a demo array
*/
template <typename T, size_t const Size>
using demo_array_const_iterator = demo_array_iterator_type <T, 
    demo_array<T, Size> const, Size>;

// Info #4: Provide begin and end functions for the iterators to know about
// the elements at the start and the end of the array. It must be implemented
// for the mutable and const iterators.

/**
 * Define a begin for iterators of the type demo array, as it will return the
 * first element of the array.
 * 
 * @param collection Demo array with a given type and size.
 * 
 * @return Element at the beginning of the array
*/
template <typename T, size_t const Size>
inline demo_array_iterator<T, Size> begin(
    demo_array<T, Size>& collection)
{
    return demo_array_iterator<T, Size>(collection, 0);
}

/**
 * Define a end for iterators of the type demo array, as it will return the
 * last element of the array.
 * 
 * @param collection Demo array with a given type and size.
 * 
 * @return Element at the end of the array.
*/
template <typename T, size_t const Size>
inline demo_array_iterator<T, Size> end(
    demo_array<T,Size>& collection)
{
    return demo_array_iterator<T, Size>(collection, collection.GetSize());
}

/**
 * Define a begin for iterators of the type demo array, as it will return the
 * first element of the array.
 * 
 * @param collection Const demo array with a given type and size.
 * 
 * @return Element at the beginning of the array
*/
template <typename T, size_t const Size>
inline demo_array_const_iterator<T, Size> begin(
    demo_array<T, Size> const & collection)
{
    return demo_array_const_iterator<T, Size>(collection, 0);
}

/**
 * Define a end for iterators of the type demo array, as it will return the
 * last element of the array.
 * 
 * @param collection Const demo array with a given type and size.
 * 
 * @return Element at the end of the array
*/
template <typename T, size_t const Size>
inline demo_array_const_iterator<T, Size> end(
    demo_array<T, Size> const & collection)
{
    return demo_array_const_iterator<T, Size>(
        collection, collection.GetSize());
}

int main(int argc, char* argv[])
{
    // Instance of a custom float array
    demo_array<float, 4> custom_array;

    // Filling the array
    custom_array.setAt(0, 1.6);
    custom_array.setAt(1, 2.0);
    custom_array.setAt(2, 6.2);
    custom_array.setAt(3, 0.0);

    // Displaying the elements with a for each:
    std::cout << "Elements of custom array: { ";
    for(auto && element : custom_array)
    {
        std::cout << element << " , ";
    }
    std::cout << "}"<<std::endl;
    return 0;
}