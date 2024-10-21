#ifndef INPUT_THREAD_H
#define INPUT_THREAD_H

#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <cctype>
#include "buffer.h"
#include <mutex>
#include <condition_variable>

class InputThread
{
public:
    std::string inputString;
    Buffer* buffer;

    void run();
    bool validateInput(const std::string& inputString);
    std::string sortInput(const std::string& inputString);
    std::string processInput(const std::string& inputString);
};

#endif