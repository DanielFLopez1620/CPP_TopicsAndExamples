// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * You should remember that we can generate an encapsulation in C by using structures and
 * pointers, to refresh you mind, check the code here:
*/

#include <math.h>

typedef struct 
{
    float x;
    float y;
    float z;
    int num;
} my_point_t;

float point_norm(my_point_t* point);

int main(int argc, char const *argv[])
{
    my_point_t point;
    point.num = 0;
    point.x = 1.0;
    point.y = 2.5;
    point.z = -1.0;

    printf("Norm of vector (%f, %f, %f) ", point.x, point.y, point.z);
    printf("is: %f\n", point_norm(&point));
    return 0;
}

/**
 * Get the norm of a vector respect the origin
 * 
 * @return Norm (float) of the vector formed with origin.
*/
float point_norm(my_point_t* point)
{
    return sqrt(pow(point->x,2) + pow(point->y,2) + pow(point->x,2));
}
