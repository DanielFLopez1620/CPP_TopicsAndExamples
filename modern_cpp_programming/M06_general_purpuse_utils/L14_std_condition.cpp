// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * We have used std::enable_if to hide function overloads and std::decay
 * to remove const and volite qualifiers. But we can mention another type
 * transformation feature that is std::conditional which enables a way
 * two select/choose between two types at compilation time.
 * 
 *
 */

#include <type_traits>
#include <typeinfo>

template <int size>
    using num_bit_selector = 
        typename std::conditional_t<
            size<=1, std::int8_t,
            typename std::conditional_t<
                size<=2, std::int16_t,
                typename std::conditional_t<
                    size<=4, std::int32_t, std::int64_t>>>;

template <typename T>
void display_value_and_type(const T& value, std::string waited_precision);

int main(int argc, char* argv[])
{
    std::cout << "Lesson 14: Using std::conditional for deciding types\n"
              << std::endl; 
    
    // Info #1: You can use std::conditional to select between two types
    // according to the size detected. Here we also present a way to display
    // the type with type_id and the comparation with remove_cv and
    // remove_reference.
    using custom_long_num = std::conditional_t<sizeof(void*) <= 4, 
        long, long long>;
    auto num = custom_long_num{16};
    auto my_num_type = typeid(custom_long_num).name();
    using T = std::remove_cv_t<std::remove_reference_t<custom_long_num>>;
    std::cout << "Defining long or long long in compile time: " << std::endl
              << "\tValue: " << num << std::endl << "\tType: " << my_num_type
              << std::endl << "\tType name: ";
    if (std::is_same<T, long long>::value) 
    {
        std::cout << "Long long" << std::endl;
    } 

    else if (std::is_same<T, long>::value) 
    {
        std::cout << "Long" << std::endl;
    } 
    else 
    {
        std::cout << "Unknown type" << std::endl;
    }

    // Info #2: You can even generate nested std::conditional to generate
    // a more complex decision. In this case experimenting with size of
    // integers that go from int8 to int32.
    num_bit_selector<1> var1 = 127;  // Maximum value for int8_t
    display_value_and_type(var1, "int8");
    num_bit_selector<2> var2 = 32000;  // Typical value for int16_t
    display_value_and_type(var2, "int16");
    num_bit_selector<4> var3 = 2147483647;  // Maximum value for int32_t
    display_value_and_type(var3, "int32");
    num_bit_selector<8> var4 = 9223372036854775807LL;  // Maximum value for int64_t
    display_value_and_type(var4, "int32");

    return 0;
}

template <typename T>
void display_value_and_type(const T& value, std::string waited_precision)
{
    // Print the value and its type using typeid
    std::cout << "\tWaited precision: " << waited_precision << std::endl
              << "\t\tValue: " << static_cast<int64_t>(value) << std::endl
              << "\t\tType: " << typeid(T).name() << std::endl;
              // TODO: Add type name
}