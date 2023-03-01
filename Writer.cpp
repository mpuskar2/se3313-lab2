#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include <thread>
#include <stack>
#include "Semaphore.h"

struct MyShared{
    int threadNumber;
    int reportID;
    int totalTime;
};

Semaphore writer("writer", 1, true);
Semaphore reader("reader", 1, true);

class WriterThread : public Thread{
public:
    int threadNum;
    int reportID;
    int delay;
    bool flag = false;

    WriterThread(int threadNum, int delayTime):Thread(delayTime * 1000){
        this->threadNum = threadNum;
        this->delay = delayTime;
    }

    virtual long ThreadMain(void) override{
        //declare shared memory var so this thread can access it
        Shared<MyShared> sharedMemory ("sharedMemory");

        while(true)
        {
            //write to shared memory
            this->reportID++;

            time_t startTime = time(nullptr);
            sleep(delay);
            writer.Wait();
            time_t endTime = time(nullptr);

            int totalTime = endTime - startTime;
            sharedMemory-> threadNumber = threadNum;
            sharedMemory-> reportID = reportID;
            sharedMemory-> totalTime = totalTime;

            reader.Signal();

            if(flag){//Exit loop to end the thread
                break;
            }
        }
        return 1;
    }
};

int main(void)
{
    std::string userInput;
    std::string delayTimeStr;
    int threadNumber = 0;
    std::stack<WriterThread*> threadStack;

	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMemory
    WriterThread * thread1;

	while(true){
        std::cout << "Would you like to create a writer thread?\n";
        getline(std::cin, userInput);

        if (userInput == "n") {
            break;
        }
        else {
            std::cout << "What is the delay time for this thread?\n";
            //std::cin >> delayTime;
            getline(std::cin, delayTimeStr);
            int delayTime = stoi(delayTimeStr);
            threadNumber++;
            //create thread using user input
            thread1 = new WriterThread(threadNumber, delayTime);
            threadStack.push(thread1);
        }
	}

    for(int i = 0; i < threadStack.size(); i++){
        thread1 = threadStack.top();
        thread1->flag = true;
        delete thread1;
        threadStack.pop();
    }
}
