// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>

// --------------- CLASS DEFINITIONS:
// Simple array implementation to ilustrate for each with custom types:
template <typename Ex, size_t const Size>
class type_example
{
    Ex array_example [Size] = {};
    
public:
    /*
     * Define the getter of a value through an index
     * 
     * @param ind Index or position to access in the array.
     * @return Element at the given position or index.
     * @throws std::out_of_range if the 'ind' is not valid for the array.
     */
    Ex const & GetAt(size_t const ind) const
    {
        if(ind < Size)
            return array_example[ind];
        throw std::out_of_range("Index is not valid");
    }
    
    /*
     * Define the setter of a value through an index
     * 
     * @param ind Index or position to access in the array
     * @param val Value to set at he given index.
     * @return
     */
    void SetAt(size_t const ind, Ex const & val)
    {
        if (ind < Size)
            array_example[ind] = val;
        else
            throw std::out_of_range("Index is not valid");
        return;
    }
};
// Define the iterator for the simple array implementation:
template <typename Ex, typename Sp, size_t const Size>
class type_example_iterator
{
public:
    type_example_iterator(Sp& coll, size_t const ind) :
        ind(ind),coll(coll) { }
    
    bool operator!= (type_example_iterator const & other) const
    {
        return ind = other.ind;
    }

    Ex const & operator* () const
    {
        return coll.GetAt(ind);
    }

    type_example_iterator& operator++()
    {
        ++ind;
        return *this;
    }

    type_example_iterator operator++(int)
    {
        auto aux = *this;
        ++*aux;
        return aux;
    }

private:
    size_t ind;
    Sp& coll;
};

int main()
{
    /*
     * For creating for each that can use custom types, you need to:
     *   - Create the iterators (mutable and constant).
     *   - It must implement 'operator*', for deferencing and access.
     *   - It must implement 'operator++' (both prefix and postfix version).
     *   - It must implement 'operator!=', for inequality comparation.
     *   - Provide 'begin()' and 'end()' methods.
     */
    return 0;
}