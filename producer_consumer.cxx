#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <thread>
#include <BoundedBuffer.h>

void producer()
{
    int maxSize;
    std::cout << "This is the producer \n";
    BoundedBuffer& producerInstance = BoundedBuffer::getInstance();
    maxSize = producerInstance.getMaxQueueSize();

    for (int i = 0; i < 100; i++) {
        std::cout << "producer " << i << std::endl;
        producerInstance.addItem();
        std::chrono::microseconds(100);
    }
}

void consumer()
{
    int maxSize;
    std::cout << "This is the consumer \n";
    BoundedBuffer& consumerInstance = BoundedBuffer::getInstance();
    maxSize = consumerInstance.getMaxQueueSize();

    for (int i = 0; i < 50; i++) {
        std::cout << "consumer " << i << std::endl;
        consumerInstance.delItem();
        std::chrono::microseconds(300);
    }
}

int main(int argc, char *argv[])
{
    std::thread firstThread(producer);
    std::thread secondThread(consumer);

    BoundedBuffer& testInstance = BoundedBuffer::getInstance();

    firstThread.join();
    secondThread.join();

    return 0;
}
