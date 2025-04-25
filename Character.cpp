#include "Character.h"
#include <iostream>

Character::Character(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower), level(1) {}

std::string Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

bool Character::isAlive() const {
    return health > 0;
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}


