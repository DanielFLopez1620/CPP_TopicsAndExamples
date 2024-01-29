// File name: Main.java

/**
 * As it was said in the intro, java compiler uses Java bytecode and it is analogous ot the
 * Application Binary Interface (ABI), keep in mind that it will only run on a Java Virtual
 * Machine (JVM) which is written in C or C++, therefore it has the power to load and use the C
 * Standard Library.
 * 
 * NOTE: Bytecode is also used by scala, kotlin and groovy and are called JVM languages.
 * 
 * You cannot simply have a C code and call the functions in Jave (as there are separated 'native
 * methods'), but there is a interface called Java Native Interface (JNI) to load shared object
 * libraries, and we will take advantage of it in this code.
 * 
 */
package com.packt.extreme_c.ch21.ex1;

class NativeStack {

  // Loading stack library
  static {
    System.loadLibrary("NativeStack");
  }

  // Interfaces for wrapping memory managemnt from the custom C stack.
  public static native long newStack();
  public static native void deleteStack(long stackHandler);

  // Interfaces for wrapping the constructor and destructor from the custom C stack.
  public static native void ctor(long stackHandler, int maxSize);
  public static native void dtor(long stackHandler);

  // Interfaces for wrapping the stack functions from the custom C stack.
  public static native int size(long stackHandler);
  public static native void push(long stackHandler, byte[] item);
  public static native byte[] pop(long stackHandler);
  public static native void clear(long stackHandler);
}

interface Marshaller<T> {

  byte[] marshal(T obj);

  T unmarshal(byte[] data);
}

class Stack<T> implements AutoCloseable {
  private Marshaller<T> marshaller;
  private long stackHandler;

  public Stack(Marshaller<T> marshaller) {
    this.marshaller = marshaller;
    this.stackHandler = NativeStack.newStack();
    NativeStack.ctor(stackHandler, 100);
  }

  @Override
  public void close() {
    NativeStack.dtor(stackHandler);
    NativeStack.deleteStack(stackHandler);
  }

  public int size() {
    return NativeStack.size(stackHandler);
  }

  public void push(T item) {
    NativeStack.push(stackHandler, marshaller.marshal(item));
  }

  public T pop() {
    return marshaller.unmarshal(NativeStack.pop(stackHandler));
  }
  public void clear() {
    NativeStack.clear(stackHandler);
  }
}

class StringMarshaller implements Marshaller<String> {

  @Override
  public byte[] marshal(String obj) {
    return obj.getBytes();
  }

  @Override
  public String unmarshal(byte[] data) {
    return new String(data);
  }
}

public class Main {
  public static void main(String[] args) {
    try (Stack<String> stack = new Stack<>(new StringMarshaller())) {
      stack.push("Hello");
      stack.push("World");
      stack.push("!");
      System.out.println("Size after pushes: " + stack.size());
      while (stack.size() > 0) {
        System.out.println(stack.pop());
      }
      System.out.println("Size after pops: " + stack.size());
      stack.push("Ba");
      stack.push("Bye!");
      System.out.println("Size after before clear: " + stack.size());
      stack.clear();
      System.out.println("Size after clear: " + stack.size());
    }
  }
}
