// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ for C++20

#include <iostream>

/**
 * In case you do not know the size of the bit sequence, it would be a better
 * option to use std::vector<bool> instaed of a std::bitset, as it is a
 * specialization with space and speed optimization for bits elements. Just, 
 * keep in mind that this specialization cannot be used with generic code
 * where a vector is expected.
 * 
 * The reason it isn't a standard vector is because the elements aren't stored
 * in a contiguous sequence, then it cannot be substituted for a boolean array,
 * for intance, you cannot use:
 * 
 * - auto& bit = bool_vector[0];
 * - auto& bit = *bool_vector.begin();
 * 
 * Also, there isn't guarantee that the individual bits can be manipulated
 * indepedently at the same time from different threads, it cannot use forward
 * iterators (then you cannot use std::search()), and also, for generic or
 * template implementations, you cannot use them in the previous cases.
 * 
 * You still need the <vector> header and work under the std namespace.
 * 
 * NOTE: One alternative for boolean usage is std::deque<bool>, a double
 * ended queue that allows all standard algorithms but has no space 
 * optimization.
 * 
 */

// ---------------------- REQUIRED HEADERS ------------------------------------
#include <vector>    // For using dynamic array and similar types.
#include <algorithm> // For using general puprose functions and methods.

// --------------------- FUNCTION DEFINITIONS ---------------------------------
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

// ------------------------------ CLASS DEFINITIONS --------------------------

// Info #2: 

/**
 * Wrapper that will be encapsulate std::vector<bool> implementations to be
 * managed as bitset.
 */
class custom_bitvector
{
    // Private/Protected method.
    std::vector<bool> bool_vec;
public:

    /*
     * Constructor that uploads the original std::vector, that uploads the
     * std::vector definition. 
     * 
     * @param bool_vec Boolean vecctor of interest to convert
     */
    custom_bitvector(std::vector<bool> const & bool_vec) : bool_vec(bool_vec)
    {}

    bool operator[](size_t const i) { return bool_vec[i]; }

    inline bool any() const 
    {
        for (auto element : bool_vec) if( element ) return true;
        return false;
    }

    inline bool all() const
    {
        for(auto element : bool_vec) if(!element) return false;
        return true;
    }

    inline bool none() const { return !any(); }

    inline size_t count() const
    {
        return std::count(bool_vec.cbegin(), bool_vec.cend(), true);
    }

    inline size_t size() const { return bool_vec.size(); }

    inline custom_bitvector & add(bool const value)
    {
        bool_vec.push_back(value);
        return *this;
    }

    inline custom_bitvector & remove(size_t const index)
    {
        if (index >= bool_vec.size())
            throw std::out_of_range("Invalid Index: Out of range.");
        bool_vec.erase(bool_vec.begin() + index);
        return *this;
    }

    inline custom_bitvector & set(bool const value = true)
    {
        for (size_t i = 0; i < bool_vec.size(); ++i)
            bool_vec[i] = value;
        return *this;
    }

    inline custom_bitvector & set(size_t const index, bool const value = true)
    {
        if(index >= bool_vec.size())
            throw std::out_of_range("Invalid Index: Out of range.");
        bool_vec[index] = value;
        return *this;
    }

    inline custom_bitvector & reset()
    {
        for( size_t i = 0; i < bool_vec.size(); ++i)
            bool_vec[i] = false;
        return *this;
    }

    inline custom_bitvector & reset(size_t const index)
    {
        if(index >= bool_vec.size())
            throw std::out_of_range("Invalid Index: Out of range.");
        bool_vec[index] = false;
    }

    inline custom_bitvector & flip()
    {
        bool_vec.flip();
        return *this;
    }

    std::vector<bool>& data()
    {
        return bool_vec;
    }
};

int main(int argc, char* argv[])
{
    // Info #1: Manipulation of a std::vector<bool> counts with the same
    // methods of any std::vector<T> implementation, here we present a short
    // review on them:
    std::vector<bool> bool_vec;
    std::cout << "Creation and modification of a boolean vector:" << std::endl
              << "Void vector creation: (";
    display_content(bool_vec);
    bool_vec.push_back(true);
    bool_vec.push_back(false);
    bool_vec.push_back(false);
    std::cout << ")\n\tAdding three elements: (";
    display_content(bool_vec);
    bool_vec[2] = true;
    std::cout << ")\n\tChaning last element: (";
    display_content(bool_vec);
    std::cout << ")\n\tHow many ones? "
              << std::count(bool_vec.cbegin(), bool_vec.cend(), true);
    bool_vec.erase(bool_vec.begin() + 1 );
    std::cout << "Erasing element in 2° position: (";
    display_content(bool_vec);
    std::cout << ")" << std::endl;

    // Info 3: Applying our user-defined interface for the boolean vector as a
    // bitset.
    std::vector<bool> att_bit;
    custom_bitvector c_bv {att_bit} ;
    c_bv.add(true).add(true).add(false);
    std::cout << "\nDisplaying info of std::vector considered as bitset:"
              << std::endl << "\tVector content: ";
    display_content(c_bv.data());
    std::cout <<"\n\tIs there any zero?: " << c_bv.any()
              << "\n\tHas only 1s?: " << c_bv.all()
              << "\n\tHas only 0s?: " << c_bv.none() << std::endl;

    return 0;
}