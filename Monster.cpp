//
//  Monster.cpp
//  battle
//
//  Created by Yuliya Durova on 22/04/25.
//
#include "Monster.h"
#include <iostream>
using std::cout;
Monster::Monster(const string& type){}

void Monster::attack(Character& target) {
    cout << name << " claws at " << target.getName() << " for " << attackPower << " damage!\n";
    ____;
}

void Monster::displayStatus() const {
    ____;
}

