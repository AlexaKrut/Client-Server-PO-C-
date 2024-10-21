#include "data_processor.h"
#include "socket_server.h"
#include <chrono>
#include <thread>

int main() {
    SocketServer server;
    DataProcessor processor;

    try {
        server.startServer(); 
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при запуске сервера: " << e.what() << std::endl;
        return 1; // Возвращаем код ошибки
    }
    
    while (true) {
        // Принимаем подключение
        try {
            server.acceptClient(); 
        } catch (const std::exception& e) {
            std::cerr << "Попытка подключения через 10 секунд..." << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10)); 
        }

        // Обрабатываем данные от клиента
        while (true) {
            std::string receivedData = server.receiveData();
            if (receivedData.empty()) { // Проверка на отключение клиента
                std::cerr << "Ожидаю новое подключение..." << std::endl;
                break; // Выход из цикла обработки клиента
            }
            processor.analyzeData(receivedData);
        }
    }

    return 0;
}