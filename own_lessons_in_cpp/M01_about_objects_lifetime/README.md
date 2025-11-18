# Lessons on Object Lifetime in C++

This module aims to explore more about objects in C++ and deepen in the lifetime cycle of them.

The full demo that summarizes the learnings of this section is [L01_about_objects.cpp](/own_lessons_in_cpp/M01_about_objects_lifetime/L01_about_objects.cpp). You can try it with:

~~~bash
g++ -std=c++20 L01_about_objects.cpp -o about_objects.out
./about_objects.out
~~~

Now... let's get started with object lifetime!

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

On one hand, **LValues** refers to something that has a name or address (so you can take a pointer (&) of it). On the other hand, **RValues** refers to something temporary, something that doesn't persist beyond the definition.

~~~C++
int x = 16;

// LValue
int& lref = x;

// RVAlue
int&& rref = 20;
~~~

Why does this matter? Easy, when programming you need to consider *copies* (can be expensive) and *moves* (can be cheap). So, keep this in mind when working with variables, classes and objects.

## Comparing ```std::move``` and ```std::forward```

On the first side, ```std::move``` cast its argument into an **rvalue** reference (it is like stealing something after it isn't required anymore there). On the second side, ```std::forward``` is related with forwarding into templates so it is able to cast conditionally for **rvalue** or **lvalue**.

```std::move``` is used to explicitly allow a move constructor or move assignment operator instead of a copy, or when returning large objects to avoid copies.

~~~C++
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string s = "String to move";
    std::vector<std::string> v_str;

    v_str.push_back(s);             // Copy
    v_str.push_back(std::move(s));  // Move
}
~~~

```std::forward``` is more related with templates and universal references (T&&) and it ensure you do not copy when requiring a move.

~~~C++
#include <iostream>
#include <utility>

void display(const std::string s)
{
    std::cout <<  "Lvalue overload: " << s << "\n";
}

void display(std::string&& s)
{
    std::cout << "Rvalue overload: " << s << "\n";
}

template <typename T>
void wrapper(T&& arg)
{
    display(std::forward<T>(arg));
}

int main()
{
    std::string text = "Which one am I?";

    wrapper(text);
    wrapper("And this one?");
}
~~~

As an additional clarification, keep in mind that:

- ```T&``` is  a lvalue reference.
- ```T&&``` is an rvalue reference.
- ```const T&``` can be both.

### Bad usages of ```std::move```

Yeah, let's clarify this, on the next cases:

- Moving something still required in other part:

    ~~~C++
    std::string s1 = "hi";
    std::string s2 = std::move(s1);

    std::cout << s1; // Unspecified
    ~~~

- Moving when it is cheaper to copy (mostly on trivial types)

    ~~~C++
    float num = 16;
    float val = std::move(num); // Ineffective
    ~~~

- Moving too early or not considering the compiler, as you may elude the **RVO** (return value optimization) and may end up slowing the process down.

    ~~~C++
    std::string set_msg()
    {
        std::string msg = "Msg";
        return std::move(msg);
    }
    ~~~

- Forgetting ```std::move``` is just a cast, so do not try moving consts or related.

    ~~~C++
        std::string s1 = "not constant";
        const std::string& cref = s1;

        std::string s2 = std::move(cref);
    ~~~

## Passing and returning in functions

We have already talked about object lifetime, but.. what if you have to consider the object to be passed to a function?

Let's review the passing values to functions.

- **Pass by value:** Copies or moves the object, so the function has its own copy and modifications do not affect the caller.

~~~C++
void function(Object obj);
~~~

- **Pass by reference:** Passes an alias to the callers object (no copy, no move), so the lifetime is still linked to the caller.

~~~C++
void function(Object& onj);
~~~

- **Pass by const reference:** Recommended for large objects, do not implements copy and avoid moves. Then, it can bind to lvalues and rvalues.

~~~C++
void function(const Object& obj);
~~~

- **Pass by rvalue reference:** It gets a reference to a temporary object (or explicit cast, for example, **std::move**), often used in move constructors.

~~~C++
void function(Object&& obj);
~~~

But... what about the returns? Are they linked to the function or what happens here? Let's consider some cases:

- **Return by value:** It is the default choice, related with **RVO** and mandatory copy elision.

~~~C++
Obj function()
{
    Obj o;
    return o;
}
~~~

- **Return by reference:** Returns an existing value, so you must ensure the object outlives the reference and you should avoid exporting locals.

~~~C++
Obj& function(Obj% o)
{
    return o;
}
~~~

- **Return by constant reference:** Similar to the return by reference one, but the function cannot modify the value.

- **Return by rvalues:** Rare in practice and only seen in low-level library code, as in high level most of the temporaries are bound to values anyway.

But, now... how is this related with the lifetime of an object? It will depend on how it is passed/returned:

- **By value:** A new object is created (copy or move), the lifetime will be managed inside the callee.

- **By reference:** No new object, just an alias so the lifetime is still managed by the caller.

- **By constant reference:** Same as previous one, but just read-only.

- **By rvalue reference:** Allow functions to mutate or steal a temporary, but lifetime is still with the caller.

- **Return by value:** Mostly avoiding copies, to maintain it safe and efficient.

- **Return by reference:** The caller just borrows the object's lifetime.

So, still be careful when considering the object lifetime and do not forget about **RAII**.

## Passing and returning in lambdas

If we talk about functions, we cannot let aside the lambdas. So, let's learn more.

Lambdas in this context can be understood as hidden objects, check the following example:

~~~C++
// Original lambda
auto l = []{ std::cout <<"Lambda\n"; };

// Interpreted expression
struct UniqueName
{
    void operator()() const
    {
        std::cout << "Lambda\n";
    }
}
~~~

