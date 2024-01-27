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
*/

template<typename T>
value_t CreateValue(const T& pValue);

template<typename T>
T ExtractValue(const value_t& value);

template<typename T>
class Stack {
public:
  // Constructor
  Stack(int pMaxSize) {
    mStack = cstack_new();
    cstack_ctor(mStack, pMaxSize);
  }

  // Destructor
  ~Stack() {
    cstack_dtor(mStack, free_value);
    cstack_delete(mStack);
  }

  size_t Size() {
    return cstack_size(mStack);
  }

  void Push(const T& pItem) {
    value_t value = CreateValue(pItem);
    if (!cstack_push(mStack, value)) {
      throw "Stack is full!";
    }
  }

  const T Pop() {
    value_t value;
    if (!cstack_pop(mStack, &value)) {
      throw "Stack is empty!";
    }
    T toReturn = ExtractValue<T>(value);
    free_value(&value);
    return toReturn;
  }

  void Clear() {
    cstack_clear(mStack, free_value);
  }

private:
  cstack_t* mStack;
};

// Template specialization
template<>
value_t CreateValue(const std::string& pValue) {
  value_t value;
  value.len = pValue.size() + 1;
  value.data = (char *)malloc(value.len * sizeof(char));
  strcpy(value.data, pValue.c_str());
  return value;
}

template<>
std::string ExtractValue(const value_t& value) {
  return std::string(value.data, value.len);
}

int main(int argc, char** argv) {
  Stack<std::string> stringStack(100);
  stringStack.Push("Hello");
  stringStack.Push("World");
  stringStack.Push("!");
  std::cout << "Stack size: " << stringStack.Size() << std::endl;
  while (stringStack.Size() > 0) {
    std::cout << "Popped > " << stringStack.Pop() << std::endl;
  }
  std::cout << "Stack size after pops: " <<
      stringStack.Size() << std::endl;
  stringStack.Push("Bye");
  stringStack.Push("Bye");
  std::cout << "Stack size before clear: " <<
      stringStack.Size() << std::endl;
  stringStack.Clear();
  std::cout << "Stack size after clear: " <<
      stringStack.Size() << std::endl;
  return 0;
}
