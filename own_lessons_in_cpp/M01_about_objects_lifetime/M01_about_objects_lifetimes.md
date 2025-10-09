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
    Logger log;
    File configFile;
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

## Why to limit a variable scope?

We already checked about RAII, and the lifecycle of variables. Now, let's focus on the reasons.

1. **Clarity:** To ensure a variable only exists where and when it is relevant and avoid the thinking of "Is this variable still alive here?"

2. **Prevent bugs:** As you focus on where the variable is important, you keep it from using elsewhere as it can have name conflicts or a improper value in other scope.

3. **Resource management:** Going back to RAII, as the scope finish, the resource is freed so you ensure a proper resource management.

4. **Optimization:** For a variable located only in a scope, the compiler can reuse or stack space more effectively.

## Limit variable scope

There are more considerations to consider when limit the scope, let's proceed with the most common ones:

- Only declare variables where they are first required.

    ~~~C++
    void process()
    {
        int x = 16;
        double y = 20;
    }
    ~~~

- Use the inner scopes, also known as the brackets {}.

    ~~~C++
    void add_log_file
    {
        {
            std::ofstream log("log.txt");
            log << "Log: It is a mess!";
        }
        std::cout << "Added log" << std::endl;
    }
    ~~~

- Take advantage of *if* and *loop* scopes: 

    ~~~C++
    if(auto it = map.find(key); it != map.end())
    {
        std::cout << it->second;
    }
    ~~~

You can follow this, and implement the RAII approach better.

## The As-If Rule

This rule applies more for the compiler, but you should keep it present. It refers to: "The compiler may perform any optimization or transformation, as if the observable behavior of the program is unchanged"

What are is *behaviors*? They can be writing to stdout/stderr, modifying volatile variables, File and Network I/O and syncs with threads.

A simple example can be:

~~~C++
// Before
for(int = 0; i < 100; ++i)
{
    id = 16;
}

// After
id = 16;
~~~

Then, make sure to follow RAII and keep in mind the compiler will do its work to guarantee behavior consistency.

## Notes on Lvalues and Rvalues

On one hand, **LValues** refers to something that has a name or address (so you can take a pointer (&) of it). On the other hand, **RValues** refers to something temporary, something that doesn't persist beyond the defintion.

~~~C++
int x = 16;

// LValue
int& lref = x;

// RVAlue
int&& rref = 20;
~~~

Why does this matter? Easy, when programming you need to consider *copies* (can be expensive) and *moves* (can be cheap). So, keep this in mind when working with variables, classes and objects.

## Comparing ```std::move``` and ```std::forward```

## Useful Resources

- [Jason's Training Classes on C++ | Empty Create](https://articles.emptycrate.com/training.html#understanding-object-lifetime)
