#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "Socket creation error\n";
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cout << "Invalid address / Address not supported\n";
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection Failed\n";
        return 1;
    }

    // Receive initial prompt for player name
    read(sock, buffer, 1024);
    cout << buffer;

    string name;
    getline(cin, name);
    send(sock, name.c_str(), name.size(), 0);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = read(sock, buffer, 1024);
        if (bytesReceived <= 0) break;
        cout << buffer;

        // If server is asking for an action or next move
        if (strstr(buffer, "Your action") || strstr(buffer, "appeared") || strstr(buffer, "Unknown command") ||
            strstr(buffer, "Monster HP") || strstr(buffer, "Do you want to continue fighting?")) {

            string input;
            getline(cin, input);
            send(sock, input.c_str(), input.size(), 0);

            // If user typed "no" for continue prompt, skip and wait for server goodbye
            if (input == "no") {
                memset(buffer, 0, sizeof(buffer));
                read(sock, buffer, 1024);
                cout << buffer;
                break;
            }
        }

        // If game over or quit was announced, exit loop
        if ( strstr(buffer, "Goodbye") || strstr(buffer, "Game Over")) {
            break;
        }
    }

    close(sock);
    return 0;
}
