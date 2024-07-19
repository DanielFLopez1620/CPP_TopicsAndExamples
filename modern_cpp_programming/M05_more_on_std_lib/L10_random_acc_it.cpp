// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasm't tested for C++20

#include <iostream>

/**
 * During some lessons we have explored the power of iterators, like when we
 * implemented our own for each, or using free begin() and end() functions to
 * return iterators to the first and one-past-the-last element of you own
 * container implementation (module 1 about core modern features).
 * 
 * Our focus here, will be to create the implementation of a random-access
 * iterator that meets all the requirements. But do you know enough of iterators?
 * 
 * Well... an iterator is a object with the ability to iterate through the 
 * elements of the range it was pointed originally (just to an element) and has
 * the implementation of increment (++) and deferencing (*). But we have some 
 * types:
 * 
 * - Pointer: The most basic iterator.
 * - Input/Output: The most limited, as they can just perform sequential single
 *   pass input or output operations.
 * - Forward: They can have the functionaly of both input/output iterators, but
 *   the iteration can only happen forward (all containers support this it.)
 * - Bidirectional: They are like forward iteratros that can also go 
 *   backwards.
 * - Random-access: They are like bidirectional iterators with the ability to
 *   access ranges non-sequentially
 * 
 * For more information on iterators go an check:
 *      https://cplusplus.com/reference/iterator/
 */

#include <iterator>
#include <cassert>
#include <memory>
#include <algorithm>

// Info #1: For creating your own random access iterator, you should have a 
// custom implementation of a container, here we have the implementation for a
// custom array class, that initially just have defined the operations for
// initialize, and get the size and elements. 
template <typename Type, size_t const SIZE>
class custom_array
{
    // Data definition
    Type data[SIZE] = {};
public:

    /**
     * Getter of the element at the given index.
     * 
     * @param index Index in array of interest
     * 
     * @return Element present in the given index
     * 
     * @throw std::out_of_range if index is not in range.
     */
    Type& operator[] (size_t const index)
    {
        if (index < SIZE) return data[index];
        throw std::out_of_range("Index out of bounds");
    }

    /**
     * Getter of the element at the given index.
     * 
     * @param index Index in array of interest
     * 
     * @return Element present in the given index
     * 
     * @throw std::out_of_range if index is not in range.
     */
    Type const & operator[](size_t const index) const
    {
        if(index < SIZE) return data[index];
        throw std::out_of_range("Index out of bounds");
    }

    /**
     * Getter of the size of the array.
     * 
     * @return Get size (in terms of variables stored inside).
     */
    size_t size() const { return SIZE; }
};

template <typename T, size_t const Size>
class custom_array_iterator
{
public:
    typedef custom_array_iterator iter_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::random_access_iterator_tag iter_category;
    typedef ptrdiff_t difference_type;

private:
    pointer ptr = nullptr;
    size_t index = 0;

    bool compatible(iter_type const & other) const
    {
        return ptr == other.ptr;
    }

public:
    explicit custom_array_iterator(pointer ptr, size_t const index)
        : ptr(ptr), index(index) {}

    custom_array_iterator(custom_array_iterator const & o)
        = default;

    custom_array_iterator& operator=(custom_array_iterator const & o)
        = default;

    iter_type & operator++()
    {
        if (index >= Size)
            throw std::out_of_range("Iter cannot be incremented, end reached");
        ++index;
        return *this;
    }

    iter_type operator++ (int)
    {
        iter_type tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator== (iter_type const & other) const
    {
        assert(compatible(other));
        return index == other.index;
    }

    bool operator!= (iter_type const & other) const
    {
        return !(*this == other);
    }

    reference operator* () const
    {
        if (ptr == nullptr)
            throw std::bad_function_call();
        return *(ptr + index)
    }

    reference operator-> () const
    {
        if (ptr == nullptr)
            throw std::bad_function_call();
        return *(ptr + index);
    }

    custom_array_iterator() = default;

    iter_type & operator--()
    {
        if (index <= 0)
            throw std::out_of_range("Iter cannot be decremented, begin reached");
        
        --index;
        return *this;
    }

    iter_type operator--(int)
    {
        iter_type tmp = *this;
        --*this;
        return tmp;
    }

    iter_type operator+(difference_type offset) const
    {
        iter_type tmp = *this;
        return tmp += offset;
    }

    iter_type operator-(difference_type offset) const
    {
        iter_type tmp = *this;
        return tmp -= offset;
    }

    difference_type operator-(iter_type const & other) const
    {
        assert(compatible(other));
        return (index - other.index);
    }

    difference_type operator<(iter_type const & other) const
    {
        assert(compatible(other));
        return index < other.index;
    }

    
};