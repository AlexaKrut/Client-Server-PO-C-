#include "input_thread.h"

void InputThread::run()
{
    while(true) {
        std::getline(std::cin, inputString);

        try {
            if (!validateInput(inputString)) {
                throw std::invalid_argument("Введена неверная строка!");
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка! " << e.what() << std::endl;
            continue;
        }

        try {
            inputString = sortInput(inputString);
            inputString = processInput(inputString);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при обработке ввода! " << e.what() << std::endl;
            continue;
        }

        try {
            buffer->putData(inputString); 
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: Буфер недоступен, отправка данных невозможна. " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5)); 
        }
    }
}

bool InputThread::validateInput(const std::string& inputString)
{
    if  (inputString.length() > 64) {
        throw std::out_of_range("Длина введенной строки превышает 64 символа");
    }
    for(char c : inputString) {
        if (!std::isdigit(c)) {
            throw std::invalid_argument("Введенная строка содержит недопустимые символы. Допускаются только цифры.");
        }
    }
    return true;
}

std::string InputThread::sortInput(const std::string& inputString)
{
    std::string sortString = inputString;
        int n = sortString.length();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sortString[j] < sortString[j + 1]) {
                char temp = sortString[j];
                sortString[j] = sortString[j + 1];
                sortString[j + 1] = temp;
            }
        }
    }

    return sortString;
}

std::string InputThread::processInput(const std::string& inputString)
{
    std::string processedString = inputString;
    for (int i = 0; i < static_cast<int>(processedString.length()); i++) {
        if ((processedString[i] >= '0') && (processedString[i] <= '9') && ((processedString[i] - '0') % 2 == 0)) {
            processedString[i] = 'K';
            processedString.insert(i + 1, "B");
            i++;
        }
    }
    return processedString;
}