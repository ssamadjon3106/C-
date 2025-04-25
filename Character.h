

#ifndef Character_h
#define Character_h

#include <string>
using std::string;
class Character {
_______:
    string name;
    int health;
    int attackPower;
    
public:
    Character(const string& name, int health, int attackPower);
    string getName();
    int getHealth();
    virtual void attack(Character& target) = 0;
    virtual void displayStatus() const = 0;

    bool isAlive() const;
    void takeDamage(int amount);
};
#endif /* Character_h */
