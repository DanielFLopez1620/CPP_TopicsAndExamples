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
 * libraries, and we will take advantage of it in this code. So, go and check the classes
 * implemented and the comments.
 * 
 * TIP: Do not trust the Garbage Collector Mechanism.
 * 
 * The code only talks about the Java implementation, but you will also need to do some things with
 * the native part. As the definitions are outside Java, therefore you need to provide a way to
 * make sure the JVM finds them. 
 * 
 * For this case, the C library doesn't need assumpsitions to be used in JVM environments. And
 * let's make a brief example: If you need a 'func' call of C from Java and the definition is in the
 * file 'libfunc.so', we need to implement a native function in Java 'doFunc' but it will search
 * for it in Java, then we need an intermediary library or obj file 'libNativeLibrary.so' that 
 * contains the same symbols Java is looking for. For implementing this in the current example, you
 * can run:
 * 
 *    cd java
 *    mkdir -p build/headers
 *    mkdir -p build/classes
 *    javac -cp src -h build/headers -d build /classes \
 *    src/com/packt/extrem_c/ch21/ex17Main.java
 * 
 * If everything goes right, when you check the directories, you should see that the marshaller and
 * native classes appeared. The files .class contains the Java bytecode that will be used for
 * loading the classes into JVM instances. As these codes are machine generated, it is not
 * recommended to modify them, and they are intended to traslate and define the steps needed
 * to consider the C/C++ code. Finally, you will need to add the intermediate library like this:
 * 
 *    cd java/native
 *    g++ -c -fPIC -I$PWD/../.. -I$JAVA_HOME/include \
 *    -I$JAVA_HOME/include/linux NativeStack.cpp -o NativeStack.o
 *    g++ -shared -L$PWD/../.. NativeStack.o -lcstack -o libNativeStack.so
 * 
 * After all this, you can run the integration following the next:
 * 
 *    cd java/native
 *    LD_LIBRARY_PATH=$PWD/.. java -Djava.library.path=$PWD/native \
 *    -cp build/classes com.packt.extrem_c.ch21.ex1.Main
 * 
 * -Djava.library.path=... is used to add the path to the JVM so it can be found.
 * 
 * WHEN READY: After you reviewed this lesson, then you can go to the Python lesson for integration
 * with C.
 */

// Package paths
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
  /* 
   * The constructor implementation is static and it search for loading a shared obj
   * library file and try to match the methods.
   */
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

/**
 * Generic class that wraps the native methods exposed. It can be used for String, Point, Integer
 * and other specified types.
 * 
 * The Autoclosable inheritance is related with some resources having to be freed upon
 * destruction. Keep in mind that the Garbage Collector wouldn't be able to free the stack if is
 * not needed anymore,  therefore, with the close option (from AutoClosable), you can override 
 * implementations for this purpose.
 * 
 */
class Stack<T> implements AutoCloseable {

  // Marshaller object is used to serialize/deserialize methods' inputs arguments (from C stack)
  private Marshaller<T> marshaller;
  private long stackHandler;

  /**
   * Constructor that uses the exposed interface to instance a new object, while injecting the
   * marshaller.
   */
  public Stack(Marshaller<T> marshaller) {
    this.marshaller = marshaller;
    this.stackHandler = NativeStack.newStack();
    NativeStack.ctor(stackHandler, 100);
  }

  /**
   * Destructor override to make sure that the deletion of the stack is done correctly.
   * Inherited from AutoClosable.
   */
  @Override
  public void close() {
    NativeStack.dtor(stackHandler);
    NativeStack.deleteStack(stackHandler);
  }

  /**
   * Wrapped getter of the size of the stack.
   */
  public int size() {
    return NativeStack.size(stackHandler);
  }

  /**
   * Wrapped implementation of the push of the custom C stack.
   */
  public void push(T item) {
    NativeStack.push(stackHandler, marshaller.marshal(item));
  }

  /**
   * Wrapped implementation of the pop of the custom C stack.
   */
  public T pop() {
    return marshaller.unmarshal(NativeStack.pop(stackHandler));
  }

  /**
   * Wrapped implmentation to empty the custom C stack.
   */
  public void clear() {
    NativeStack.clear(stackHandler);
  }
}

/**
 * Martsheller implementation for Strings, as they are the ones predeterminated in the C custom
 * Stack functions. This will mix the byte and string (char arrays in C) implementations.
 */
class StringMarshaller implements Marshaller<String> {

  // Serialization
  @Override
  public byte[] marshal(String obj) {
    return obj.getBytes();
  }

  // Deserialization
  @Override
  public String unmarshal(byte[] data) {
    return new String(data);
  }
}

public class Main {
  public static void main(String[] args) {
    // "Try_with_resources" is used to execute code in a controlled way to check for exceptions.
    // In this case, the expection is related with the instance of the object that can use the
    // native interface of the C Library.
    try (Stack<String> stack = new Stack<>(new StringMarshaller())) {
      
      // Add elements to the stack
      stack.push("Hello");
      stack.push("World");
      stack.push("!");
      System.out.println("Size after pushes: " + stack.size());

      // Pop everything out
      while (stack.size() > 0) {
        System.out.println(stack.pop());
      }

      // Adding again elements
      System.out.println("Size after pops: " + stack.size());
      stack.push("Ba");
      stack.push("Bye!");
      System.out.println("Size after before clear: " + stack.size());

      // Clear everythink and check size
      stack.clear();
      System.out.println("Size after clear: " + stack.size());
    }
  }
}
