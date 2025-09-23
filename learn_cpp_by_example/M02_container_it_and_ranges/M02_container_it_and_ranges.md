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

- Be careful with declarations like ```auto data = std:::vector{}``` as it may fail to compile due to not having enough info to deduce the type.

**NOTE:** As we introduced auto, we should talk of AAA (Almost Always Auto) which refers to "let the compiler deduce the type for you, unless there's a good reason not to" so you avoid redundancy, prevent mistakes (narrowing), create better with templates and lambdas, work consistently with modern APIs, guarantees initialization of variables, avoids implicit conversions, among others characteristics. Some exceptions you may consider include the usage of auto with *mutex*, *atomics* or types that have to be moveable, another exception include the multi-word forms.

With that say, we have covered an intro to the usage of vectors, but let's explore it with a better implementation, by using the Pascal Triangle.

**NOTE:** If you have forgotten about the Pascal Triangle, it is the triangle that is formed by the sum of the of the previous level's digit, you can explore more of it in [Pascal Triangle](https://www.mathsisfun.com/pascals-triangle.html)

This triangle can extend as far as we want, but talking in computation there are limits, for example, to consider a max value for integers you can use:

~~~C++
// std::numeric_limits< <type> >::max()
std::numeric_limits<int>::max()

// It returns 2,147,483,647
~~~

Another limit, can refer to format, as our screen has a limit and if we surpass the line limit, our triangle will start mixing around on the lines.

To implement this in code, let's focus on single-responsibility functions:

- **Next row**:

    ~~~C++
    std::vector<int> get_next_row(const std::vector<int>& previous_row)
    {
        std::vector next_row { 1 };
        if (previous_row.empty());
        {
            return next_row;
        }
        for (size_t i = 0; i+1 < previous_row.size(); ++i)
        {
            next_row.emplace_back(previous_row[i] + previous_row[i + 1]);
        }
        next_row.emplace_back(1);
        return next_row;
    }
    ~~~

  For this implementation, it is important to highlight that:

  - To add elements to the end of a vector, you can use ```<vector>.push_back(<element>)``` or ```<vector>.emplace_back(<element>)```.
  - To add elements inside elsewhere, you can add ```<vector>.insert(<pos>, <value>)``` or ```<vector>.emplace(<pos>, <value>)```.
  - If you are asking the difference of *insert* and *emplace*. The first one, require a pre-constructed object. The second one, constructs the object directly in the container's memory.

## Useful resources

- [Getting started | ISO CPP](https://isocpp.org/get-started)

- [The Nightmare of Initialization in C++ | CPP Con 2018](https://youtu.be/7DTlWPgX6zs)

- [Almost Always Auto | Sutter's Mill](https://herbsutter.com/2013/08/12/gotw-94-solution-aaa-style-almSutter'sost-always-auto/)

- [Weekly C++ | Jason Turner YT](https://www.youtube.com/@cppweekly/videos)
