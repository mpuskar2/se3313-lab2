#include <iostream>
#include "SharedObject.h"

struct MyShared{
    int threadNumber;
    int reportID;
    int delay;
};

int main(void)
{
    Shared<MyShared> sharedMemory("sharedMemory");

    int count = 0;
    while (count < 30){
        std::cout<<"Thread Number: " << sharedMemory->threadNumber << ", Report ID: " << sharedMemory->reportID << ", Delay: " << sharedMemory->delay <<"\n";
        count++;
        sleep(1);
    }
}
