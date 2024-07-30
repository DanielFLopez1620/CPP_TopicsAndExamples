// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested for C++20 with g++

#include <iostream>

/**
 * Here we intended to create a custom container class and tried to implement
 * some non-member function related to access like std::data, std::size and
 * std::empty with a little different approach to the lesson 11 on this module.
 * 
 * When you are ready, you can use:
 * 
 *      g++ -std=c++20 L12_more_non_member.cpp -o more_non_m.out
 *      ./more_non_m.out
 */

// ------------------------- REQUIRED HEADERS ---------------------------------

#include <iterator>   // For using iterators, considering we want a random acc
#include <stdexcept>  // Standard exceptions
#include <cstddef>    // C standard definitions


// ------------------------ CLASS DEFINITIONS ---------------------------------

/**
 * Generic custom container class with a known size.
 */
template <typename T, std::size_t N>
class CustomContainer 
{
public:
    
    /**
     * Nested class iterator for purpose of using as if it was a standard
     * container with a random access iteratior.
     */
    class Iterator 
    {
    public:
        // ----> Type definitions for the iterator methods and operations
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * User defined cconstructor for the iterator by just considering the
         * pointer to the direction where the container begins.
         * 
         * @param ptr Pointer that points to the start of the container.
         */
        Iterator(pointer ptr) : m_ptr(ptr) {}

        // ----> Pointer related methods

        /**
         * Reference operator to access to the element pointed by the 
         * iterator's pointer.
         * 
         * @return Pointed element according the type interpreted.
         */
        reference operator*() const { return *m_ptr; }

        /**
         * Obtain the pointer reference stored by the iterator
         * 
         * @return Pointer of the iterator.
         */
        pointer operator->() { return m_ptr; }

        // ---> Forward/increment related methods

        /**
         * Increment (single) the poisiton of the iterator
         * 
         * @return This iterator after the increment. 
         */
        Iterator& operator++() 
        { 
                m_ptr++; 
                return *this; 
        }

        /**
         * Increment by considering temporal variable assign
         * 
         * @return Iterator after the increment.
         */
        Iterator operator++(int) 
        {
            Iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }

        // --------> Backward /decrement related methods

        /**
         * Decrement (single) operator for the iterator.
         * 
         * @return Iterator after the decrement has ocurred
         */
        Iterator& operator--() 
        { 
            m_ptr--; 
            return *this; 
        }

        /**
         * Decrement by considering temporal variable.
         * 
         * @return Iterator after the decrement
         */
        Iterator operator--(int) 
        { 
            Iterator tmp = *this; 
            --(*this); 
            return tmp; 
        }

        // ---> Arithmetic related methods and operators

        /**
         * Sum definition by considering an offset to the index that the 
         * iterator works.
         * 
         * @param offset Numeric increment (considering type size) to move the
         *               the iterator.
         * 
         * @return Incremented iterator
         */
        Iterator operator+(difference_type offset) const 
            { return Iterator(m_ptr + offset); }

        /**
         * Substract definition by considering an offset to the current index
         * of the iterator.
         * 
         * @param offset Numeric increment (considering type size) to move the
         *               the iterator.
         * 
         * @return Decremented iterator
         */
        Iterator operator-(difference_type offset) const 
            { return Iterator(m_ptr - offset); }

        /**
         * Substratc tht considers the difference between two iterators (and the
         * position they are currently pointing)
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation.
         * 
         * @return New iterator with the differences implemented
         */
        difference_type operator-(const Iterator& other) const 
            { return m_ptr - other.m_ptr; }

        // ------> Comparison related operators

        /**
         * Equality comparison based on the indexes of the iterators.
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation
    std::cout .
         * 
         * @return True if the positions of the iterators are equal, False
         *         otherwise.
         */
        bool operator==(const Iterator& other) const 
            { return m_ptr == other.m_ptr; }

        /**
         * Inqualuality comparison based on the indexes of the iterators.
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation.
         * 
         * @return True if the positions of the iterators aren't equal, False
         *         otherwise.
         */
        bool operator!=(const Iterator& other) const 
            { return m_ptr != other.m_ptr; }
        
        /**
         * Less than comparison by considering the indexes of two iterators.
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation.
         * 
         * @return True if the positions of the first iterators is less than the
         *         second one, False otherwise.
         */
        bool operator<(const Iterator& other) const 
            { return m_ptr < other.m_ptr; }

        /**
         * Greater than comparison by considering the indexes of two iterators.
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation.
         * 
         * @return True if the positions of the first iterators is greater than 
         *         the second one, False otherwise.
         */
        bool operator>(const Iterator& other) const 
            { return m_ptr > other.m_ptr; }

