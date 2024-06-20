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
 * Check the info below to understand how to implement cooked literals,
 * indicate voerrides for them, display them in a proper way, and also use
 * string literals and chrono 
 * 
 * You can compile and run this code with:
 * 
 *      g++ -std=c++17 L05_cooked_used_lit.cpp -o cooked_lit.out
 *      ./cooked_lit.out
 * 
 * NOTE: Do not forget to use namespace to prevent name clashing and name
 * conflicts.
*/

// ------------------  REQUIRED HEADERS ---------------------------------------

#include <array>   // For managing contiguous array, including operators
#include <complex> // For using complex numbers (real and imaginary part)
#include <chrono>  // Related with time tracking in different precisions.
#include <string>  // Usage of string and char arrays.
#include <codecvt> // For conversion of character strings (wide and multibyte)

// ----------------- CLASS AND STRUCT DEFINITIONS -----------------------------

// Info #1: Creating literal by defining const expression, for this you use a
// constexpr and the usage of the ' operator "" ' and adding the suffix. The
// usage of this definition can be checked on the main.
namespace bytes_related
{
    constexpr size_t operator "" _MB(unsigned long long const size)
    {
        return static_cast<size_t>(size * 1024 * 1024);
    }
} 

// Info #2: Overriding operators in literals, for this we will take advantage
// of enumerations, then define the literals and then use templates to override
// the operator + and - to allow this add and substract base operations. You
// can check an example on the main.
namespace packing
{
    // Enumeration defined for later implementation of each enumerated value
    // with a literal.
    enum class pack
    {
        kilogram,
        squared_meters,
        num_elements,
    };

    // Class definition as a generic implementation with a construct to assign
    // the class quantity (corresponding to the enumerations idea).
    template <pack P>
    class quantity_pack
    {
        // Generic value that can refer to kg, m² or #
        const double amount;
    public:

        /**
         * User defined constructor to initialize a generic amount.
         * 
         * @param a Amout that will be specialized later.
         */
        constexpr explicit quantity_pack(double const a) : amount(a) {}

        /**
         * Caster definition of operator double, that just return
         * the same amount.
         * 
         * @return Generic amount as a double value.
        */
        explicit operator double() const { return amount; } 
    };

    /**
     * Define the sum of elements based on quantities that must be of the
     * same specialization.
     * 
     * @param p1 Pointer to quantity pack 1
     * @param p2 Pointer to quantity pack 2
     * 
     * @return A quantity pack with the amount attribute as the sum of the 
     * two elements.
     */
    template <pack P>
    constexpr quantity_pack<P> operator+(quantity_pack<P> const &p1, 
                                         quantity_pack<P> const &p2)
    {
        return quantity_pack<P>(
            static_cast<double>(p1) + static_cast<double>(p2));
    } // operator+ quantity_pack

    /**
     * Define the difference of elements based on quantities that must be of 
     * the same specialization.
     * 
     * @param p1 Pointer to quantity pack 1
     * @param p2 Pointer to quantity pack 2
     * 
     * @return A quantity pack with the amount attribute as the difference of
     * the two elements.
     */
    template <pack P>
    constexpr quantity_pack<P> operator-(quantity_pack<P> const &p1,
        quantity_pack<P> const &p2)
    {
        return quantity_pack<P>(
            static_cast<double>(p1) - static_cast<double>(p2));
    } // operator- quantity pack

    /**
     * Defintion to allow displaying of the pack by using out stream.
     *  
     * @param os Ostream to use for printing.
     * @param p1 Pointer to generic quantity pack to display.
     * 
     * @return Ostream with the info to be displayed attached.
     */
    template <pack P>
    std::ostream& operator<<(std::ostream& os, quantity_pack<P> const &p1)
    {
        os << static_cast<double>(p1);
        return os;
    } // operator<< quantity pack

    // Namespace for specialization with literals
    namespace quantity_pack_literals
    {
        /*
         * Kilogram suffix specialization for floating type
         * 
         * @param amount Double amount intended as kilogram.
         * 
         * @return Quantity pack object specialized as kilogram.
         */
        constexpr quantity_pack<pack::kilogram> operator "" _kg (
            long double const amount)
        {
            return quantity_pack<pack::kilogram> 
                { static_cast<double>(amount) };

        } //  operator ""_kg quantity_pack

        /*
         * Kilogram suffix specialization for integer type
         * 
         * @param amount Long integer amount intended as kilogram.
         * 
         * @return Quantity pack object specialized as kilogram.
         */
        constexpr quantity_pack<pack::kilogram> operator "" _kg (
            unsigned long long const amount)
        {
            return quantity_pack<pack::kilogram> 
                { static_cast<double>(amount) };

        } // operator ""_kg quantity_pack 

        /*
         * Square meters suffix specialization for double type
         * 
         * @param amount Double amount intended as square meters.
         * 
         * @return Quantity pack object specialized as m².
         */
        constexpr quantity_pack<pack::squared_meters> operator "" _m2 (
            long double const amount)
        {
            return quantity_pack<pack::squared_meters> 
                { static_cast<double>(amount) };

        } // opeartor ""_m2 quantity_pack

        /*
         * Number of elements suffix specialization for floating type
         * 
         * @param amount Integer amount intended as pieces.
         * 
         * @return Quantity pack object specialized as pieces.
         */
        constexpr quantity_pack<pack::num_elements> operator "" _pcs (
            unsigned long long const amount)
        {
            return quantity_pack<pack::num_elements> 
                { static_cast<double>(amount) };

        } // operator "" _psc quantity_pack
    }
}

// ------------------------------ MAIN IMPLEMENTATION -------------------------
int main(int argc, char** argv)
{
    std::cout << "Lesson 5: Cooked user literals definitions...\n" << std::endl;
    
    // Info #1: Using literal by calling our implementation.
    using namespace bytes_related;
    auto mb_size{ 2_MB };
    using byte = unsigned char;
    auto buffer = std::array<byte, 1_MB>{};
    std::cout << "Example of literal 2 MB to bytes: " << mb_size << std::endl 
              << std::endl;

    // Info #2: Using custom defined literals and check operations.
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
    // std::basic_string and std::basic_string_view with, keep in mind that for
    // the implementation you will need to override oeprator << or use diffent
    // ostream options.

    using namespace std::string_literals;
    auto str1{  "Dan"s };
    auto str2{ L"Dan"s };
    auto str3{ u"Dan"s };
    auto str4{ U"Dan"s };
    using namespace std::string_view_literals;
    auto str5{ "Dan"sv };

    std::string utf8_16(str3.begin(), str3.end());
    std::string utf8_32(str4.begin(), str4.end());
    
    std::cout  << "Let's see the string literals: " << std::endl
               << "\tstd::string: " << str1 << std::endl;
    std::wcout << "\tstd::wstring: " << str2 << std::endl;
    std::cout  << "\tstd::u16string: " <<  utf8_16 << std::endl 
               << "\tstd::u32string: "  << utf8_32 << std::endl
               << "\tstd::string_view: " << str5 << std::endl;

    // Info 4: You can also use literals with chronos for time related
    // operations, which type would be std::chrono::duration<long long>, the 
    // operators can be operator""h (hours), operator""min (minutes), 
    // operator""s (seconds), operator""ms (miliseconds), operator""us 
    // (microseconds).
    using namespace std::chrono_literals;
    auto timer {16h + 42min + 16s};
    std::cout << "Chrono duration of 16h 42m 16s is: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(timer).count() 
        << " ms" << std::endl;

    return 0;

} // main