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
 */

#include <string>

struct Stored
{
    int id;
    std::string name;

    Item(int const id, std::string const & name)
        : id(id), name(name)
    {}

    bool operator==(Item const & other) const
    {
        return id == other.id && name == other.name;
    }
}

int main(int argc, char* argv)
{
    
    return 0;
}