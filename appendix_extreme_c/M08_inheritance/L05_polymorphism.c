// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * POLYMORPHISM: The idea here is two have the same code for different behaviors, in other words,
 * using the same public interface for  different behaviors.
 * 
 * You can think of it with the movement of a person vs a dog, we can call the function 'walk()' but
 * inside of it is different, as a human has two legs and a dog has four. This is a better approach than
 * using 'dog_walk()' and 'human_walk()'.
 * 
 * The 'why?' polymorphism is that we want to keep the code 'as is' even with different subtypes, so we
 * can keep the same logic and reduce the number of changes, this refers with two key concepts:
 * 
 * - ABSTRACTION:  To have an idea or and unimplemented behavior function that will be defined in the future.
 * - OVVERRIDE: To write (under the same name) the parent's implementation with a different behavior in the
 *   child.
*/