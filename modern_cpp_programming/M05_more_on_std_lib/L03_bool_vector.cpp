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
 * When ready you can run and execute with:
 *  
 *      g++ -std=c++20 L03_bool_vec -o bool_vec.out
 *      ./vec.out
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

// Info #2: Down below you can check a wrapper of a std::vector that can be
// used to work with them as if they were bitsets.

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
     * @param bool_vec Boolean vector of interest to convert
     */
    custom_bitvector(std::vector<bool> const & bool_vec) : bool_vec(bool_vec)
    {}

    /**
     * For creating array implementation by reserving memory according the num
     * of elements passed.
     * 
     * @param i Size of the reservation for the array
     * 
     * @return Pointer to beginning of the array created
     */
    bool operator[](size_t const i) { return bool_vec[i]; }

    /**
     * Validates if any of the values stored in the group is true.
     * 
     * @return True if any of the elements is true, false otherwise.
     */
    inline bool any() const 
    {
        for (auto element : bool_vec) if( element ) return true;
        return false;

    } // any()

    /**
     * Validates that all the elements of the sequence are true.
     * 
     * @return true if all the elements are true, false otherwise.
     */
    inline bool all() const
    {
        for(auto element : bool_vec) if(!element) return false;
        return true;

    } // all()

    /**
     * Validates if there are no true values in a sequence.
     * 
     * @return true if nothing is true, false otherwise.
     */
    inline bool none() const { return !any(); }

    /**
     * Count how many true values are located in the sequence.
     * 
     * @return Final count on true values.
     */
    inline size_t count() const
    {
        return std::count(bool_vec.cbegin(), bool_vec.cend(), true);
    
    } // count()

    /**
     * Getter of the size of the array/sequence.
     * 
     * @return Size of the boolean sequence.
     */
    inline size_t size() const { return bool_vec.size(); }

    /**
     * Add boolean element to the end of the sequence.
     * 
     * @param value Boolean value to add.
     * 
     * @return Pointer to the modified sequence
     */
    inline custom_bitvector & add(bool const value)
    {
        bool_vec.push_back(value);
        return *this;

    } // add ()

    /**
     * Delete the element at the given position.
     * 
     * @param index Position of the element to delete in the sequence.
     * 
     * @return Pointer to the modified sequence.
     */
    inline custom_bitvector & remove(size_t const index)
    {
        if (index >= bool_vec.size())
            throw std::out_of_range("Invalid Index: Out of range.");
        bool_vec.erase(bool_vec.begin() + index);
        return *this;

    } // remove ()

    /**
     * Setter of true value to all the elements present in the sequence.
     * 
     * @param value Value to set, as a default it is true.
     * 
     * @return Pointer to the modified sequence.
     */
    inline custom_bitvector & set(bool const value = true)
    {
        for (size_t i = 0; i < bool_vec.size(); ++i)
            bool_vec[i] = value;
        return *this;

    } // set()

    /**
     * Setter of a value in hte given position of the sequence.
     * 
     * @param index Position at which the value is going to be set.
     * @param value Value to set, as a default it is true.
     * 
     * @return Pointer to the modified sequence.
     * 
     * @exception Throws std::out_of_range if the index is invalid.
     */
    inline custom_bitvector & set(size_t const index, bool const value = true)
    {
        if(index >= bool_vec.size())
            throw std::out_of_range("Invalid Index: Out of range.");
        bool_vec[index] = value;
        return *this;
    } // set ()

    /**
     * Reset all the elements of the sequence to be OFF/False.
     * 
     * @return Pointer to the modified sequence.
     */
    inline custom_bitvector & reset()
    {
        for( size_t i = 0; i < bool_vec.size(); ++i)
            bool_vec[i] = false;
        return *this;

    } // reset()

    /**
     * Setter of false at the given index.
     * 
     * @param index Positon to set as a False value.
     * 
     * @exception Throws std::out_of_range if the index isn't valid.
     */
    inline custom_bitvector & reset(size_t const index)
    {
        if(index >= bool_vec.size())
            throw std::out_of_range("Invalid Index: Out of range.");
        bool_vec[index] = false;

    } // reset()

    /**
     * Change and invert all the elements present in the sequence.
     * 
     * @return Pointer to the modified sequence
     */
    inline custom_bitvector & flip()
    {
        bool_vec.flip();
        return *this;

    } // flip ()

    /**
     * Getter of the data as the form of a std::vector<bool>
     * 
     * @return Original vector that is working under the wrapper.
     */
    std::vector<bool>& data()
    {
        return bool_vec;

    } // data ()
};  // class custom_bitvector

// ----------------------------------- MAIN IMPLEMENTATION --------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 3: Using standard boolean vectors...\n" << std::endl;
    
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
} // Main