#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <iostream>
#include <string>
#include "socket_server.h"

class DataProcessor {
public:
    void analyzeData(const std::string& data);
    bool isMultipleOf32(int number);

};

#endif