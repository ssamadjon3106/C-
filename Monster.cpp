#include "Monster.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Monster::Monster(const std::string& name)
    : Character(name, 100, 5) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    attackPower = 5 + std::rand() % 11; // Random attack power between 5 and 15
}

void Monster::attack(Character& target) {
    int damage = attackPower + (level * 2);
    std::cout << "[Monster] " << name << " claws at " << target.getName()
              << " for " << damage << " damage!" << std::endl;
    target.takeDamage(damage);
}

void Monster::displayStatus() const {
    std::cout << "[Monster] " << name << " | HP: " << health << " | Level: " << level << std::endl;
}


