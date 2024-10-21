#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <iostream>
#include <chrono>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class SocketClient {
public:
    int socketFD;
    SocketClient() : socketFD(-1) {}

    bool connectToServer();
    bool isConnected();
    int sendData(const std::string& data);
};

#endif