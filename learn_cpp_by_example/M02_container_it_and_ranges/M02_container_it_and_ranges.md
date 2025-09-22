# Containers, iterators and ranges

## Overview

In this module, you will learn about containers (mostly focused on vectors), range-based *for* loops, standard algorithms with containers, format, lambdas and views.

## Containers and vectors

Containers are related to sequences or collection of elements, they can be *vector*s, *map*s, *unordered map*s, among others. They contain elements and manage their own storage of those elements.

### Create and display a vector

For this lesson, check the code [L01_fill_container.cpp](/learn_cpp_by_example/M02_container_it_and_ranges/L01_fill_container.cpp).

~~~C++
#include <iostream>
#include <vector>

void create_triangle()
{
    std::vector<int> data { 1 };
    for (auto number : data)
    {
        std::cout << number << ' ';
    }
    std::cout << std::endl;
}

auto main() -> int
{
    create_triangle();
}
~~~

Some key points to consider in this lesson are:

- ```<vector>``` is the required library to use vectors, the dynamic container of interest in this module.

- The basic definition of a vector consist of ```std::vector < <type> > name { <values> };```.

- The initialization using curly braces is called **uniform initialization syntax**, this is recommended by ISO to avoid *narrowing* (potentially unsafe numeric conversions which may lead to data loss or unexpected behaviors.)

- You can use *range-based for* loops, it is as simple as ```for( auto <element> : <container>)```, and this can be easily interpreted in a traditional way like ```for ( auto position = <container>.begin(), position != <container>.end(), ++position)``` and the proper usage of the iterator position to obtain the element as ```std::cout << *position << ' ';```.

**NOTE:** As we introduced auto, we should talk of AAA (Almost Always Auto) which refers to "let the compiler deduce the type for you, unless there's a good reason not to" so you avoid redundancy, prevent mistakes (narrowing), create better with templates and lambdas, work consistently with modern APIs, guarantees initialization of variables, avoids implicit conversions, among others characteristics. Some exceptions you may consider include the usage of auto with *mutex*, *atomics* or types that have to be moveable, another exception include the multi-word forms.

## Useful resources

- [Getting started | ISO CPP](https://isocpp.org/get-started)

- [The Nightmare of Initialization in C++ | CPP Con 2018](https://youtu.be/7DTlWPgX6zs)

- [Almost Always Auto | Sutter's Mill](https://herbsutter.com/2013/08/12/gotw-94-solution-aaa-style-almSutter'sost-always-auto/)
