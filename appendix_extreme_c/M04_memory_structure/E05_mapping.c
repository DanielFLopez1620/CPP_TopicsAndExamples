// Simple program than takes a delay (sleep)

#include <unistd.h> // Library needed for sleep functions

int main(int argc, char** argv)
{
    while(1)
    {
        sleep(1);  // Wait in seconds
    };
    return 0;
}