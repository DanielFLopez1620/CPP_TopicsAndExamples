// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>

// --------------- CLASS DEFINITIONS:
// 1) Simple array implementation to ilustrate for each with custom types:
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
// 2) Define the iterator for the simple array implementation:
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

// 3) Define alias templates for mutable and constant iterators.
template <typename Ex, size_t const Size>
    using type_example_it = type_example_iterator <Ex, type_example<Ex, Size>, Size>;

template <typename Ex, size_t const Size>
    using type_example_cte_it = type_example_iterator <Ex, type_example<Ex, Size> const, Size>;

// 4) Create methods for 'begin()' and 'end()' for both templates
template <typename Ex, size_t const Size>
    inline type_example_it <Ex, Size> begin (type_example<Ex, Size>& coll)
    {
        return type_example_it<Ex, Size> (coll, 0);
    }

template <typename Ex, size_t const Size>
    inline type_example_it <Ex, Size> end (type_example<Ex, Size>& coll)
    {
        return type_example_it<Ex, Size> (coll, coll.GetSize());
    }

template <typename Ex, size_t const Size>
    inline type_example_cte_it <Ex, Size> begin (type_example<Ex, Size>& coll)
    {
        return type_example_cte_it<Ex, Size> (coll, 0);
    }

template <typename Ex, size_t const Size>
    inline type_example_cte_it <Ex, Size> end (type_example<Ex, Size>& coll)
    {
        return type_example_cte_it<Ex, Size> (coll, coll.GetSize());
    }

// 5) Display elements of the array.
template <typename Ex, const size_t Size>
void display_array (type_example<Ex, Size> const & array_example)
{
    for(auto && a : array_example)
        std::cout << e << std::endl;
}

int main()
{
    std::cout << "Module 01 - Lesson 10" << std::endl;
    std::cout << "Using 'for each' with custom Types... " << std::endl;
    
    /*
     * For creating for each that can use custom types, you need to:
     *   - Create the iterators (mutable and constant).
     *   - It must implement 'operator*', for deferencing and access.
     *   - It must implement 'operator++' (both prefix and postfix version).
     *   - It must implement 'operator!=', for inequality comparation.
     *   - Provide 'begin()' and 'end()' methods.
     *  
     * Please refer to class and templates definition to review the steps.
     */
    
    return 0;
}