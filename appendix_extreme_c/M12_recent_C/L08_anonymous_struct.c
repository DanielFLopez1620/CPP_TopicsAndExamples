// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * Anonymus structures and unions corresponds to those type definitions without names. They
 * are linked to two or more implementations that allows different access to them. Check the example here:
*/


typedef struct
{
    union 
    {
        struct 
        {
            char letter_1;
            char letter_2;
        };
        char ID[2];
    };
} person_id_t;

int main(int argc, char **argv)
{
    printf("Testing anonymous structures and uniones here...\n\n");
    person_id_t person;
    person.letter_1 = 'D';
    person.ID[1] = 'n';

    printf("The letters are: %c, %c\n", person.letter_1, person.letter_2);

    printf("Which is equal to: %c, %c\n", person.ID[0], person.ID[1]);

    return 0;
}
