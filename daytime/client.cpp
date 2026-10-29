#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        cerr << "Не удалось создать сокет" << endl;
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(13);
    inet_pton(AF_INET, "172.16.40.1", &server.sin_addr);

    char request[] = "";
    sendto(sock, request, strlen(request), 0,
           (struct sockaddr*)&server, sizeof(server));

    char buffer[256] = {0};
    socklen_t len = sizeof(server);
    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr*)&server, &len);

    if (n > 0) {
        buffer[n] = '\0';
        cout << "Время на сервере: " << buffer;
    } else {
        cerr << "Сервер не ответил" << endl;
    }

    close(sock);
    return 0;
}
