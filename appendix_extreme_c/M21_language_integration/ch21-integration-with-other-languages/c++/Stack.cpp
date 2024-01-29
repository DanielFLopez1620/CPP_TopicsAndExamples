/* File name: Stack.cpp

 * Description: A generic stack class wrapping the cstack functions. It also contains a test 
 * scenario to check the stack functionality.
 */

#include <string.h>

#include <iostream>
#include <string>

#include "cstack.h"

/**
 * When making an integration for C++, we can thought of it as an OOP extension of C, therefore,
 * it can use C objects easier than other languages.
 * 
 * One of our first matter will be the name mangling which support namescape and function
 * overloading. Here, our focus for compiler will be 'clang' and 'clang++', they both can be used
 * in C files, but there would be differences and warnings if you do it, for that you can use the 
 * a flag related with macros which give a sign for clang++ of a C code being compiled, the usage
 * is implemented below:
 * 
 *    #ifdef __cplusplus
 *    extern "C" {
 *    #endif
 *    ...
 *    #ifdef __cplusplus
 *    }
 *    #endif
 * 
 * If you want to learn more about this 'linkage specification', you can check:
 * 
 * - https://isocpp.org/wiki/faq/mixing-c-and-cpp
 * - https://stackoverflow.com/questions/1041866/what-is-the-effect-of-extern-c-in-c
 * 
 * Now, check the C++ implementation below, and place you attention in the how C++ wrapped the C
 * code previously mentioned.
 * 
 * For compilation, the C++ code is using C++11, for that we need a compliant compiler, then try:
 * 
 *    cd c++
 *    g++ -c -g -std=c++11 -I$PWD/.. Stack.cpp -o Stack.o
 *    g++ -L$PWD/.. Stack.o -lcstack -o cstack_cpp.out
 *    LD_LIBRARY_PATH=$PWD/.. ./cstack_cpp.out # Base running
 *    
 *    LD_LIBRARY_PATH=$PWD/.. valgrind --leak-check=full ./cstack_cpp.out # Valgrind check
 * 
 * Here are some comments, on the commands:
 *  * -std=c++11 specifies to use a C++11 compiler
 *  * -I -L are used for specifying custom includes and library directories
 *  * -lcstack is passed to the linker for searching and linking the libcstack.so library
 *  * valgrind can also be used to test the code against memory leaks.
 * 
 * WHEN READY: After finishing with C++, we will move to Java.
*/

// PROTOTYPE DEFINITONS (For various datatypes)
template<typename T>
value_t CreateValue(const T& pValue);

template<typename T>
T ExtractValue(const value_t& value);

// CLASS IMPLEMENTATION
template<typename T>
class Stack 
{
// Public class interface
public:
  /**
   * Wrapped constructor of the custom C stack implementation
   * 
   * @param pMaxSize Max size for objects to stack.
  */
  Stack(int pMaxSize) 
  {
    mStack = cstack_new();
    cstack_ctor(mStack, pMaxSize);
  }

  /**
   * Wrapped destructor of the custom C stack implementation
  */ 
  ~Stack() 
  {
    cstack_dtor(mStack, free_value);
    cstack_delete(mStack);
  }

  /**
   * Wrapped getter of the stack's size.
   * 
   * @return Assigned size to the stack
  */
  size_t Size() 
  {
    return cstack_size(mStack);
  }

  /**
   * Wrapped push of the custom C stack implementation
   * 
   * @param pItem Value to be treated and then stored in stack.
   * 
   * @throws an error message when the stack is full.
  */
  void Push(const T& pItem) 
  {
    value_t value = CreateValue(pItem);
    if (!cstack_push(mStack, value)) 
    {
      throw "Stack is full!";
    }
  }

  /**
   * Wrapped pop ofthe custo C stack implementation
   * 
   * @return Value that was on top of the stack.
   * 
   * @throws an error message whne the stack is empty.
  */
  const T Pop() 
  {
    value_t value;
    if (!cstack_pop(mStack, &value)) 
    {
      throw "Stack is empty!";
    }
    T toReturn = ExtractValue<T>(value);
    free_value(&value);
    return toReturn;
  }

  /**
   * Wrapped clear of the C custom stack implementation.
  */
  void Clear() 
  {
    cstack_clear(mStack, free_value);
  }

// Private interface class
private:
  // Pointer to custom c stack type, handle of an existing object in C
  cstack_t* mStack;
};

// Template specialization

/**
 * Templeate function (string specialization) for creating values by using a string passed.
 * 
 * @param pValue String with the info to store.
 * 
 * @return Info stored in a value object needed for usage in stack.
*/
template<>
value_t CreateValue(const std::string& pValue) 
{
  value_t value;
  value.len = pValue.size() + 1;
  value.data = (char *)malloc(value.len * sizeof(char));
  strcpy(value.data, pValue.c_str());
  return value;
}

/**
 * Template function (string specialization) for extracting the values and using them in C++
 * 
 * @param value Pointer to object where the value is stored.
 * 
 * @return String with the converted info.
*/
template<>
std::string ExtractValue(const value_t& value) 
{
  return std::string(value.data, value.len);
}

// MAIN 
int main(int argc, char** argv) 
{
  // Create array for messages
  Stack<std::string> stringStack(100);

  // Push content into array
  stringStack.Push("Hello");
  stringStack.Push("World");
  stringStack.Push("!");

  // Display info of stack
  std::cout << "Stack size: " << stringStack.Size() << std::endl;

  // Pop loop
  while (stringStack.Size() > 0) 
  {
    std::cout << "Popped > " << stringStack.Pop() << std::endl;
  }

  // Log info to check size after popping out.
  std::cout << "Stack size after pops: " <<
      stringStack.Size() << std::endl;

  // Make more push operations
  stringStack.Push("Bye");
  stringStack.Push("Bye");
  std::cout << "Stack size before clear: " <<
      stringStack.Size() << std::endl;

  // Clear stack (delete all and log)
  stringStack.Clear();
  std::cout << "Stack size after clear: " <<
      stringStack.Size() << std::endl;

  return 0;
}
