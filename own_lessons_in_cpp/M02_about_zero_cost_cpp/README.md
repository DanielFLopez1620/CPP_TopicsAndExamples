# About Zero Cost C++

It is a pillar of modern C++ design, which aims to provide very high-level abstractions without costing extra performance. From this topic, Herb Sutter said "You don't pay for what you don't use, and what you do use, you couldn't hand-code faster." So, if an abstraction has overhead, it's not a proper abstraction.

It can be achieved by:

- **Compile-time resolution:** Templates, inline functions, constexpr and auto disappear at runtime.
- **No mandatory runtime components:** Avoiding runtime GC, VM or overhead from object systems.
- **ABI stability and predictability:** Full optimization and everything is deterministically.
- **Inlining + static dispatch:** If the compiler can inline o devirtualize something, the cost is eliminated.

Let's see briefly how it works and then go further:

1. Constructors and destructors with zero cost principles, so you must consider that the costs refers to what has been written.
2. Methods have no implicit runtime cost, so it is like calling a free function where you should avoid dynamic dispatch, hidden metadata, tracing, boxing and unboxing.
3. Value semantics have zero runtime overhead, so keep in mind rvalues and lvalues.
4. Move semantics and optimization enable zero-copy operations, which means that modern compilers optimize no copy, no move and no heap allocation if string optimization triggers.
5. Inline functions and templates are zero-cost abstractions, then you can optimize the generated machine output to avoid calls and additional generations.
6. Preferring lambdas without captures as it saves cost, because if something is captured it will generate a structure.
7. Keeping in mind the cost of virtual functions as they introduce v-tables, calls, indirections and more.

Now, let's go deeper with this topic.

## Objects

Now, in the case of objects... what we should consider in terms of cost? Well, you can keep in mind the next:

- **Use value semantics:** In order to have predictable lifetimes, store them on the stack and take advantage of the compiler trivial optimizations.

    ~~~C++
    struct Point
    {
        int x, y;
    };
    ~~~

- **Avoiding virtual methods:** Unless they are required, prefer not to so you can avoid the introduction of v-tables, indirect calls and RTTI. The better options are templates are CRTP and static polymorphism.

    ~~~C++
    template<class Vehicle>
    float sound(const Vehicle& v)
    {
        return r.sound();
    }
    ~~~

- **Easily inlinable statements:** Which means to implement small and trivial methods (for example, getters and setters of the object) avoiding virtual elements and pointer loads.

    ~~~C++
    class MyObject
    {
    public:
        int getNum() const
        {
            return num;
        }

        int setNum(int num)
        {
            this->num = num;
        }
    private:
        int num;
    }
    ~~~

- **Implement *final*:** So you can allow de-virtualization when implementing polymorphic classes.

    ~~~C++
    class Son final : Father
    {
        void study() override {}
    }
    ~~~

- **Avoid hidden allocations:** Which refers to keep in mind the next points:

  - Avoid hidden ```new``` inside constructors.
  - Do not use internal ```std::function``` without capturing.
  - Be careful with strings that resize frequently.
  - Prefer small buffers.
  - Take advantages of ```std::array```
  - Pre-reserve memory.

## Methods

If we talk about objects, we need to continue with methods, for this you can consider the next cases to reduce the costs of your programs:

- **```constexpr```and ```noexcept```:** Aiming to allow compile-time evaluation, inlining and const propagation.

    ~~~C++
    class Triangle
    {
    public:
        constexpr double  Area() const noexcept
        {
            return ((this->a*this->b)/2)
        }
    private:
        double a, b;
    };
    ~~~

- **Templates and inline methods:** This can reduce the cost and for trivial types, it means zero overhead.

    ~~~C++
    template<typename T>
    struct InterfaceGetter
    {
        T element;
        T get() const { return element; }
    }
    ~~~

- **Avoid type erasure unless required:** This means that some erasure abstractions like ```std::any```, ```std::function``` can add dynamic allocations or indirections, so you can instead use error codes, enums, concepts, auto returns or templates.

- **References or pointers, not copies:** Yeah, as you heard, avoid copies, mostly on non-trivial types.

~~~C++
void my_func(const CustomType c); // No copy
void my_func(CustomType c); // Copy
~~~

- **Be explicit when moves are required:** It is better as in zero-cost code you relay on the compiler knowing what are you intending.

~~~C++
auto var = std::move(another_var); // avoid copy
~~~

## Delegating constructors and destructors

In zero-cost we aim to eliminate repeated code and avoid unnecessary items that may add load to our execution. In the context of constructors and destructors, you may want to simplify them and add delegations.

This can be achieved on the context:

~~~C++
struct Vehicle
{
    int seats, wheels;

    Vehicle() : Vehicle(2, 2) {}
    Vehicle(int s, int w) : seats{s}, wheels{w}
}
~~~

Now, let's consider the next items when delegating:

- All cleanups should be in the destructor, so you allow it to be deterministic, inlined and even optimized when unused.

- Empty destructors are implicitly ```noexcept``` and optimizable, so if you can do it, make them default:

    ~~~C++
    struct Element
    {
        ~Element() = default;
    }
    ~~~

- Aim for member-initializer lists, not inside assignments:

    ~~~C++
    // No!
    struct Object()
    {
        var = 16;
    }

    // Yes!
    Object : var(16);
    ~~~

- Do not add high workload on construction/destruction elements. Make them trivial or very simple.

- Delegate instead of duplicate.

## Lambdas with/without captures

## Structure binding (destructing)

## Functions calls that are inlined (forced inline)

## If-init

## Templates (variadic, recursive)

## Standard algorithms

## Additional resources

- [Jason's Training Classes | Empty Create](https://articles.emptycrate.com/training.html#understanding-object-lifetime)
