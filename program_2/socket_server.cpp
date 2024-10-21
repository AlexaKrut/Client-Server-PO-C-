#include "socket_server.h"

void SocketServer::startServer() {
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        perror("Ошибка при создании сокета сервера");
        return;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(1111);

    if (bind(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Ошибка при привязке сокета к адресу и порту");
        close(socketFD);
        return;
    } else {
        std::cout << "Сокет успешно привязан к адресу и порту" << std::endl;
    }

    if (listen(socketFD, 5) < 0) {
        perror("Ошибка при ожидании подключения клиента");
        close(socketFD);
        return;
    }
}

void SocketServer::acceptClient() {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    clientSocket = accept(socketFD, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        perror("Ошибка при принятии входящего соединения");
        close(socketFD);
        return;
    }

    std::cout << "Подключение клиента успешно" << std::endl;
}


std::string SocketServer::receiveData() {
    char buffer[1024] = {0};
    int valread = read(clientSocket, buffer, 1024);
    if (valread == 0) { 
        // Клиент отключился
        std::cerr << "Клиент отключился" << std::endl;
        close(clientSocket); // Закрываем сокет клиента
        return ""; 
    } else if (valread < 0) {
        perror("Ошибка при чтении данных от клиента");
        return "";
    } 

    return std::string(buffer);
}