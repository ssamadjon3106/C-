//
//  player.h
//  battle
//
//  Created by Yuliya Durova on 22/04/25.
//

#ifndef player_h
#define player_h

#include "Character.h"

class Player : public Character {
private:
    int level;

public:
    Player(const std::string& name);

    void attack(Character& target) override;
    void displayStatus() const override;

    void levelUp();
    int getLevel();
};


#endif /* player_h */
