#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include <iostream>
#include <string>
#include "socket_server.h"
#include "data_processor.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class SocketServer {
public:
    int socketFD;
    int clientSocket;

    void startServer();
    void acceptClient();
    std::string receiveData();
};

#endif