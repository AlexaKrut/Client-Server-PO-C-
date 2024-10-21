#include "processing_thread.h"

void ProcessingThread::run() {
    while (true) {
        try {
            bool connected = false;
            while (!connected) {
                if (socketClient) {
                    try {
                        connected = socketClient->connectToServer();
                        if (!connected) {
                            std::cout << "Повторная попытка через 5 секунд." << std::endl;
                            std::this_thread::sleep_for(std::chrono::seconds(5));
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Ошибка при подключении к серверу: " << e.what() << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                    }
                } else {
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                }
            }

            while (true) {
                try {
                    std::string data = buffer->getData();
                    if (!data.empty()) {
                        std::cout << "Данные из буфера: " << data << std::endl;
                        int sum = calculateSum(data);
                        std::string sumAsString = std::to_string(sum);
                        socketClient->sendData(sumAsString);
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка при получении данных из буфера или отправке на сервер: " << e.what() << std::endl;
                    // Обработка ошибки, например, повторная попытка получения данных
                }

                // Проверяем, не разорвано ли соединение
                try {
                    if (!socketClient->isConnected()) {
                        std::cout << "Повторная попытка подключения." << std::endl;
                        break;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка при проверке соединения: " << e.what() << std::endl;
                    // Обработка ошибки, например, повторная попытка подключения
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при работе с сервером: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Ждем 5 секунд перед новой попыткой
        }
    }
}
int ProcessingThread::calculateSum(const std::string& data)
{
    int sum = 0;
    for(char c : data) {
        if (std::isdigit(c)) {
            sum = sum + (c - '0');
        }
    }
    return sum;    
}