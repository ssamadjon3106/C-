#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include <ctime>

using namespace std;

#define PORT 8080

int main() {
    srand(time(0));
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return 1;
    }

    cout << "Server is waiting for a player to connect...\n";
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept");
        return 1;
    }

    send(new_socket, "Enter your hero's name:\n", strlen("Enter your hero's name:\n"), 0);
    memset(buffer, 0, sizeof(buffer));
    read(new_socket, buffer, 1024);
    string playerName(buffer);
    cout<<playerName<<" joined the game!\n";
    Player player(playerName);
    string monster_names[3] = {"Goblin", "Dragon", "Terror"};

    bool keepPlaying = true;

    while (keepPlaying && player.isAlive()) {

        // Generate random monster
        Monster monster(monster_names[rand() % 3] + to_string(rand() % 100));
        string intro = "A wild " + monster.getName() + " appeared! HP: " + to_string(monster.getHealth()) + "\nType word 'attack' to fight.";
        send(new_socket, intro.c_str(), intro.length(), 0);

        // Battle loop
        while (player.isAlive() && monster.isAlive()) {
            memset(buffer, 0, sizeof(buffer));
            read(new_socket, buffer, 1024);
            
            if (strcmp(buffer, "attack") == 0) {
                player.attack(monster);

                if (!monster.isAlive()) {
                    player.levelUp();
                    string victory = "You defeated " + monster.getName() + "! Level Up! Now Level " + to_string(player.getLevel()) + ".\n";
                    send(new_socket, victory.c_str(), victory.size(), 0);
                    break;
                }

                monster.attack(player);
                if (!player.isAlive()) {
                    send(new_socket, "You have been defeated!\n", strlen("You have been defeated!\n"), 0);
                    break;
                }

                string update = "Monster HP: " + to_string(monster.getHealth()) + ", Your HP: " + to_string(player.getHealth()) + "\n";
                send(new_socket, update.c_str(), update.size(), 0);

            } else {
                send(new_socket, "Unknown command.\n", strlen("Unknown command.\n"), 0);
            }
        }

        if (!player.isAlive()) {
            send(new_socket, "Game Over. Thanks for playing!\n", strlen("Game Over. Thanks for playing!\n"), 0);
            break;
        }

        // Ask if the player wants to continue
        send(new_socket, "Do you want to continue fighting? (yes/no):\n", strlen("Do you want to continue fighting? (yes/no):\n"), 0);
        memset(buffer, 0, sizeof(buffer));
        read(new_socket, buffer, 1024);

        if (strncmp(buffer, "no", 2) == 0) {
            keepPlaying = false;
            send(new_socket, "Adventure ended. Goodbye!\n", strlen("Adventure ended. Goodbye!\n"), 0);
        } else {
            send(new_socket, "A new enemy awaits you!\n", strlen("A new enemy awaits you!\n"), 0);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
