#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int health;
    int attackPower;
    int level;

public:
    Character(const std::string& name, int health, int attackPower);
    std::string getName() const;
    int getHealth() const;
    bool isAlive() const;
    void takeDamage(int amount);
    virtual void attack(Character& target) = 0; // Pure virtual function
    virtual void displayStatus() const = 0; // Pure virtual function
};

#endif // CHARACTER_H

