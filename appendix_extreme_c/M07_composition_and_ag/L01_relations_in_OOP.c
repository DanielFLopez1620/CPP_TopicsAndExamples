// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * RELATIONS BETWEEN CLASSES:
 * 
 * - OBJECT AND CLASS: There are two approaches prototype-based (from empty object or clone, where instance and object
 *   are the same thing) or class-based (when it is based in somthing, a class, which is the base of an object).
 *   
 *   The point here is that classes are the base (blueprint) that indicates which attributes must be present, so its 
 *   memory is allocated first and then the attributes are initialized (construction). So there must be a 'constructor'
 *   and a destructor (whihc free allocated resources). So we can say that classes are the blueprint for object (which
 *   can be many of them), it does not consume memory (exists at source level) and it should contruct/destruct.
*/

#include <string.h>

typedef struct 
{
    char gamertag[32];
    int age;
    char fav_game[16];
} player_t;

int main(int argc, char const *argv[])
{
    printf("There are relationships in classes, do not forget to read about them\n");
    printf("Meanwhile let's see an example of attribute structure:\n\n");

    player_t example;
    strcpy(example.gamertag, "DanielFLopez1620");
    example.age = 20;
    strcpy(example.fav_game, "Halo");

    printf("Player info:\n");
    printf("Gamertag: %s\n", example.gamertag);
    printf("Age: %d\n", example.age);
    printf("Favorite game: %s\n", example.fav_game);


    return 0;
}
