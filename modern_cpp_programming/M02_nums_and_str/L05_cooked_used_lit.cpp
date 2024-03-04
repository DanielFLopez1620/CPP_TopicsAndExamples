// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++17

#include <iostream>

/**
 * Literals refers to built-in types that cannot be altered, in C++ (and ahead)
 * you can create your own literals for numerical, character and string types. 
 * Cooked literals refers to those processed by the compilers, and it will be
 * the focus here. They appeared in C++11, and some features have been added
 * over time.
 * 
 * The steps to consider a literal are:
 * 
 * 1. Define literals in a separate namespace to avoid clashes.
 * 2. Prefix using '_' the suffix.
 * 3. Define the literal operator, which must be related to one of these:
 * 
 *      T operator "" _suffix(unsigned long long int);
 *      T operator "" _suffix(long double);
 *      T operator "" _suffix(char);
 *      T operator "" _suffix(wchar_t);
 *      T operator "" _suffix(char16_t);
 *      T operator "" _suffix(char32_t);
 *      T operator "" _suffix(char const *, std::size_t);
 *      T operator "" _suffix(wchar_t const *, std::size_t);
 *      T operator "" _suffix(char16_t const *, std::size_t);
 *      T operator "" _suffix(char32_t const *, std::size_t);
 * 
 * Keep in mind that for integral literals the operator taks a unsigned long
 * long and the raw literal operator taks a const char*, for floating-point
 * literals you use long double and const char*, for character literals you
 * should use the appropriate operator depdending on the character type
 * (char, wchar_t, char16_t, char32_t) and for strings consider the type of
 * string (with a pointer) and the size.
 * 
 * You can compile and run this code with:
 * 
 *      g++ -std=c++17 L05_cooked_used_lit.cpp -o cooked_lit.out
 *      ./cooked_lit.out
 * 
 * NOTE: Do not forget to use namespace to prevent clash.
*/

#include <array>
#include <complex>
#include <chrono>
#include <string>

// Info #1: Creating literal by defining const expression.
namespace bytes_related
{
    constexpr size_t operator "" _MB(unsigned long long const size)
    {
        return static_cast<size_t>(size * 1024 * 1024);
    }
} 

// Info #2: Overriding operators in literals.
namespace packing
{
    enum class pack
    {
        kilogram,
        squared_meters,
        num_elements,
    };

    template <pack P>
    class quantity_pack
    {
        const double amount;
    public:
        constexpr explicit quantity_pack(double const a) : amount(a) {}
        explicit operator double() const { return amount; } 
    };

    template <pack P>
    constexpr quantity_pack<P> operator+(quantity_pack<P> const &p1, 
                                         quantity_pack<P> const &p2)
    {
        return quantity_pack<P>(
            static_cast<double>(p1) + static_cast<double>(p2));
    }

    template <pack P>
    constexpr quantity_pack<P> operator-(quantity_pack<P> const &p1,
        quantity_pack<P> const &p2)
    {
        return quantity_pack<P>(
            static_cast<double>(p1) - static_cast<double>(p2));
    }

    template <pack P>
    std::ostream& operator<<(std::ostream& os, quantity_pack<P> const &p1)
    {
        os << static_cast<double>(p1);
        return os;
    }

    namespace quantity_pack_literals
    {
        constexpr quantity_pack<pack::kilogram> operator "" _kg (
            long double const amount)
        {
            return quantity_pack<pack::kilogram> 
                { static_cast<double>(amount) };
        }

        constexpr quantity_pack<pack::kilogram> operator "" _kg (
            unsigned long long const amount)
        {
            return quantity_pack<pack::kilogram> 
                { static_cast<double>(amount) };
        }

        constexpr quantity_pack<pack::squared_meters> operator "" _m2 (
            long double const amount)
        {
            return quantity_pack<pack::squared_meters> 
                { static_cast<double>(amount) };
        }

        constexpr quantity_pack<pack::num_elements> operator "" _pcs (
            unsigned long long const amount)
        {
            return quantity_pack<pack::num_elements> 
                { static_cast<double>(amount) };
        }
    }
}


int main(int argc, char** argv)
{
    // Info #1: Using literal by calling our implementation.
    using namespace bytes_related;
    auto mb_size{ 2_MB };
    using byte = unsigned char;
    auto buffer = std::array<byte, 1_MB>{};
    std::cout << "Example of literal 2 MB to bytes: " << mb_size << std::endl;

    std::cout << std::endl;
    // Info #2:
    using namespace packing;
    using namespace quantity_pack_literals;

    std::cout << "Let's obtain the info of the package #1: " << std::endl;
    auto p1_kg{ 1_kg };
    auto p1_m2{ 0.25_m2 };
    auto p1_pcs{ 20_pcs };
    std::cout << "\tWeight: " << p1_kg << " kg" << std::endl << "\tArea: " 
              << p1_m2 << " m^2" << std::endl << "\tPieces: " << p1_pcs 
              << std::endl;

    std::cout << "Let's obtain the info of the package #2: " << std::endl;
    auto p2_kg{ 3.5_kg };
    auto p2_m2{ 0.2_m2 };
    auto p2_pcs{ 5_pcs };
    std::cout << "\tWeight: " << p2_kg << " kg" << std::endl << "\tArea: " 
              << p2_m2 << " m^2" << std::endl << "\tPieces: " << p2_pcs 
              << std::endl;
    
    std::cout << "Now let's sum the information of the packages:" << std::endl;
    auto pt_kg =  p1_kg + p2_kg;
    auto pt_m2 = p1_m2 + p2_m2;
    auto pt_pcs = p1_pcs + p2_pcs;
    std::cout << "\tWeight: " << pt_kg << " kg" << std::endl << "\tArea: " 
              << pt_m2 << " m^2" << std::endl << "\tPieces: " << pt_pcs 
              << std::endl;

    // Info #3: Additionally you can create literals for types like 
    // std::basic_string and std::basic_string_view with:

    using namespace std::string_literals;
    auto str1{  "Dan"s };
    auto str2{ L"Dan"s };
    auto str3{ u"Dan"s };
    auto str4{ U"Dan"s };
    using namespace std::string_view_literals;
    auto str5{ "Dan"sv };

    // For watching the results, you will need to override operator<<
    /* 
    std::cout << "Let's see the string literals: " << std::endl
              << "\tstd::string: " << str1 << std::endl
              << "\tstd::wstring: " << str2 << std::endl
              << "\tstd::u16string: " << str3 << std::endl
              << "\tstd::u32string: " << str4 << std::endl
              << "\tstd::string_view: " << str5 << std::endl;
    */



    return 0;
}