// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>
#include <memory>

// ------------- STRUCTS DEFINITIONS:

/*
 * EXPLICIT CONSTRUCTORS:
 * After C++11, you must specify 'explicit' if you don't want a converting 
 * constructor or operator.
 * You can also use it for  explicit conversion operators.
 * Usage:
 *  - explicit <class or struct> (<params>) : <assignations> {<process>}
 *  - explicit operator <type_operator> (<params>) { <process> };
 */
struct example_explicity
{
    explicit example_explicity(char const l) : letter(l) {}
    explicit operator bool() const { return letter != ' '; };

private:
    char letter;
};


// Common usage without explicit constructors:
struct no_explicity
{
    no_explicity() 
        { std::cout << "Base Constructor" << std::endl; }
    
    no_explicity(char const a) 
        { std::cout << "Constructor with a" << std::endl;}
    
    no_explicity(char const a,char const b) 
        { std::cout << "Constructor with a,b" << std::endl;}
    
    operator bool() const { return false; };
};

// ------------- CLASS DEFINITIONS:
// Class to ilustrate why you must use explicit conversion:
class text_buffer_implicit
{
public:
    text_buffer_implicit() 
        { std::cout << "Using void constructor." << std::endl; }
    
    text_buffer_implicit(size_t const length) 
        { std::cout << "Using constructor with size_t" << std::endl; }
    
    text_buffer_implicit(char const * const pointer) 
        { std::cout << "Using constructor with char pointer" << std::endl;}
    
    size_t size() const { return this->length; }
    operator bool() const { return true; }
    operator char * const () const { return this->word_ptr; }

private:
    size_t length;
    char * word_ptr;
};

// Examples with 'enum':
enum Stars {One, Two, Three, Four, Five};

// Class to ilustrate why you must use explicit conversion:
class text_buffer_explicit
{
public:
    explicit text_buffer_explicit() 
        { std::cout << "Using void constructor." << std::endl; }
    
    explicit text_buffer_explicit(size_t const length) 
        { std::cout << "Using constructor with size_t" << std::endl; }
    
    explicit text_buffer_explicit(char const * const pointer) 
        { std::cout << "Using constructor with char pointer" << std::endl;}
    
    // explicit size_t size() const { return this->length; } // --> Is not allowed for size_t
    explicit operator bool() const { return true; }
    operator char * const () const { return this->word_ptr; }

private:
    size_t length;
    char * word_ptr;
};



// -------------- FUNCTIONS PROTOTYPES DEFINITIONS: 
void use_exp(no_explicity const f);

int main()
{
    std::cout << "Module 01 - Lesson 11: " << std::endl;
    std::cout << "" << std::endl;

    // SHOWCASE: Depending on the params, the constructor should be...
    std::cout << "Example #1: Implicit conversion or constructors:" << std::endl;
    std::cout << "\t no_explicity s1; --> ";
    no_explicity s1;
    std::cout << "\t no_explicity s2 {}; --> ";
    no_explicity s2 {};
    std::cout << "\t no_explicity s3 ('a'); --> ";
    no_explicity s3 ('a');
    std::cout << "\t no_explicity s4 = 'b'; --> ";
    no_explicity s4 = 'b';
    std::cout << "\t no_explicity s5 { 'c' }; --> ";
    no_explicity s5 { 'c' };
    std::cout << "\t no_explicity s6 = { 'd' }; --> ";
    no_explicity s6 = { 'd' };
    std::cout << "\t no_explicity s7 ('a', 'c'); --> ";
    no_explicity s7 ('a', 'c');
    std::cout << "\t no_explicity s8 { 'b', 'b'}; --> ";
    no_explicity s8 { 'b', 'b'};
    std::cout << "\t no_explicity s9 { 'c' , 'a'}; --> ";
    no_explicity s9 { 'c' , 'a'};
    // When  using 'initializer_list', all the initializations will use the same constructor.

    // SHOWCASE: Constructor while in a function:
    std::cout << std::endl << "Example #2: Correct looks:" << std::endl;
    std::cout << "\t use_exp({}) --> ";
    use_exp({});
    std::cout <<"\t use_exp('z') --> ";
    use_exp('z');
    std::cout <<" \tuse_exp({ 'y', 'z' }) --> ";
    use_exp({ 'y', 'x' });

    // SHOWCASE: Using the operators defined for the class/struct:
    std::cout << std::endl << "Example #3: Bool declarations: " << std::endl;
    bool validExp = s1;
    if ( !s2 )
        { std::cout << "\t Define bool operator to use it with 'if' or 'if/else' statements" << std::endl; }
    std::cout << "\t It is not recommended to use operators that you haven't defined. " << std::endl;

    // SHOWCASE: Why should you prefer explicit conversion...
    std::cout << std::endl << "Example #4: Implicit conversion for a class (text_buffer_implicit): " << std::endl;
    std::shared_ptr<char> word_ptr;
    std::cout << "\t For 't1': ";
    text_buffer_implicit t1;
    std::cout << "\t For 't2(20)': ";
    text_buffer_implicit t2(20);
    std::cout << "\t For 't3(word_ptr.get())':  ";
    text_buffer_implicit t3(word_ptr.get());
    std::cout << "\t For 't4='a'':  ";
    text_buffer_implicit t4 = 'a';
    std::cout << "\t For 't5 = Stars::Three':  ";
    text_buffer_implicit t5 = Stars::Three;

    // SHOWCASE: Results for the explicit class modified...
    std::cout << std::endl << "Example #5: Implicit conversion for a class (text_buffer_explicit): " << std::endl;
    std::cout << "\t For 'et1: ";
    text_buffer_explicit et1;
    std::cout << "\t For 'et2(20)': ";
    text_buffer_explicit et2(20);
    std::cout << "\t For 'et3(word_ptr.get())': ";
    text_buffer_explicit et3(word_ptr.get());
    std::cout << "\t For 'et4 = text_buffer_explicit('x')': ";
    text_buffer_explicit et4 = text_buffer_explicit('x');
    std::cout << "\t For 'et5 = static_cast<text_buffer_explicit>(static_cast)<text_buffer_explicit>(Stars::Three)':  ";
    text_buffer_explicit et5 = static_cast<text_buffer_explicit>(Stars::Three);
    std::cout << "\t For 'et6 = text_buffer_explicit{ \"a\" }':  ";
    text_buffer_explicit et6 = text_buffer_explicit{ "a" };
    /*
    * text_buffer_explicit et7{'b'};
    * text_buffer_explicit et8('c'); //Still possible but wrong
    */
    return 0;
}

void use_exp(no_explicity const f)
{
    return;
}