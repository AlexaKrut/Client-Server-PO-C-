#include <functional>
#include "buffer.h"
#include "input_thread.h"
#include "processing_thread.h"
#include <thread>
#include <iostream>


Buffer buffer;

int main() {
    InputThread inputThread;
    inputThread.buffer = &buffer;
    
    ProcessingThread processingThread;
    processingThread.buffer = &buffer;
    
    std::thread inputThreadHandle(std::bind(&InputThread::run, &inputThread));
    std::thread processingThreadHandle(std::bind(&ProcessingThread::run, &processingThread));

    inputThreadHandle.join();
    processingThreadHandle.join();

    return 0;
}