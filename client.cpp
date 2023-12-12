#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // Создание сокета
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return -1;
    }

    // Установка адреса сервера
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(11000);
    if (inet_pton(AF_INET, "10.102.109.135", &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Ошибка при установке адреса сервера" << std::endl;
        return -1;
    }
    // Установка соединения с сервером
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Ошибка при установке соединения с сервером" << std::endl;
        return -1;
    }
    // как передаем логин и пароль?
    int score = 8;
    char message[80] = "";
    // Отправка скора на сервер
    
    sprintf(message,"%d",score);
        if (send(clientSocket, message, strlen(message), 0) < 0) {
            std::cerr << "Ошибка при отправке сообщения на сервер" << std::endl;
            return -1;
        }


    // Получение ответа от сервера
    char buffer[1024] = {0};
    if (read(clientSocket, buffer, 1024) < 0) {
        std::cerr << "Ошибка при чтении ответа от сервера" << std::endl;
        return -1;
    }
    // Вывод ответа сервера
    std::cout << "Ответ от сервера: " << buffer << std::endl;
    // Закрытие клиентского сокета

    close(clientSocket);
    return 0;
}