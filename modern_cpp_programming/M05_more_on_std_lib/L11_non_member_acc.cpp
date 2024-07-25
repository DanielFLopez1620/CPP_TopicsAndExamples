// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasm't tested for C++20

#include <iostream>

/**
 * In the previous lesson we checked the standard container implementation
 * of begin() and end() member functions. However, there are more, like
 * cbegin()/cend(), rbegin()/rend(), crbegin()/crend() that return iterators. 
 * And after C++17 more appeared, like std::data() that returns a pointer to
 * the memory block, std::size() that returns the size of the container, 
 * std::empty() that specifies wheter the container is empty or not. Also,
 * in C++20 std::ssize() was added to return the size of a container as a 
 * signed int. In resume they are used for:
 * 
 *  - std::size() -> Returns the size of the container
 *  - std::empty() -> Checks if the array is empty
 *  - std::data() -> Return the position in memory
 * 
 * Then, they can be implemented in the definitions you create, but the
 */

// -------------------------... REQUIRED LIBRARIES ----------------------------
#include <vector>     // For using dynamic containers 
#include <algorithm>  // Collections of general purpose algorithms
#include <cassert>    // Assertions from C
#include <memory>     // Dynamic memory management

// --------------------------- FUNCTION PROTOTYPES ---------------------------
template <typename T>
void display_content(std::vector<T> vector);

// ---------------------------- CLASS DEFINITION ------------------------------

// Reused from lesson 10.
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
     * @param index I
     * 
     * @return Element present in the given index
     */
    Type const & operator[](size_t const index) const
    {
        if(index < SIZE) return data[index];
        throw std::out_of_range("Index out of bounds");
    } // operator[]

    
    // ------------------------------------------------------------------------
    // Info #1: Here are members definitions of the size(), data()
    // and empty(), later you can check for the non-member implementations.
    // ------------------------------------------------------------------------

    // /**
    //  * Getter of the size of the array.
    //  * 
    //  * @return Get size (in terms of variables stored inside).
    //  */
    // size_t size() const 
    // {
    //     return SIZE; 
    // }

    // /**
    //  * Check if the arrays is empty or if it has content.
    //  * 
    //  * @return True if it is void, False otherwise.
    //  */
    // bool empty() const
    // {
    //     return SIZE == 0;
    // }

    // /**
    //  * Obtain the direction in memory of an array (begin).
    //  * 
    //  * @return Pointed memory.
    //  */
    // Type* data()
    // {
    //     return data;
    // }

    // /**
    //  * Obtain the direction in memory of a constant array (begin)
    //  * 
    //  * @return Pointed memory.
    //  */
    // Type const* data() const
    // {
    //     return data;
    // }

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
        /**modern_cpp_programming/M05_more_on_std_lib/L11_non_member_acc.cpp:509:14: error: expected unqualified-id before ‘inline’
  509 | constexpr T* inline begin(T (&array)[N])   
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

}; // custom_array

template<class C>
constexpr auto inline begin(C& c) -> decltype(c.end())
{
    return c.begin();
}

template<class C>
constexpr auto inline end(C& c) -> decltype(c.end())
{
    return c.end();
}

template<class T, std::size_t N>
constexpr T* begin(T (&array)[N])
{
    return array;
}

template<class T, std::size_t N>
constexpr T* begin(T (&array)[N])
{
    return array+N;
}

template <class C>
constexpr auto data(C& c) -> decltype(c.data())
{
    return c.data();
}

template <class C>
constexpr auto data(const C& c) -> decltype(c.data())
{
    return c.data();
}

template <class T, std::size_t N>
constexpr T* data(T (&array)[N]) noexcept
{
    return array;
}

template <class E>
constexpr const E* data(std::initializer_list<E> il) noexcept
{
    return il.begin();
}

template <class C>
constexpr auto size(const C& c) -> decltype(c.size())
{
    return c.size();
}

template <class T, std::size_t N>
constexpr std::size_t size(const T (&array)[N]) noexcept
{
    return N;
}

template <class C>
constexpr auto empty(const C& c) -> decltype(c.empty())
{
    return c.empty();
}


template <class T, std::size_t N>
constexpr bool empty(const T(&array)[N]) noexcept
{
    return false;
}

template <class E>
constexpr bool empty(std::initializer_list<E> il) noexcept
{
    return il.size() == 0;
}

template <class C>
constexpr auto ssize(const C& c) 
    -> std::common_type<std::ptrdiff_t, std::make_signed_t<decltype(c.size())>>
{
    using R = std::common_type_t<std::ptrdiff_t,
        std::make_signed_t<decltype(c.size())>>;
    
    return static_cast<R>(c.size());
}

template <class T, std::ptrdiff_t N>
constexpr std::ptrdiff_t ssize(const T(&array)[N]) noexcept
{
    return N;
}

// --------------------------- MAIN IMPLEMENTATION ----------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 11: Using non-meber function for accesing info\n"
              << std::endl;
    
    std::vector<float> vec_flt1 {1.6, 2.0, 6.2, 1.0};
    auto s_v1 = std::size(vec_flt1);
    auto e_v1 = std::empty(vec_flt1);
    auto d_v1 = std::data(vec_flt1);
    std::cout << "Using a float container: " << std::endl
              << "\tSize: " << s_v1 << std::endl 
              << "\tIs empty?: " << e_v1 << std::endl
              << "\tData:" << d_v1 << std::endl
              << "\tContent: (";
    display_content(vec_flt1);
    std::cout << ")" << std::endl;

    int arr_int1[4] = {1620, 261, 162, 612};
    auto s_v2 = std::size(arr_int1);
    auto e_v2 = std::empty(arr_int1);
    auto d_v2 = std::data(arr_int1);
    std::cout << "Using a integer array: " << std::endl
              << "\tSize: " << s_v2 << std::endl 
              << "\tIs empty?: " << e_v2 << std::endl
              << "\tData:" << d_v2 << std::endl
              << "\tContent: (";
    for (int i = 0; i < s_v2; i++)
    {
        std::cout << arr_int1[i] << ", ";
    }
    std::cout << ")" << std::endl;


    custom_array<float, 4> cus_example;
    cus_example[0] = 1.6;
    cus_example[1] = 6.2;
    cus_example[2] = 2.0;
    cus_example[3] = 1.0;
    auto s_v3 = std::size(cus_example);
    auto e_v3 = std::empty(cus_example);
    auto d_v3 = std::data(cus_example);

    std::cout << "Using custom_array: " << std::endl
              << "\tSize: " << s_v3 << std::endl 
              << "\tIs empty?: " << e_v3 << std::endl
              << "\tData:" << d_v3 << std::endl
              << "\nHere, we didn't defined data or empty (yet)..."
              << "\tContent: (";
    for(auto const & element : cus_example)
    {
        std::cout << element << ", ";
    }
    std::cout << ")" << std::endl;
    

    return 0;
}

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