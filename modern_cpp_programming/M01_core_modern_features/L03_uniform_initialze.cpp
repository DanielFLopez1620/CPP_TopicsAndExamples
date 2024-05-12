// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20

#include <iostream>

/**
 * Do you know about brace-initialization? It was introduced in C++ and later
 * called uniform initialization. You will check some comparation thoughout
 * this code for what a proper initialization should be and how can they be
 * improved.
*/

#include <vector>
#include <map>

// Custom types and classes defined for this lesson
class question
{
private:
    std::string q_text_;
    char correct_opt_;
public:
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

int main(int argc, char* argv[])
{
    // Info #1: There are two types of initialization, one that is make direct
    // by using braces and other that is based on a copy.
    std::string text1("direct");
    std::string text2 = "copy";
    std::cout << "Text1: " << text1 << " initialization" << std::endl
              << "Text2: " << text2 << " initialization" << std::endl;

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
    std::cout << std::endl;



    return 0;
}