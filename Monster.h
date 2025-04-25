#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"

class Monster : public Character {
public:
    Monster(const std::string& name); // Constructor to initialize a Monster

    void attack(Character& target) override; // Attack function for Monster
    void displayStatus() const override; // Display Monster status
};

#endif // MONSTER_H
