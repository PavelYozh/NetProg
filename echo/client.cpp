#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Не удалось создать сокет" << endl;
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(7);
    inet_pton(AF_INET, "172.16.40.1", &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        cerr << "Не удалось подключиться к серверу" << endl;
        close(sock);
        return 1;
    }

    const char* message = "Hello, echo!\n";
    send(sock, message, strlen(message), 0);
    cout << "Отправлено: " << message;

    char buffer[256] = {0};
    int n = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        cout << "Получено: " << buffer;
    } else {
        cerr << "Сервер не ответил" << endl;
    }

    close(sock);
    return 0;
}
