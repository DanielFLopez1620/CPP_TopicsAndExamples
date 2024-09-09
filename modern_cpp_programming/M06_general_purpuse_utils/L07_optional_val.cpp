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
 * 
 * 
 */

#include <optional>
#include <string>
#include <map>


struct custom_struct
{
    int num;
    char letter;
};

struct game
{
    std::string title;
    std::optional<std::string> developers;
    std::string console;
    std::optional<int> stimated_hours;
};

template <typename K, typename V>
std::optional<V> find_in_map(int const key, std::map<K,V> const & map);

int main(int argc, char *argv[])
{
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

    return 0;
}

template <typename K, typename V>
std::optional<V> find_in_map(int const key, std::map<K,V> const & map)
{
    auto pos = map.find(key);
    if (pos != map.end())
    {
        return pos->second;
    }
    return {};
}

std::string extract_from_str(std::string const &text, std::optional<int> start,
    std::optional<int> end)
{
    auto s = start.value_or(0);
    auto e = end.value_or(text.length());
    return text.substr(s, e - s);
}