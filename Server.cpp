#include "Player.h"
#include "Monster.h"
#include <iostream>

int main() {
    Player player("Hero");
    Monster monster("Dragon");

    player.displayStatus();
    monster.displayStatus();

    player.attack(monster);
    monster.attack(player);

    player.levelUp();
    player.displayStatus();

    return 0;
}


