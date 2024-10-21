#include "data_processor.h"

bool DataProcessor::isMultipleOf32(int number) {
    return (number % 32 == 0);
}

void DataProcessor::analyzeData(const std::string& data) {
    if (data.length() > 2) {
        int dataLength = std::stoi(data);
        if (isMultipleOf32(dataLength)) {
            std::cout << "Получены данные: " << data << std::endl;
        } else {
            std::cout << "Ошибка: Длина данных не кратна 32" << std::endl;
        }
    } else {
        std::cout << "Ошибка: Длина данных меньше или равна 2" << std::endl;
    }
}