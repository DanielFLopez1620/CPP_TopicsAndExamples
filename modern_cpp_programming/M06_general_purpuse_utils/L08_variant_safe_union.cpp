// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Have you ever used unions in C++? If not, they are a special class that
 * can hold only one member at a time. It is similar to struct but all the
 * members share the same memory location, which means that the size of the
 * union comes from its larger type, one example of it is:
 * 
 *      union Data
 *      {
 *          int num;
 *          char letter;
 *          bool check;
 *      }
 *
 * It comes handy when you need memory eficcient like in embedded systems and
 * represent a value that may have multiple types. But it is usually not safe,
 * that is the reason std::variant appeared and it is the reason we will cover
 * it here.
 * 
 * std::variant is a type-safe union that also overcomes the drawback of the
 * union in terms of allowing different types additional to the POD and
 * explicit construction for non-POD types.
 * 
 * For using std::variant, make sure you imported the <variant> header.
 * 
 * It is a class template that models a type-safe union, that holds one value
 * of the specifieds at a time. To check if is is empty, you can use the
 * member function called valueless_by_exception().
 * 
 * The alternatives that doesn't support the std::variant are void, arrays
 * and containers, as the memory need to be reserved as its larger member.
 * And the first member must be by default constructible, if you do not
 * want to initalize it, you should consider using monostate, more info below.
 * 
 * When ready, compile and run this code with:
 * 
 *      g++ -std?c++20 L08_variant_safe_union.cpp -o variant.out
 *      ./variant.out
 */

#include <variant>

struct showcase
{
    char letter;

    explicit showcase(char const l) : letter(l) {}
};

int main(int argc, char* argv[])
{
    // Info #1: You can declare a std::variant, by using the template
    // specialization with the members types you want to consider,
    // remember that you can only use one at a time, to assign a value,
    // you assign it directly or by using constructors.
    std::variant<int, float, char> variant_d1;
    variant_d1 = 16;
    variant_d1 = 16.20f;
    variant_d1 = 'D';
    
    // Info #2: To modify the sotred value, use the member functions emplace()
    // and swap(), we have using them for std::any and std::optional, and the
    // usage is the same, just except that the change will "delete" the old
    // value and just store the present one.
    std::variant<char, std::string, showcase> variant_d2 ='d';
    variant_d2.emplace<showcase>('d');

    // Info #3: For getting the value, use the non-member functions std::get
    // (for direct getter) or std::get_if(for conditional getter). Do not
    // forget to implement directly the exception management to avoid problems
    // when accesing to the elements.
    std::cout << "Obtaining the value of a variant: " << std::endl;
    variant_d2.emplace<char>('f');
    auto got_letter = std::get<char>(variant_d2);
    std::cout << "\tGetting char from variant_d2: " << got_letter << std::endl
              << "\tGetting string from variant_d2: ";
    try
    {
        std::string got_string = std::get<std::string>(variant_d2);
    }
    catch(std::bad_variant_access const & e)
    {
        std::cerr << e.what() << std::endl;
    }
    if(auto str_ptr = std::get_if<std::string>(&variant_d2))
    {
        std::cout <<"\tGetting if string is present: " << *str_ptr 
                  << std::endl;
    }
    else
    {
        std::cout << "\tGetting if string is not present." << std::endl;
    }

    // Info #4: You can check with type is being used for the variant storage
    // with the index, and knowing the order you declared the types, for that
    // you can use the member function index().
    std::cout << "For the variant_d1, the types are int, flt and char"
              << ", then let's check the change of the type: " << std::endl
              << "\t When using int: ";
    variant_d1 = 16;
    std::cout << variant_d1.index() << "\n\tWhen using flt: ";
    variant_d1 = 16.20f;
    std::cout << variant_d1.index() << "\n\then using char: ";
    variant_d1 = 'D';
    std::cout << variant_d1.index() << std::endl;
        
    // Info #5: If you need to check that someone is using a certain
    // alternative, you can use std::hold_alternative().
    std::cout << "Checking alternatives with variant_d1: " << std::endl
              << "\tHolds int?: " << std::holds_alternative<int>(variant_d1)
              << std::endl << "\tHolds float?:"
              << std::holds_alternative<float>(variant_d1) << std::endl
              << "\tHolds char?: " << std::holds_alternative<char>(variant_d1)
              << std::endl;

    // Info #6: If you need a default or "empty" value, you can use the
    // placeholder std::monostate. 
    std::variant<std::monostate, int, char> mono_variant;
    std::cout << "Variants with default values: " << std::endl
              << "\tHas monovariant a default?: "
              << std::holds_alternative<std::monostate>(mono_variant)
              << std::endl;
     
    // Info #7: You can "visit" the stored value and make something according
    // to it by considering alternatives or lambda usage.
    std::visit([](auto&& arg) 
        {std::cout << "Using lambda with std::visit...\n\tValue:" << arg << std::endl; }, 
        variant_d1);
    

    return 0;
}