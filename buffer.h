#ifndef BUFFER_H
#define BUFFER_H

#include <mutex>
#include <condition_variable>

class Buffer
{
public:
    std::string data;
    std::mutex mtx;
    std::condition_variable cv;

    void putData(const std::string& data);
    std::string getData();
};

#endif