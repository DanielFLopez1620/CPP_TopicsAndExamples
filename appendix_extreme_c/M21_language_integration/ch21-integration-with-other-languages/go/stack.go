// File name: stack.go
// Description: Go wrapper around the cstack library


/*
Finally, we will explore Golang, it provides an easy integration with native shared libraries.
It is called itself a system programming language as the future generation C or C++.

But, let's move on to what interest us, and it is a package called 'cgo' to call C code
and load the shared object files. So, go and check below, when you are done, you 
can execute: 

    cd go
    go build -o stack.out stack.go
    LD_LIBRARY_PATH=$PWD/.. ./stack.out

WHEN READY: Move to the nex module
*/
package main

/*
#cgo CFLAGS: -I..
#cgo LDFLAGS: -L.. -lcstack
#include <cstack.h>
*/
import "C" // Import C
import (
  "fmt"
)

// Create a handler struct to use the C custom stack
type Stack struct {
  handler *C.cstack_t
}

// New Stack function that wraps the C implementation
func NewStack() *Stack {
  s := new(Stack)
  s.handler = C.cstack_new()
  C.cstack_ctor(s.handler, 100)
  return s
}

// Destructor wrapped of the C implementation
func (s *Stack) Destroy() {
  C.cstack_dtor(s.handler, C.deleter_t(C.free_value))
  C.cstack_delete(s.handler)
}

// Wrapped getter of the size of the custom stack
func (s *Stack) Size() int {
  return int(C.cstack_size(s.handler))
}

// Wrapped push function of the C custom Stack
func (s *Stack) Push(item string) bool {
  value := C.make_value(C.CString(item), C.ulong(len(item) + 1))
  pushed := C.cstack_push(s.handler, value)
  return pushed == 1
}

// Wrapped pop function of the C custom Stack 
func (s *Stack) Pop() (bool, string) {
  value := C.make_value(nil, 0)
  popped := C.cstack_pop(s.handler, &value)
  str := C.GoString(value.data)
  defer C.free_value(&value)
  return popped == 1, str
}

// Wrapped clear all function of the C custom Stack
func (s *Stack) Clear() {
  C.cstack_clear(s.handler, C.deleter_t(C.free_value))
}

// Main implementation of Golang
func main() {

  // Create new stack
  var stack = NewStack()

  // Push elements
  stack.Push("Hello")
  stack.Push("World")
  stack.Push("!")
  fmt.Println("Stack size:", stack.Size())

  // Pop elements
  for stack.Size() > 0 {
    _, str := stack.Pop()
    fmt.Println("Popped >", str)
  }

  // Destroy
  stack.Destroy()
}
