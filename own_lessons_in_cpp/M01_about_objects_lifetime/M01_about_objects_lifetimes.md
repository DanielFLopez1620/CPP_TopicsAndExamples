# Lessons on Object Lifetime in C++

This module aims to explore more about objects in C++ and deepen in the lifetime cycle of them.

## About RAII

It is one of the fundaments in C++, it refers to **Resource Acquisition Is Initialization** which meaning applies on the context of a design principle where resources are tied to the lifetime of the objects. So:

- You acquire resources in a constructor.
- You release resources in the destructor.

This also means that the resources are released when you exit a scope. So, you never forget to release it and you do not need to use *malloc* and *free*.

~~~C++
#include <fstream>
#include <string>

void writeToFile(const std::string& my_file)
{
    std::ofstream file(my_file);
    if(!my_file.is_open())
    {
        throw std::runtime_error("Error with file! Unable to open it.");
    }

    file << "A showcase on RAII\n";
}
~~~

Where is also RAII implemented? You can find it when using: *std::unique_ptr*, *std::shared_ptr*, *std::vector*, *std::lock_guard*, *std::fstream* and more...

## Standard object lifecycle and member variable lifecycle

First, the lifecycle of an object includes:

1. **Creation:** Refers to memory allocation. On one hand, if it is on the stack, memory is reserved automatically when enters a new scope. On the other hand, if it is on the heap, is is via *new* or smart pointers.

2. **Initialization:** When the constructor is called after the reservation, so RAII begins.

3. **Usage:** To achieve its purpose (store, access, invoke...).

4. **Destruction:** Refers to the cleanup, when going out of scope or resource is deleted, so RAII ends.

5. **Deallocation:** Memory is cleaned as it is reclaimed.

Second, the lifecycle of a member may have additional rules to consider:

- **Initialization order:** Members are initialized in the order they are declared in the class, so a common mismatch can be:

~~~C++
class Point2D
{
    int x;
    int y;

public:
    Point2D() : y(10), x(y) {} // Invalid, it can have undefined behavior
    Point2D() : x(10), y(x) {} // Valid, based on order
};
~~~

- **Destruction order:** It is inverted, so if you constructed as A, B, C. Then, the destruction goes C, B, A.

- **Static members:** A static object belong to the class in general, not a certain instance. So, they have static storage (related with the program lifetime), therefore it is only constructed and destroyed once.

Third, let's proceed with an example that concludes this lesson:

~~~C++
#include <iostream>

struct File
{
    File(const char* name) { std::cout << "Opening " << name << "\n"; }
    ~File() { std::cout << "Closing file\n"; }
};

struct Logger
{
    Logger() { std::cout << "Logger created\n"; }
    ~Logger() { std::cout << "Logger destroyed\n"; }
};

class Application
{
    Logger log;        // constructed first
    File configFile;   // constructed second
public:
    Application() : log(), configFile("settings.ini")
    {
        std::cout << "Application running\n";
    }
    ~Application() { std::cout << "Application shutting down\n"; }
};

int main()
{
    Application app;
}
~~~

## Useful Resources

- [Jason's Training Classes on C++ | Empty Create](https://articles.emptycrate.com/training.html#understanding-object-lifetime)