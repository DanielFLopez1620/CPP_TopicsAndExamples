// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Do you know about brace-initialization? It was introduced in C++ and later
 * called uniform initialization. You will check some comparation thoughout
 * this code for what a proper initialization should be and how can they be
 * improved.
 * 
 * Down below you will watch examples using braces for uniform initalization
 * in different situations and with different types.
 * 
 * NOTE: If you do not know about POD, it comes from Plain Old Data, it refers
 * to trivial and standard layout (defaulted members by compiler). But after 
 * C++20 it is a deprecated concept in order to prefer the latter concepts 
 * (trivial and standard).
 * 
 * Also, keep in mind that you cannot initialize integers or floats directly
 * with braces. And it also happens with narrowing conversions like long double
 * to float or doubles, or unscoped enumerations. 
 * 
 * You can run this code with:
 * 
 *      g++ -std=c++20 L03_uniform_initialze.cpp -o init.out
 *      ./init.out
*/

// --------------------------- INCLUDES AND DEPENDENCIES ----------------------

#include <vector>   // For using dynamic arrays.
#include <map>      // For using pairs or key/value elements.

// --------------------------- CUSTOMS DEFINITION -----------------------------

/**
 * Simple class that has private attributes oriented to a question of an exam.
 */
class question
{
private:
    std::string q_text_;
    char correct_opt_;
public:
    //Let's implement some constructors
    question():q_text_(" "), correct_opt_(' ') 
    {   std::cout << "Question: Void constructor" << std::endl; }
    question(std::string q_text, char correct_opt)
        :q_text_(q_text), correct_opt_(correct_opt) 
    {   std::cout << "Question: User constructor" << std::endl; }
};

struct rectangle 
{
    float l1; 
    float l2;
};

void display_content(std::initializer_list<float> const);

// ----------------------------- MAIN IMPLEMENTATION -------------------------

int main(int argc, char* argv[])
{
    std::cout << "Lesson 3: Uniform initialization...\n" << std::endl;

    // Info #1: There are two types of initialization, one that is make direct
    // by using braces and other that is based on a copy.
    std::string text1("direct");
    std::string text2 = "copy";
    std::cout << "Text1: " << text1 << " initialization" << std::endl
              << "Text2: " << text2 << " initialization" << std::endl
              << std::endl;

    // Info #2: But, we want to create uniform initializations regardless the 
    // type, so we then use braces '{}' which can be used with direct or copy 
    // init:
    //      T <obj> {<other>};  For direct list init
    //      T <obj> = {<other>}; For copy list init.
    // And it can be achieved for std containers, dynamically allocated arrays,
    // arrays, build-in types and even user defined types.
    std::vector<int> my_int_vector {16, 20};
    std::map<int, char> idx_abc { {1, 'a'}, {2, 'b'}, {3, 'c'}};
    float* my_float_vector = new float[2]{1.6, 2.0};
    char my_char_array[3]{'D', 'a', 'n'};
    // Let's display their content...
    std::cout << "Uniform init experiments: " << std::endl << "\tInt Vector:";
    for( auto num : my_int_vector)
    {
        std::cout << num << ", ";
    }
    std::cout << std::endl << "Map (Int, Char)";
    for( auto& pair : idx_abc)
    {
        std::cout << "(" << pair.first << ", " << pair.second << "), ";
    }
    std::cout << std::endl << "Float Array: ";
    for(int i = 0; i < 2; i++)
    {
        std::cout << my_float_vector[i] << ", ";
    } 
    std::cout << std::endl << "Char Array";
    for(int j = 0; j < 3; j++)
    {
        std::cout << my_char_array[j] << ", ";
    }
    std::cout << std::endl << "Now let's watch for classes" << std::endl;
    question first_q{};
    question second_q{"Name?", 'D'};
    rectangle rect{1.6, 6.2};
    std::cout << "POD Type Rectangle: (" << rect.l1 << ", " << rect.l2
              << ")" << std::endl << std::endl;
    
    // Info #3: You can use std::initialize_list<T> for initialization of
    // standard containers, and it can also be used to overload functions
    // or methods to suppport more arguments.
    std::cout << "Initialization with list: " << std::endl;
    display_content({16, 20, 62});

    return 0;
}

/**
 * A simple function to display the content list passed.
 * 
 * @param list A collection of float elements.
*/
void display_content(std::initializer_list<float> const list)
{
    std::cout << "( ";
    for(auto const & element : list)
    {
        std:: cout << element << ", ";
    }
    std::cout << " )" << std::endl; 
}