// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * In the previous lesson we explored about type trait, but what if I told you
 * that you can create your own?
 * 
 * For this purpose, this example is based on multiple classes that allow
 * serialization with different types and precisions, then you can create
 * a uniform API for serialize the types. 
 * 
 * Check the implementations, and when you are ready, compile and run:
 * 
 *      g++ -std=c++20 L13_own_type_traits.cpp -o own_trait.out
 *      ./own_trait.out
 */

// ------------------------ STRUCT DEFINITIONS --------------------------------

// Demo struct, it refers to a plain text that can be serialized
struct plain_text
{
    std::string serial()
    {
        return "serialized";
    }
}; // struct plain_text

// Demo struct, it refers to a text that can be serialized and encoded
struct encoded_text
{
    std::string serial_encoded()
    {
        return "encoded";
    }
}; // struct encoded_text

/**
 * Template that set the type trait to false for every structure or type, as
 * they aren't (supposing in this case) serialized and encoded.
 */
template <typename T>
struct is_serialized_and_encoded
{
    static const bool value = false;

}; // struct is_serialized_and_encoded

/**
 * Template that set the value of the encoded_text struct in the case of
 * the type trait as true, as here we are considering this is the only type
 * that is allowed to be encoded and serialized.
 */
template <>
struct is_serialized_and_encoded<encoded_text>
{
    static const bool value = true;

}; // struct is_serialized_and_encoded

/**
 * Template that call the serialization function of a type, in this case
 * for the plain_text struct.
 */
template <bool b>
struct serializer
{
    template <typename T>
    static auto serialize(T& v)
    {
        return v.serial();
    }
}; // struct serializer

/**
 * Template specfialization that call the serializer (and encoded) function of
 * a type, in this case the option for encoded_text struct.
 */
template <>
struct serializer<true>
{
    template <typename T>
    static auto serialize(T& v)
    {
        return v.serial_encoded();
    }
}; // struct serializer <true>

// ------------------------------- FUNCTION DEFINITIONS -----------------------

/**
 * Function template that uses the type trait defined to select the
 * serialization method. 
 */
template <typename T>
auto serialize(T& v)
{
    return serializer<i s_serialized_and_encoded<T>::value>::serialize(v);
} // serialize()

// ------------------------------ MAIN IMPLEMENTATION -------------------------
int main(int argc, char* argv[])
{
    std::cout << "Lesson 13: Your own type trait\n" << std::endl
              << "Checking if a type is  serialized and encoded: " << std::endl
              << "\tPlain text struct: " 
              << is_serialized_and_encoded<plain_text>::value << std::endl
              << " \tEncoded text struct: "
              << is_serialized_and_encoded<encoded_text>::value << std::endl
              << "\tInteger type: "
              << is_serialized_and_encoded<int>::value << std::endl
              << "\tString type: "
              << is_serialized_and_encoded<std::string>::value << std::endl;
    return 0;

} // main()