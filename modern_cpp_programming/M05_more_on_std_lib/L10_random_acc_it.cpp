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
 * 
 * NOTE: Here we have to make an important highlight, it is about rvalues and
 * lvalues. Lvalues represents an object that is present in a location in memory 
 * (you can adress it) while rvalues are temporary objects that do not persist 
 * more than the expression they are used:
 * 
 *      int x = 16; // x is an lvalue
 *      int y = 20; // 20 is an rvalue
 *      
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

    // Info #2: Inside the container of interest, you will need to implement
    // the iterator class, where you have to initially consider defining types
    // for the iterator itself, the value type, the reference, the category
    // access as public definitions.
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

    // Info #3: For the private data you will need to create a pointer (and
    // initialize it to null) and define a start index (at 0).
    private:
        pointer ptr = nullptr;
        size_t index = 0;

        // Info #4: You need imprlement a compatible function to check if it
        // valid to interact between to pointers. 

        /**
         * Validates if both type of iterators are the same to check 
         * compatibility.
         * 
         * @param other Pointer to the other iterator to consider.
         * 
         * @return True if both iterators type are consistent, False otherwise.
         */
        bool compatible(iter_type const & other) const
        {
            return ptr == other.ptr;
        }

    public:
        // Info #5: Do not forget to consider an explicit constructor for the
        // iterator class.

        /**
         * Explicit constructor that defines an iterator by providing the 
         * pointed memory and the initial index.
         * 
         * @param ptr Pointer that points to the start of a container.
         * @param index First value of the index to consider.  
         */        
        explicit custom_array_iterator(pointer ptr, size_t const index)
            : ptr(ptr), index(index) {}

        // Info #6: The next step implies to work with a proper implementation,
        // that meet the requirements of an iterator, then it should consider
        // to implement a copy constructor, a copy assignment, a destruction
        // implementation, a prefix and a post increment.

        /**
         * Default constructor implementation by considering copy
         * 
         * @param o Other iterator that can be used as the base to construct
         *          another.
         */
        custom_array_iterator(custom_array_iterator const & o)
            = default;

        /**
         * Define a copy assignation and set it to default.
         * 
         * @param o Other iterator to use as a copy base for the assignation.
         */
        custom_array_iterator& operator=(custom_array_iterator const & o)
            = default;

        /**
         * Default destructor is used.
         */
        ~custom_array_iterator() = default;

        /**
         * Postincrement implementation for the iteration index.
         * 
         * @return Pointer to the current object.
         * 
         * @throw std::out_of_range if increment is out of bounds
         */
        iter_type & operator++()
        {
            if (index >= Size)
                throw std::out_of_range(
                    "Iter cannot be incremented, end of container reached");
            ++index;
            return *this;
        }

        /**
         * Posincrement implementation of the value considered at the current
         * index of the container.
         * 
         * @param - Integer value considered at increment
         * 
         * @return Pointer to the current iterator.
         */
        iter_type operator++ (int)
        {
            iter_type tmp = *this;
            ++*this;
            return tmp;
        }

        // Info #7: Do not forget that for usages in loops and conditions, the
        // iterator must have equality and inequallity comparison.

        /**
         * Define equaility operator by first considering if both of the
         * elements are compatible and then checking their indexes.
         * 
         * @param other Element to compare equaillity
         * 
         * @return True, if indexes are equal, False otherwise.
         * 
         * @throw Generic exception if elements aren't compatible.
         */
        bool operator== (iter_type const & other) const
        {
            assert(compatible(other));
            return index == other.index;
        }

        /**
         * Define inequaility operator by first considering if both of the
         * elements are compatible and then checking their indexes.
         * 
         * @param other Element to compare equaillity
         * 
         * @return True, if indexes aren't equal, False otherwise.
         * 
         * @throw Generic exception if elements aren't compatible.
         */
        bool operator!= (iter_type const & other) const
        {
            return !(*this == other);
        }

        /**
         * Deferencing operator definition to check the value that the 
         * iterator allows to point. 
         * 
         * @return Value stored in the container at the direction of the iter.
         * 
         * @throw std::bad_function_call if the deferencing isn't proper.
         */
        reference operator* () const
        {
            if (ptr == nullptr)
                throw std::bad_function_call();
            return *(ptr + index);
        }

        /**
         * Operator for accesing to the given elemet at the index specified by
         * the iterator. 
         * 
         * @return Value stored in the container at the direction of the iter.
         * 
         * @throw std::bad_function_call if the access isn't proper.
         */
        reference operator-> () const
        {
            if (ptr == nullptr)
                throw std::bad_function_call();
            return *(ptr + index);
        }

        // Info #8: You have to include a default constructor to meet the
        // forward iterator requirements.
        
        /**
         * Default construction for the iterator.
         */
        custom_array_iterator() = default;

        // Info #9: As we mentioned in the intro, we have to also consider the
        // bidirectional iterator requirements to achieve our random access.  Then,
        // do not forget to add decrement operators.

        /**
         * Postdecrement implementation for the iteration index.
         * 
         * @return Pointer to the current object.
         * 
         * @throw std::out_of_range if increment is out of bounds
         */
        iter_type & operator--()
        {
            if (index <= 0)
                throw std::out_of_range("Iter cannot be decremented, begin reached");
            
            --index;
            return *this;
        }

        /**
         * Posdecrement implementation of the value considered at the current
         * index of the container.
         * 
         * @param - Integer value considered at increment
         * 
         * @return Pointer to the current iterator.
         */
        iter_type operator--(int)
        {
            iter_type tmp = *this;
            --*this;
            return tmp;
        }

        // Info #10: Finally we need to add dependencies oriented to the 
        // random access iterator, for thsi consider add and substract,
        // comparison, compound assignments and offset deference.

        /**
         * Arithmetic add by considering pointed element by the iterator index
         * and the offset of other element.
         *
         * 
         * @param offset Element to consider for the sum.
         * 
         * @return Final sum stored in the original pointer object.
         */
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

        bool operator<(iter_type const & other) const
        {
            assert(compatible(other));
            return index < other.index;
        }

        bool operator>(iter_type const & other) const
        {
            return other < *this;
        }

        bool operator<=(iter_type const & other) const
        {
            return !(other < * this);
        }        

        bool operator>=(iter_type const & other) const
        {
            return !(*this < other);
        }

        iter_type & operator+=(difference_type const offset)
        {
            if(index + offset < 0 || index + offset > Size)
                throw std::out_of_range("Iterator out of bounds");
            index += offset;
            return *this;
        }

        iter_type & operator-=(difference_type const offset)
        {
            return *this += -offset;
        }

        value_type & operator[](difference_type const offset)
        {
            return (*(*this + offset));
        }

        value_type const & operator[](difference_type const offset)
        const
        {
            return (*(*this + offset));
        }

    };

    typedef custom_array_iterator<Type, SIZE> iterator;
    typedef custom_array_iterator<Type const, SIZE> constant_iterator;

    iterator begin()
    {
        return iterator(data, 0);
    }

    iterator end()
    {
        return iterator(data, SIZE);
    }

    constant_iterator begin() const 
    {
        return constant_iterator(data, 0);
    }

    constant_iterator end() const
    {
        return constant_iterator(data, SIZE);
    }
};

int main(int argc, char* argv[])
{
    return 0;
}