#include "socket_client.h"

bool SocketClient::connectToServer() {
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        perror("Ошибка при создании сокета клиента");
        return false;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1111);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Ошибка при подключении к серверу");
        close(socketFD);
        socketFD = -1;
        return false;
    }

    std::cout << "Подключение к серверу успешно" << std::endl;
    return true;
}

bool SocketClient::isConnected() {
    if (socketFD < 0) return false;

    // Проверяем, не разорвано ли соединение
    char buffer[1];
    int bytesReceived = recv(socketFD, buffer, 1, MSG_PEEK | MSG_DONTWAIT);
    if (bytesReceived == 0 || (bytesReceived < 0 && errno != EAGAIN && errno != EWOULDBLOCK)) {
        // Соединение разорвано
        close(socketFD);
        socketFD = -1;
        return false;
    }

    return true;
}

int SocketClient::sendData(const std::string& data) {
    if (socketFD < 0) {
        std::cerr << "Ошибка: нет подключения к серверу" << std::endl;
        return -1;
    }

    if (send(socketFD, data.c_str(), data.length(), 0) < 0) {
        perror("Ошибка при отправке данных на сервер");
        return -1;
    }

    std::cout << "Данные успешно отправлены на сервер" << std::endl;
    return 0;
}