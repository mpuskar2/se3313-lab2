#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

struct MyShared{
    int threadNumber;
    int reportID;
    int totalTime;
};

int main(void)
{
    Semaphore writer("writer", 1, false);
    Semaphore reader("reader", 1, false);

    Shared<MyShared> sharedMemory("sharedMemory");

    int count = 0;
    while (count < 30){
        reader.Wait();
        std::cout<<"Thread Number: " << sharedMemory->threadNumber << ", Report ID: " << sharedMemory->reportID << ", Total Time: " << sharedMemory->totalTime <<"\n";
        count++;
        writer.Signal();
    }
}
