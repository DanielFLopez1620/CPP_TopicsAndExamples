// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code wasm't tested for C++20

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
template <typename T, std::size_t N>
class CustomContainer 
{
public:
    // Nested iterator class
    class Iterator 
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        Iterator& operator++() 
            { m_ptr++; return *this; }
        Iterator operator++(int) 
            { Iterator tmp = *this; ++(*this); return tmp; }

        Iterator& operator--() 
            { m_ptr--; return *this; }
        Iterator operator--(int) 
            { Iterator tmp = *this; --(*this); return tmp; }

        Iterator operator+(difference_type offset) const 
            { return Iterator(m_ptr + offset); }
        Iterator operator-(difference_type offset) const 
            { return Iterator(m_ptr - offset); }
        difference_type operator-(const Iterator& other) const 
            { return m_ptr - other.m_ptr; }

        bool operator==(const Iterator& other) const 
            { return m_ptr == other.m_ptr; }
        bool operator!=(const Iterator& other) const 
            { return m_ptr != other.m_ptr; }
        bool operator<(const Iterator& other) const 
            { return m_ptr < other.m_ptr; }
        bool operator>(const Iterator& other) const 
            { return m_ptr > other.m_ptr; }
        bool operator<=(const Iterator& other) const 
            { return m_ptr <= other.m_ptr; }
        bool operator>=(const Iterator& other) const 
            { return m_ptr >= other.m_ptr; }

        Iterator& operator+=(difference_type offset) 
            { m_ptr += offset; return *this; }
        Iterator& operator-=(difference_type offset) 
            { m_ptr -= offset; return *this; }

        reference operator[](difference_type offset) const 
            { return *(m_ptr + offset); }

    private:
        pointer m_ptr;
    };

    CustomContainer() = default;

    T& operator[](std::size_t index) {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }

    Iterator begin() { return Iterator(m_data); }
    Iterator end() { return Iterator(m_data + N); }

    const Iterator begin() const { return Iterator(m_data); }
    const Iterator end() const { return Iterator(m_data + N); }

private:
    T m_data[N];

}; // class CustomContainer

// -------------------------- FUNCTION DEFINITION -----------------------------

// Non-member functions for std::data(), std::empty(), and std::size()
template <typename T, std::size_t N>
T* data(CustomContainer<T, N>& container) {
    return &container[0];
}

template <typename T, std::size_t N>
const T* data(const CustomContainer<T, N>& container) {
    return &container[0];
}

template <typename T, std::size_t N>
bool empty(const CustomContainer<T, N>& container) {
    return N == 0;
}

template <typename T, std::size_t N>
std::size_t size(const CustomContainer<T, N>& container) {
    return N;
}

// ------------------------ MAIN IMPLEMENTATION -------------------------------
int main() 
{
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
    std::cout << std::endl;

    std::cout << "Container size: " << size(container) << std::endl
              << "Container is empty: " << (empty(container) ? "yes" : "no") 
              << std::endl;

    auto data_ptr = data(container);
    std::cout << "Data pointer points to: " << *data_ptr << std::endl;

    return 0;

} // main