        /**
         * Less or equal than comparison by considering the indexes of two
         * iterators.
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation.
         * 
         * @return True if the positions of the first iterators is less or 
         *         equal than the second one, False otherwise.
         */
        bool operator<=(const Iterator& other) const 
            { return m_ptr <= other.m_ptr; }

        /**
         * Greater or equal than comparison by considering the indexes of two 
         * iterators.
         * 
         * @param other Pointed direction to other iterator considered for the
         *              operation.
         * 
         * @return True if the positions of the first iterators is greater or 
         *         equal than the second one, False otherwise.
         */
        bool operator>=(const Iterator& other) const 
            { return m_ptr >= other.m_ptr; }

        // ------> Self given increment operator 

        /**
         * Self given increment by considering an offset.
         * 
         * @param offset Numeric increment desired to apply to the iterator.
         * 
         * @return Iterator after increment.
         */
        Iterator& operator+=(difference_type offset) 
        { 
            m_ptr -= offset;
            return *this; 
        }

        /**
         * Access operator member for a given position
         * 
         * @param offset Index to consider for the direction.
         * 
         * @return Pointed value after considering offset.
         */
        reference operator[](difference_type offset) const 
        { 
            return *(m_ptr + offset); 
        }

    private:
        pointer m_ptr;
    };

    // Defaulted base constructor
    CustomContainer() = default;

    /**
     * Access operator that check the increment and access the element.
     * 
     * @param index Consider index direction for the access.
     * 
     * @return Element present at the given index.
     * 
     * @exception std::out_of_range if bounds are passed.
     */
    T& operator[](std::size_t index) {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }
    
    /**
     * Constant access operator that check the increment and access the element
     * 
     * @param index Consider index direction for the access.
     * 
     * @return Element present at the given index.
     * 
     * @exception std::out_of_range if bounds are passed.
     */
    const T& operator[](std::size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }

    /**
     * Iterator implementation for pointing to the beginning of a given
     * container. 
     * 
     * @return Iterator that points to the start of the container.
     */
    Iterator begin() 
        { return Iterator(m_data); }
    
    /**
     * Iterator implementation for pointing to the end of a given
     * container. 
     * 
     * @return Iterator that points to the end of the container.
     */
    Iterator end() 
        { return Iterator(m_data + N); }

    /**
     * Constant iterator implementation for pointing to the beginning of a 
     * given container. 
     * 
     * @return Iterator that points to the start of the container.
     */
    const Iterator begin() const 
        { return Iterator(m_data); }

    /**
     * Iterator implementation for pointing to the end of a given
     * container. 
     * 
     * @return Iterator that points to the end of the container.
     */
    const Iterator end() const 
        { return Iterator(m_data + N); }

private:
    T m_data[N];  // Private definitions of the container

}; // class CustomContainer

// -------------------------- FUNCTION DEFINITION -----------------------------

// Non-member functions for std::data(), std::empty(), and std::size()

/**
 * Non member for accessing the data direction of a custom container.
 * 
 * @param container Pointed container of interest
 * 
 * @return Memory adress of the beginning of the container.
 */
template <typename T, std::size_t N>
T* data(CustomContainer<T, N>& container) 
{
    return &container[0];
}

/**
 * Non member for accessing the data direction of a const custom container.
 * 
 * @param container Pointed container of interest
 * 
 * @return Memory adress of the beginning of the container.
 */
template <typename T, std::size_t N>
const T* data(const CustomContainer<T, N>& container) 
{
    return &container[0];
}

/**
 * Non member for checking if a custom container is empty.
 * 
 * @param container Pointed container of interest
 * 
 * @return True if there are no element, False otherwise
 */
template <typename T, std::size_t N>
bool empty(const CustomContainer<T, N>& container) 
{
    return N == 0;
}

/**
 * Non member for accessing the size  a custom container.
 * 
 * @param container Pointed container of interest
 * 
 * @return Size (consideration of elements) of the container
 */
template <typename T, std::size_t N>
std::size_t size(const CustomContainer<T, N>& container) 
{
    return N;
}

// ------------------------ MAIN IMPLEMENTATION -------------------------------
int main() 
{
    std::cout << "Lesson 12: Another example on non member access...\n"
              << std::endl;

    CustomContainer<int, 5> container;
    container[0] = 1;
    container[1] = 2;
    container[2] = 3;
    container[3] = 4;
    container[4] = 5;

    std::cout << "Container elements: ";
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl
              << "Container size: " << size(container) << std::endl
              << "Container is empty: " << (empty(container) ? "yes" : "no") 
              << std::endl;

    auto data_ptr = data(container);
    std::cout << "Data pointer points to: " << *data_ptr << std::endl;

    return 0;

} // main
