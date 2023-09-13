// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with g++

#include <iostream>
#include <cmath>

/**
 * Custom class for implementing 3D points with identificator.
*/
class MyPoint
{
public:

    /**
     * Calculates the norm of the vector formed with the origin.
     * 
     * @return Norm of the vector (0,0,0) -> (x,y,z)
    */
    float Norm()
    {
        return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    }

    
    float x;
    float y;
    float z;
    float num;
};

int main(int argc, char const *argv[])
{
    MyPoint point;
    point.x = 2.0;
    point.y = 2.5;
    point.z = 0.5;

    float norm = point.Norm();

    std::cout << "Norm of ( " << point.x << " , " << point.y << " , " << point.z <<" = ";
    std::cout << norm << std::endl;
    return 0;
}
