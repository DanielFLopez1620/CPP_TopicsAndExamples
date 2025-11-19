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

## Methods

## Delegating constructors and destructors

## Lambdas with/without captures

## Structure binding (destructing)

## Functions calls that are inlined (forced inline)

## If-init

## Templates (variadic, recursive)

## Standard algorithms

## Additional resources

- [Jason's Training Classes | Empty Create](https://articles.emptycrate.com/training.html#understanding-object-lifetime)
