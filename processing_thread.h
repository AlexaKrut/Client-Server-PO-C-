#ifndef PROCESSING_THREAD_H
#define PROCESSING_THREAD_H

#include "socket_client.h"
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include "buffer.h"

class ProcessingThread
{
public:
    Buffer* buffer;
    SocketClient* socketClient = new SocketClient();

    void run();
    int calculateSum(const std::string& data);
};

#endif