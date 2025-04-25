#include "Player.h"
#include <iostream>

Player::Player(const std::string& name)
    : Character(name, 100, 5) {}

void Player::attack(Character& target) {
    int damage = attackPower + (level * 2);
    std::cout << "[Player] " << name << " attacks " << target.getName()
              << " for " << damage << " damage!" << std::endl;
    target.takeDamage(damage);
}

void Player::displayStatus() const {
    std::cout << "[Player] " << name << " | HP: " << health << " | Level: " << level << std::endl;
}

void Player::levelUp() {
    level++;
    attackPower += 5;
    health = 100;
    std::cout << name << " leveled up! Attack Power is now " << attackPower
              << " and health is fully restored!" << std::endl;
}
