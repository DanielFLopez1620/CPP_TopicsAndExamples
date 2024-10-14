// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * We have used std::enable_if to hide function overloads and std::decay
 * to remove const and volite qualifiers. But we can mention another type
 * transformation feature that is std::conditional which enables a way
 * two select/choose between two types at compilation time.
 * 
 * Check down below to understand the implementation of std::conditional_t
 * to select among types according size, number of bytes or type for an
 * array.
 * 
 * When ready, you can use:
 *      
 *      g++ -std=c++20 L14_std_condition.cpp -o condition.out
 *      ./condition.out
 */

// --------------------- REQUIRED LIBRARIES -----------------------------------
#include <type_traits>  // For info (in compile-time) about types
#include <typeinfo>     // Contains info of the types, like name and unique id
#include <random>       // For pseudo-random generations

// --------------------- STRUCT AND TYPE DEFINITIONS --------------------------

// Bit selector that will be used in INFO#2, allows for selection of size of
// the integer in a proper way.
template <int size>
    using num_bit_selector = 
        typename std::conditional_t<
            size<=1, std::int8_t,
            typename std::conditional_t<
                size<=2, std::int16_t,
                typename std::conditional_t<
                    size<=4, std::int32_t, std::int64_t>>>;

// ----------------------- FUNCTION PROTOTYPES -------------------------------
template <typename T>
void display_value_and_type(const T& value, std::string waited_precision);


template <typename T,
          typename D = std::conditional_t<
              std::is_integral_v<T>, std::uniform_int_distribution<T>,
              std::uniform_real_distribution<T>>,
          typename = typename std::enable_if_t<
              std::is_arithmetic_v<T>>>
std::vector<T> RandomVector(T const min, T const max, size_t const size);

// ------------------------ MAIN IMPLEMENTATION -------------------------------
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
    num_bit_selector<1> var1 = 127;  // Max for int8_t
    display_value_and_type(var1, "int8");
    num_bit_selector<2> var2 = 32000;  // Max for int16_t
    display_value_and_type(var2, "int16");
    num_bit_selector<4> var3 = 2147483647;  // Max for int32_t
    display_value_and_type(var3, "int32");
    num_bit_selector<8> var4 = 9223372036854775807LL;  // Max for int64_t
    display_value_and_type(var4, "int32");

    // Info #3: You can even use the std::conditional with containers, for
    // example,  to generate a vector with random numbers.
    auto random_vector = RandomVector(1.6, 16.0, 5);
    std::cout << "Creating a random vector: \n\t( ";
    for (auto const & element : random_vector)
    {
        std::cout << element << ", ";
    }
    std::cout << ")" << std::endl;
    return 0;

} // main()


// -------------------------- FUNCTION DEFINITIONS ----------------------------

/**
 * Oriented to display info about the type selected by std::condition_t
 * for the num_bit_selector_type.
 * 
 * @param value Inferenced value for the current type
 * @param waited_precision Will log the waited precsiion by the user
 */
template <typename T>
void display_value_and_type(const T& value, std::string waited_precision)
{
    auto my_int_type = typeid(T).name();
    using Tt = std::remove_cv_t<std::remove_reference_t<T>>;
    std::string my_int_type_name = "Unknown type";
    if(std::is_same<Tt, int8_t>::value)
    {
        my_int_type_name = "int8";
    }
    else if(std::is_same<Tt, int16_t>::value)
    {
        my_int_type_name = "int16";
    }
    else if(std::is_same<Tt, int32_t>::value)
    {
        my_int_type_name = "int32";
    }
    else if(std::is_same<Tt, int64_t>::value)
    {
        my_int_type_name = "int64";
    }


    // Print the value and its type using typeid
    std::cout << "\tWaited precision: " << waited_precision << std::endl
              << "\t\tValue: " << static_cast<int64_t>(value) << std::endl
              << "\t\tType: " << my_int_type << std::endl
              << "\t\tType name: " << my_int_type_name << std::endl;

} // display_value_and_type()

/**
 * Function that creates a pseudo random vector (based on uniform distribution)
 * that can be integral o real, by considering the type of the args passed.
 * 
 * @param min Minimum value of the sequence, can be integer or real
 * @param max Maximum value of the sequence, can be integer or real
 * @param size Integer value of the size of the array
 * 
 * @return Vector of the given size with pseudo-random elements.
 */
template <typename T,
          typename D = std::conditional_t<
              std::is_integral_v<T>, std::uniform_int_distribution<T>,
              std::uniform_real_distribution<T>>,
          typename = typename std::enable_if_t<
              std::is_arithmetic_v<T>>>
std::vector<T> RandomVector(T const min, T const max, size_t const size)
{
    // Initialize vector size
    std::vector<T> v(size);

    // Set pseudo random generation
    std::random_device rand_dev{};
    std::mt19937 mt { rand_dev() };
    D dist{min, max};

    // Create a pseudo-random value for each position
    std::generate(std::begin(v), std::end(v),
        [&dist, &mt] {return dist(mt); });
    
    // Return final vector
    return v;

} // RandomVector()