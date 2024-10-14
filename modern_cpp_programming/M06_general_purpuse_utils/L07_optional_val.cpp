// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Have you ever wondered how can you make the returns in a function
 * according to a case? No, well, have you ever tried to return keys of a 
 * dictionary, but when you do not find one you end up depending on
 * exceptions rather that error codes?
 * 
 * In that case, or just if you are curious, after C++17 std::optional
 * was added to store values that may or may not exist. It is present
 * in the <optional> header.
 * 
 * In this template, there are no heap allocations or pointer involment,
 * and its implementation can be like the one below:
 * 
 *      template <typename T>
 *      class optional
 *      {
 *        bool _initialized;
 *        std::aligned_storage_t<sizeof(t), alignof(T)> _storage;
 *      };
 * 
 * Where the std::aligned_storage_t is an alias template that allows the 
 * creation  of unintialized chunks of memory that can hold objects of the
 * specified types. It will not have a value (std::optional) if you use the
 * default constructor, a copy of a void std::optional or from a std::nullopt_t
 * 
 * When using std::optional keep in mind that even if you do not pass the arg,
 * it may make some copies of the empty std::optional value, for that, you muss
 * consider a proper way of calling the args, for example, if you pass a
 * non-std::optional value to an std::optional arg, you will inquire in a copy.
 * 
 * NOTE: The implementation of optional can be checked in other programming
 * languages under the name "nullable".
 * 
 * NOTE: std::optional cannot be used to return polymorphic types. If you need
 * a factory method, it is better to use return pointers.
 * 
 * When ready, you can compile and run the code with:
 * 
 *      g++ -std=c++20 L07_optional_val.cpp -o opt.out
 *      ./opt.out
 * 
 */

// ------------------- REQUIRED HEADERS ---------------------------------------
#include <optional>  // For usage of optional type
#include <string>    // String management and operations
#include <map>       // For using pair like struct

// -------------------- STRUCT DEFINITIONS ------------------------------------

// Custom struct to check that it can be used with optional values.
struct custom_struct
{
    int num;
    char letter;
};

// Unused struct, just added to confirm that you can use optional values in
// custom structs. Check more info below.
struct game
{
    std::string title;
    std::optional<std::string> developers;
    std::string console;
    std::optional<int> stimated_hours;
};

// --------------------------- FUNCTION PROTOTYPES ----------------------------
template <typename K, typename V>
std::optional<V> find_in_map(int const key, std::map<K,V> const & map);

std::string extract_from_str(std::string const &text, std::optional<int> start,
    std::optional<int> end);

// -------------------------- MAIN IMPLEMENTATION ----------------------------
int main(int argc, char *argv[])
{
    std::cout << "Using optional values...\n" << std::endl;
    
    // Info #1: You can create an optional value by using assing, the 
    // default constructor and the copy constructor, just remember that for
    // printing you have to use the member function value():
    std::optional<int> opt_num1;
    opt_num1 = 16;
    std::optional<float> opt_num2 = 4.2;
    std::optional<float> opt_num3 = opt_num2;
    std::cout << "Creating optional values: " << std::endl
              << "\tDefault, then assign: " << opt_num1.value() << std::endl
              << "\tAssign value: " << opt_num2.value() << std::endl
              << "\tCopy optional: " << opt_num3.value() << std::endl; 

    // Info #2: To read the stored values, you can use  operator* or 
    // operator*
    std::optional<custom_struct> opt_struct{ custom_struct{16, 'd'}};
    std::cout << "Reading the values of the optional variables: " << std::endl
              << "\topt_num1: " << *opt_num1 << std::endl
              << "\topt_struct: (num = " << opt_struct->num << ") (letter = "
              << opt_struct->letter << ")" << std::endl;
    
    // Info #3: You already know that you can use value, to access the value of
    // a given optional value, but if the optional value is empty, what will it
    // show? For this cases, you can use the member function "value_or(<str>)"
    // to specify what to show (a default) in case there is no type in the opt.
    std::optional<int> opt_num4 {1620};
    std::optional<int> opt_num5;
    std::optional<std::string> opt_str;
    std::cout << "Displaying the value, but checking content: " << std::endl
              << "\topt_num4: " << opt_num4.value_or(0) << std::endl
              << "\topt_num5: " << opt_num5.value_or(0) << std::endl
              << "\topt_str1: " << opt_str.value_or("Empty") << std::endl;

    // Info #4: If you need a boolean validation to check if a std::optional
    // has a value, you can use the member function has_value()
    std::cout << "Checking if a std::optional has a value: " << std::endl
              << "\topt_num4 has value?: " << opt_num4.has_value() << std::endl
              << "\topt_num5 has value?: " << opt_num5.has_value() << std::endl;

    // Info #5: Similar to the std::any, you can use emplace(), reset() and 
    // swap() member functions.
    std::cout << "Using emplaced, reset and swap: " << std::endl;
    std::optional<std::string> opt;
    std::optional<std::string> for_swap("Wait, was I swaped?");
    opt.emplace("Hi! Emplaced 1");
    std::cout << "\tValue after 1° Emplace: " << *opt << std::endl;
    opt.emplace("Emplaced 2");
    std::cout << "\tValue after 2° Emplace: " << *opt << std::endl;
    opt.swap(for_swap);
    std::cout << "\tValue after swap: " << *opt << std::endl;
    opt.reset();
    std::cout << "\tValue after reset... Does it have a value?: " 
              << opt.has_value() << std::endl; 

    // Info #6: Check the functions definitons to learn about what can you do
    // with std::optional. Here we will showcase their usage.
    std::map<int, char> my_letter_map{ {1, 'a'}, {2, 'b'}, {3, 'c'}};
    auto value = find_in_map(3, my_letter_map);
    std::cout << "Searching for a value in a map: " << std::endl;
    if (value) 
    {
        std::cout << "\tValue found: " << *value << std::endl;
    }
    else
    {
        std::cout << " \tValue not found... " << std::endl;
    }
    auto uncut_message = extract_from_str("cut_everyhing", {}, {});
    auto cut_message = extract_from_str("cut_everything", 3, {});
    std::cout << "Giving optional arguments for functions: " << std::endl
              << "\tMessage with default args: " << uncut_message << std::endl
              << "\tTrimmed message: " << cut_message << std::endl;

    return 0;
} // main()

// --------------------------- FUNCTION DEFINITIONS ---------------------------

/**
 * Generic function to check that search for the pair of a key (the value) in a
 * map, it considers an optional return.
 * 
 * @param key elemento to search for the paier
 * @param map Map of interest
 * 
 * @return Optional value, the value if the key is found, nothing otherwise.
 */
template <typename K, typename V>
std::optional<V> find_in_map(int const key, std::map<K,V> const & map)
{
    auto pos = map.find(key);
    if (pos != map.end())
    {
        return pos->second;
    }
    return {};

} // find_in_map()

/**
 * Simple function to trim a string by considering optional values of the
 * beginning and the end of the array.
 * 
 * @param text String of interest
 * @param start Optional value to consider as the start
 * @param end Optional vlaue to consider as the end
 * 
 * @return Extracted part of the string.
 */
std::string extract_from_str(std::string const &text, std::optional<int> start,
    std::optional<int> end)
{
    auto s = start.value_or(0);
    auto e = end.value_or(text.length());
    return text.substr(s, e - s);

} // extract_from_str()