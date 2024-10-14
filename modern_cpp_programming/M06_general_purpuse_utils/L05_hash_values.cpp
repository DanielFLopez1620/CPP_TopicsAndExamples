// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Have you ever heard from sted::unordered_set, std::unordered_multiset,
 * std::unordered_map? Well, this containers do not store their elements in a
 * particular way, and the rely on std::hash.
 * 
 * The important thing here is to compute a good hash value, so you can
 * prevent collisinons and calculate them fast and uniformily dispersed
 * across the value domain.
 * 
 * If you do not know about hashes, you should search on the Internet, but
 * here is an article I found interesting:
 * 
 * https://www.techtarget.com/searchdatamanagement/definition/hashing
 * 
 * If you want to use unordered associative containers, you should:
 *      
 * 1. Specialize std::has class tempalte for your definition
 * 2. Define synonyms for the argument and result type
 * 3. Implement the call operator in order to make it take a constant reference
 *    to your type and returns the waited hash value.
 * 
 * Also, for computing a good hash value, you can consider:
 * 
 * 1. Start with an initial value, hopefully a prime number
 * 2. Adjust the hash value: hashValue = hasValue * prime + hashFunc(field)
 * 3. It is recommended to have different values for the fields, at least, 31
 * 4. Use a hash specialization of std::hash  to determinate the hash value
 * 
 * But... how does this work?
 * The "std::hash" class is a function object template that creates a hash 
 * function with size_t value, non-throw exception, if two arguments are equal,
 * then the hash should be the same, and the probability for two different
 * arguments of returning the same value should be very small. 
 * 
 * The hashes are available for the basic types, basic_string, 
 * basic_string_view, unique_ptr, shared_ptr, bitset, vector<bool> and others. 
 * However, for custom types you  should define it, but keep in mind the 
 * properties previosly mentioned.
 * 
 * When ready, you can complie this code with:
 * 
 *      g++ -std=c++20 L05_hash_value.cpp -o hash_val.out
 *      ./hash_val.out
 * 
 * NOTE: Did you know that 31 * x can be replaced with (x << 5) - x which is 
 * faster. But this also applies with 127 * x  ((x << 7) - x) o 8191 * x 
 * ((x << 13) - x).
 * 
 * 
 */


// ------------------------------ REQUIRED HEADERS ----------------------------
#include <string>         // For string management
#include <unordered_set>  // Using non sequenced containers

// -------------------------- STRUCT AND CLASS DEFINITIONS --------------------

/**
 * Class that contains the id and the name of a product.
 */
struct Stored
{
    // Attributes
    int id;
    std::string name;

    // User-defined constructor
    Stored(int const id, std::string const & name)
        : id(id), name(name)
    {}
    
    // Equality operator, to check if the Stored elements are equal
    bool operator==(Stored const & other) const
    {
        return id == other.id && name == other.name;
    }
};

namespace std
{
    template<>
    struct hash<Stored>
    {
        typedef Stored arg_type;
        typedef size_t res_type;

        /**
         * Hash function operator to consider the element and convert it
         * to a given hash.
         */
        res_type operator()(arg_type const & element) const
        {
            res_type hashValue = 23;
            hashValue = 31 * hashValue + std::hash<int>{}(element.id);
            hashValue = 31 * hashValue + std::hash<string>{}(element.name);
            
            return hashValue;
        } // res_type operator()

    }; // struct hash<Stored>

} // namespace std

// ----------------------------- MAIN IMPLEMENTATION --------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 5: Using hash values for custom types:\n" 
              << std::endl;
    
    // Defyning custom unordered set
    std::unordered_set<Stored> unordered_stored
    {
        {1, "Potato"},
        {2, "Carrot"}
    };
    
    // Info #1: For displaying user-defined unordered set, you need to implment
    // the hash in the class.
    std::cout << "Displaying unordered set with custom type:" << std::endl;
    for (const auto & obj : unordered_stored)
    {
        std::cout << "\tID: " << obj.id << ", Name: " << obj.name << std::endl;
    }

    return 0;

} // main()