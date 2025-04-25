
#include "Character.h"
#include <iostream>

Character::Character(const string& name, int health, int attackPower)
     {}

bool Character::isAlive() const {
    return ____;
}
string Character::getName(){
    return ____;
}
int Character::getHealth(){
    return ____;
}
void Character::takeDamage(int amount) {
    _____;
    if (health < 0) health = 0;
}
