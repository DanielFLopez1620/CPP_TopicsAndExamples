# File name: stack.py
# Description: The python wrapper around the cstack library

"""
Python is interpreted, then there is no compilitation but rather an execution 
in time, so for the integration, it is needed to add that native library to C,
for that exits a framework that loads shared library objects which is the 
'ctypes'.

The steps needed for using it are simple:
1) Import ctypes
2) Define the input and outputs of the functions.
3) If you preffer wraps the implementation.

So, check the code below and review the implementation.

NOTE: The Wrapping in python, as the types tend to be infered, must include the
definition of the library shared, the param types and the return type.

For using the native implementation in Python, you can run:

    cd python
    LD_LIBRARY_PATH=$PWD/.. python stack.py
"""

import platform
from ctypes import * # Library needed to use external shared libraries

class value_t(Structure):
  """
  A class that interprets the size and the content of a value
  """
  _fields_ = [("data", c_char_p), ("len", c_int)]

class _NativeStack:
  """
  Private class that wraps the native implementation of the shared library
  """
  def __init__(self):
    """
    Constructor that load the library and wraps the methods of the custom C
    Stack. 
    """
    
    # Loading library present in platform, depending on the OS.
    self.stackLib = cdll.LoadLibrary(
            "libcstack.dylib" if platform.system() == 'Darwin'
            else "libcstack.so")

    # value_t make_value(char*, size_t) wrapping
    self._makevalue_ = self.stackLib.make_value
    self._makevalue_.argtypes = [c_char_p, c_int]
    self._makevalue_.restype = value_t

    # value_t copy_value(char*, size_t) wrapping
    self._copyvalue_ = self.stackLib.copy_value
    self._copyvalue_.argtypes = [c_char_p, c_int]
    self._copyvalue_.restype = value_t

    # void free_value(value_t*) wrapping
    self._freevalue_ = self.stackLib.free_value
    self._freevalue_.argtypes = [POINTER(value_t)]

    # cstack_t* cstack_new() wrapping 
    self._new_ = self.stackLib.cstack_new
    self._new_.argtypes = []
    self._new_.restype = c_void_p

    # void cstack_delete(cstack_t*) wrapping
    self._delete_ = self.stackLib.cstack_delete
    self._delete_.argtypes = [c_void_p]

    # void cstack_ctor(cstack_t*, int) wrapping
    self._ctor_ = self.stackLib.cstack_ctor
    self._ctor_.argtypes = [c_void_p, c_int]

    # void cstack_dtor(cstack_t*, deleter_t) wrapping
    self._dtor_ = self.stackLib.cstack_dtor
    self._dtor_.argtypes = [c_void_p, c_void_p]

    # size_t cstack_size(cstack_t*) wrapping 
    self._size_ = self.stackLib.cstack_size
    self._size_.argtypes = [c_void_p]
    self._size_.restype = c_int

    # bool_t cstack_push(cstack_t*, value_t) wrapping
    self._push_ = self.stackLib.cstack_push
    self._push_.argtypes = [c_void_p, value_t]
    self._push_.restype = c_int

    # bool_t cstack_pop(cstack_t*, value_t*) wrapping 
    self._pop_ = self.stackLib.cstack_pop
    self._pop_.argtypes = [c_void_p, POINTER(value_t)]
    self._pop_.restype = c_int

    # void cstack_clear(cstack_t*, deleter_t) wrapping 
    self._clear_ = self.stackLib.cstack_clear
    self._clear_.argtypes = [c_void_p, c_void_p]

class Stack:
  """
  Stack class that contains access to the private Native Class implementation.
  """
  def __enter__(self):
    """
    Method that links a the native stack implementation, while instancing
    inside one object to get access to the content.
    """
    self._nativeApi_ = _NativeStack()
    self._handler_ = self._nativeApi_._new_()
    self._nativeApi_._ctor_(self._handler_, 100)
    return self

  
  def __exit__(self, type, value, traceback):
    """
    Method that unlinks and destruct the objects related with the native
    implementation.
    """
    self._nativeApi_._dtor_(self._handler_, self._nativeApi_._freevalue_)
    self._nativeApi_._delete_(self._handler_)

  def size(self):
    """
    Getter of the size of the stack
    """
    return self._nativeApi_._size_(self._handler_)

  def push(self, item):
    """
    Push (add item) implementation to the C custom stack 
    """
    result = self._nativeApi_._push_(self._handler_,
            self._nativeApi_._copyvalue_(item.encode('utf-8'), len(item)));
    if result != 1:
      raise Exception("Stack is full!")

  def pop(self):
    """
    Pop (take out item) implementation of the C custom stack
    """
    value = value_t()
    result = self._nativeApi_._pop_(self._handler_, byref(value))
    if result != 1:
      raise Exception("Stack is empty!")
    item = string_at(value.data, value.len)
    self._nativeApi_._freevalue_(value)
    return item

  def clear(self):
    """
    Erase everything from the stack.
    """
    self._nativeApi_._clear_(self._handler_, self._nativeApi_._freevalue_)

if __name__ == "__main__":
  # With is used to try the stack as a file (that's why we implemented the 
  # __close__ and __enter__ methods). This gives the opprotunity to free 
  # the underlying native resources.
  with Stack() as stack: 
    # Add elements to the stack
    stack.push("Hello")
    stack.push("World")
    stack.push("!")
    print("Size after pushes:" + str(stack.size()))
    
    # Take out everything from the stack
    while stack.size() > 0:
      print(stack.pop())
    print("Size after pops:" + str(stack.size()))
    
    # Add elements again
    stack.push("Ba");
    stack.push("Bye!");
    print("Size before clear:" + str(stack.size()))
    
    # Clear and close
    stack.clear()
    print("Size after clear:" + str(stack.size()))
