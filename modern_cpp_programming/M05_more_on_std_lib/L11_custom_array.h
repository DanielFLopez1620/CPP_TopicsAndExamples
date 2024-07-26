#include <iterator>  // Oriented to the usage of iterators and related methods.
#include <cassert>   // For assertion based on C
#include <memory>    // For dynamic memory usage 
#include <algorithm> // Colletion of general purpose algorithms and functions.

// ----------------------------- CLASS AND STRUCT DEFINITIONS -----------------

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
    } // operator[]

    /**
     * Getter of the element at the given index.
     * 
     * @param index Index in array of interest
     * 
     * @return Element present in the given index
     */
    Type const & operator[](size_t const index) const
    {
        if(index < SIZE) return data[index];
        throw std::out_of_range("Index out of bounds");
    } // operator[]

    /**
     * Getter of the size of the array.
     * 
     * @return Get size (in terms of variables stored inside).
     */
    size_t size() const { return SIZE; }

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
        } // compatible()

    public:
        /**
         * Explicit constructor that defines an iterator by providing the 
         * pointed memory and the initial index.
         * 
         * @param ptr Pointer that points to the start of a container.
         * @param index First value of the index to consider.  
         */        
        explicit custom_array_iterator(pointer ptr, size_t const index)
            : ptr(ptr), index(index) {}

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
        } // operator++ 

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
        } // operator++(int)

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
        } // operator==

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
        } // operator!=

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
        } // operator*

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
        } // operator->

        
        /**
         * Default construction for the iterator.
         */
        custom_array_iterator() = default;

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
        } // operator--

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
        } // operator-- (int)

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
        } // operator+ (iter_type)

        /**
         * Arithmetic substraction by considering pointed element by the
         * iterator index and the offset of other element.
         * 
         * @param offset Element to consider for the substraction.
         * 
         * @return Final differenc estored in the original pointer object.
         */
        iter_type operator-(difference_type offset) const
        {
            iter_type tmp = *this;
            return tmp -= offset;
        } // operator- (iter_type)

        /**
         * Substraction for indexex between iterators.
         * 
         * @param other Other iterator to consider for the substraction.
         * 
         * @return Iterator result after substract of indexes.
         */
        difference_type operator-(iter_type const & other) const
        {
            assert(compatible(other));
            return (index - other.index);
        } // operator- (diffrence_type)

        /**
         * Comparison less operator by checking first compatibility and then
         * making the index comparison for the iterators.
         * 
         * @param other Other iterator to consider for the comparison.
         * 
         * @return True, if the current iterator index is less, False otherwise
         */
        bool operator<(iter_type const & other) const
        {
            assert(compatible(other));
            return index < other.index;
        } // operator<

        /*
         * Comparion greater operator by implementing the negation of the
         * less than operator.
         * 
         * @param other Other iterator to consider for the comparison.
         * 
         * @return True, if the current iterator index is greater, False
         *         otherwise.
         */
        bool operator>(iter_type const & other) const
        {
            return other < *this;
        } // operator>

        /**
         * Comparison less or equal than that implements the negation of the
         * contrary case of less comparison ( other is less than current 
         * iterator)
         * 
         * @param other Other iterator to consider for the comparison.
         * 
         * @return True if the current element is less or equal than the other,
         *         False, otherwise.
         */
        bool operator<=(iter_type const & other) const
        {
            return !(other < * this);
        } // operator<=     

        /**
         * Comparison greater or equal than that implements the negation of the
         * contrary case of less comparison ( current is less than other
         * iterator)
         * 
         * @param other Other iterator to consider for the comparison.
         *
         * @return Pointer to the iterator with the summed index
         */
        iter_type & operator+=(difference_type const offset)
        {
            if(index + offset < 0 || index + offset > Size)
                throw std::out_of_range("Iterator out of bounds");
            index += offset;
            return *this;
        } // operator+=
        
        /**
         * Decrement self by operator that checks if the diff of the indexes
         * is between zero and the real size of the container. 
         * 
         * @param offset Offset to consider for the substraction
         * 
         * @return Pointer to the iterator with the differenced index
         */
        iter_type & operator-=(difference_type const offset)
        {
            return *this += -offset;
        } // operator-=

        /**
         * Getter by using the iterator of the current index, it can consider
         * an offset.
         * 
         * @param offset Distance to the index of interesst
         * 
         * @return Valee stored by the container in the given position
         */
        value_type & operator[](difference_type const offset)
        {
            return (*(*this + offset));
        } // operator []
        
        /**
         * Constant getter by using the iterator of the current index, it can 
         * consider an offset.
         * 
         * @param offset Distance to the index of interesst
         * 
         * @return Valee stored by the container in the given position
         */
        value_type const & operator[](difference_type const offset)
        const
        {
            return (*(*this + offset));
        }  // const operator[]

    }; // class custom_array_iterator


    typedef custom_array_iterator<Type, SIZE> iterator;
    typedef custom_array_iterator<Type const, SIZE> constant_iterator;

    /**
     * Begin method to obtain the iterator at the first position for 
     * a mutable custom defined array.
     * 
     *  @return Iterator with index pointing to position 0.
     */
    iterator begin()
    {
        return iterator(data, 0);
    } // begin()

    /**
     * End method to obtain the iterator at the last plus one position of the
     * container for a custom defined array.
     */
    iterator end()
    {
        return iterator(data, SIZE);
    } // end()

    /**
     * Begin method to obtain the iterator at the first position for 
     * a custom defined array, by providing a constant iterator.
     * 
     *  @return Iterator with index pointing to position 0.
     */
    constant_iterator begin() const 
    {
        return constant_iterator(data, 0);
    } // begin() const

    /**
     * End method to obtain the iterator at the last plus one position of the
     * container for a custom defined array.
     */
    constant_iterator end() const
    {
        return constant_iterator(data, SIZE);
    } // end() const
};
