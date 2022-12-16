// BASED ON THE "MODERN C++  PROGRAMMING COOKBOOK - 2 EDITION"
// Code was tested with g++ in C++20
// Made by Daniel Lopez

#include <iostream>

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

int main()
{
    std::cout << "Module 01 - Lesson 11: " << std::endl;
    std::cout << "" << std::endl;

    std::cout << "Example #1: Implicit conversion or constructors:" << std::endl;
    std:: cout << "no_explicity s1; --> ";
    no_explicity s1;
    std:: cout << std::endl << "no_explicity s2 {}; --> ";
    no_explicity s2 {};
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s3 ('a');
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s4 = 'b';
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s5 { 'c' };
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s6 = { 'd' };
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s7 ('a', 'c');
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s8 { 'b', 'b'};
    std:: cout << std::endl << "no_explicity s3 ('a'); --> ";
    no_explicity s9 { 'c' , 'a'};

    return 0;
}