So, a **lambda expression** creates a temporary object, so the lifetime of the variables created inside are controlled similarly to functions and objects we have already checked on. But... what about captures?

- **Capture by value [=] or [var]**: The lambda creates a copy when it is created, so it will leave as long as the lambda lives.

~~~C++
#include <iostream>
#include <functional>

int main()
{
    int y = 16;

    auto value_lambda = [y](){ std::cout << "y = " << y << "\n"; }
    y = 20;
    value_lambda() // Prints 16

    return 0,
}
~~~

- **Capture by reference [&] or [&var]**: It only stores a reference, in this cases do not try persistent actions like:

~~~C++
#include <iostream>
#include <functional>

std::function<void()> ref_lambda()
{
    int num = 16;
    return [&](){ std::cout << "Num: " << num << "\n"; }
}

int main()
{
    auto not_recommended = ref_lambda();
    not_recommended(); // Possible call problem
    return 0;
}
~~~

- **Mixed captures [=, &var] or [&,x]**: Which refers at where you mix captures by value and reference.

For all these, keep in mind that:

- If you store (copy) a variable in a lambda, the lifetime is tied to that object.
- If you capture a value by reference, ensure that the variable lives at least as long as the lambda lives.
- Be careful with copies as they tend to be more expensive.

## Memory model and object lifetime

Yeah, let's continue with more about memory an objects. When we talk about memory model, it includes when the object exists, how and when memory is created or destroyed, what operations are safe in multithreaded programs and what counts as *Undefined Behavior*(UB).

In the case of the lifetime, it relates with:

1. **Storage allocated:** Memory is reserved.
2. **Construction begins:** Construct runs and the object is initialized.
3. **Usage:** Whatever it has to do, happens.
4. **Destruction:** Destructor runs and the lifetime ends.
5. **Storage reclaimed:** Memory is released.

Now, when integrating these two concepts, you should keep in mind that:

- You must not access an object outside its lifetime.
- Optimizers assume you never create UBs.
- Be careful with happens-first relationships (like thread cases) to avoid race conditions or data races.

Some problems you must avoid includes:

- Reference to a destroyed variable (**dangling pointer**):

    ~~~C++
    int* ptr;
    {
        int num = 16;
        ptr = &num;
    }
    std::cout << *ptr;
    ~~~

- Use a resource after it is freed:

    ~~~C++
    auto* ptr = new double(16.20)
    delete ptr;
    std::cout << *ptr;
    ~~~

- Accessing after destructor:

    ~~~C++
    class Obj
    {
        ~Obj() { std::cout <<"Object has been destroyed\n"; }
    }

    obj = Obj();
    obj->~Obj();
    std::cout << "Wait! What?\n";
    obj->~Obj();
    ~~~

- Returning references to locals:

    ~~~C++
    double& bad_double()
    {
        int num = 16;
        return num;
    }
    ~~~

So, you have been warned, avoid these common errors when programming on C++.

## Polymorphism types

Polymorphism refers to different forms a function can take in terms of param to do an action, like a common interface. There are two types:

- **Compile-time polymorphism**: Which is implemented by function overloading, templates and **CRTP** (Curiously Recurring Template Pattern).

- **Runtime polymorphism**: It is related with virtual functions and inheritance, with indirections.

Let's focus on the second one, with an example of virtual functions:

~~~C++
#include <iostream>
#include <memory>
#include <vector>

struct Vehicle
{
    virtual void sound() const { std::cout << "Pending sound!\n"; }
    virtual ~Vehicle() = default;
};

struct Motorcycle : Vehicle
{
    void sound() const override { std::cout << "Beep!\n"; }
}

struct Car : Vehicle
{
    void sound() const override { std::cout << "BEEP!\n"; }
}

int main()
{
    std::vector<std::unique_ptr<Vehicle>> collection;

    collection.push_back(std::make_unique<Car>());
    collection.push_back(std::make_unique<Motorcycle>());

    for(const auto& c : collections)
    {
        collection->sound();
    }

    return 0;
}
~~~

Then, this virtual implementations are due to inheritance, where the base pointer of type *Vehicle* will call the right function at runtime by considering a vtable, so yuo can store mixed objects in the same container.

This can add some benefits like flexibility, indirection (small runtime lookup) and extensibility (Derived types), but you have to consider some disadvantages like memory impact and need for virtual destructors.

## Notes on optimization

Have you heard of ```-O2``` or ```-O3```? No, do not worry, let's give some insights on optimization.

You can pass optimization instructions to the compiler on **g++** and **clang++**, so it will act more or less aggressive. The options are:

- ```-O0```: No optimization, oriented for debugging.
- ```-O1```: Some optimization, but still debug-friendly.
- ```-O2```: Standard that balances speed and compile time.
- ```-O3```: Aggressive optimization, includes inlining, vectorization, loop unrolling.
- ```-Ofast```: So aggressive that can ignore standards and floating point accuracy.

For benchmarking, it is recommended to test ```-O2``` or ```-O3``` and for debugging, the first two should be fine.

## Rules of Thumb

Keep in mind the next rules when programming:

1. Think if the object is alive by now.
2. Match allocation & deallocation
3. Do not assume that memory existence is equal to object existence
4. If applying multithreading, consider using atomic, mutex and barriers.
5. Prefer RAII to handle object's lifetime.

## Useful Resources

- [Jason's Training Classes on C++ | Empty Create](https://articles.emptycrate.com/training.html#understanding-object-lifetime)

- [Polymorphism in C++ |  Geek for geeks](https://www.geeksforgeeks.org/cpp/cpp-polymorphism/)

- [Value categories (lvalues and rvalues) | Learn C++](https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/)
