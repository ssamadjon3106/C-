//
//  Monster.h
//  battle
//
//  Created by Yuliya Durova on 22/04/25.
//

#ifndef Monster_h
#define Monster_h

#include "Character.h"

class Monster : public Character {
public:
    Monster(const std::string& type);

    void attack(Character& target) override;
    void displayStatus() const override;
};


#endif /* Monster_h */
