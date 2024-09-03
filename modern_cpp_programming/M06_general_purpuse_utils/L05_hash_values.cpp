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
 */

#include <string>
#include <unordered_set>

struct Stored
{
    int id;
    std::string name;

    Stored(int const id, std::string const & name)
        : id(id), name(name)
    {}

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
        res_type operator()(arg_type const & element) const
        {
            res_type hashValue = 23;
            hashValue = 31 * hashValue + std::hash<int>{}(element.id);
            hashValue = 31 * hashValue + std::hash<string>{}(element.name);
            
            return hashValue;
        }
    };
}


int main(int argc, char* argv[])
{
    std::unordered_set<Stored> unordered_stored
    {
        {1, "Potato"},
        {2, "Carrot"}
    };

    return 0;
}