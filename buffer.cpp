#include "buffer.h"
    
void Buffer::putData(const std::string& data) {
    std::unique_lock<std::mutex> lock(mtx);
    this->data = data;
    lock.unlock();
    cv.notify_one();
}
std::string Buffer::getData() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !this->data.empty(); });
    std::string result = this->data;
    this->data.clear();
    return result;
}