#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    Player(const std::string& name); // Constructor to initialize a Player

    void attack(Character& target) override; // Attack function for Player
    void displayStatus() const override; // Display Player status
    void levelUp(); // Level up Player
};

#endif // PLAYER_H
