// BASED ON THE BOOK EXTREM C - 1° Edition
// Code tested with gcc

#include <stdio.h>

/**
 * Testing is always an important part of developing, no matter the programming language and it is 
 * a must for a real project.
 * 
 * The first question to bring to the table is.... What are we testing? What is the test about?
 * So, we can consider a 'functional' (functionality in general, related with requirementes, 
 * modules, componentes, systems that expect a certain output) or 'non-functional'(quality level
 * with memory, complexity, time to completation and security) approaches.
 * 
 * There are some levels for this, which are: Unit testing, integration testing, system testing, 
 * acceptance testing and regression testing, but we will focus on Unit Testing.
 * 
 * UNIT TESTING: Aims to taste units of functionality, or a specific part that performs a certain 
 * job. The parts that have a well-defined set of functionalities can be refered as 'components' 
 * that then together become a whole system. But in tests they are isolated, in case we test the
 * functionality of various of them we call it INTEGRATION TESTING to check if they work well 
 * together. Finally, when we reach the system at test the whole aspect and at this level we test
 * from the perspective of a 'stakeholder' or 'end-user' so the test turn to be ACCEPTANCE TESTING,
 * which isn't usually made by the devs.
 * 
 * The REGRESSION TEST is made when changes are added to the code, and you need to check if 
 * everything is still working as the beginning.
 * 
 * NOTE: You can find more info here: https://www.javatpoint.com/acceptance-testing
 * 
 * Now, we will move on to talk in code about the Unit Tests, in the case of C or C++, you test 
 * functions or a set of functions as components, but the test must be isolated, so if the function
 * call themselves with params of other functions, we need to figure out a way to pass the arguments
 * and make the tests.
 * 
 * With the codes of the next lesson, we will illustrate this.
 * 
*/

int main(int argc, char **argv)
{
    printf("Read the intro, and we will move on to the unit tests!\n");
    return 0;
}
