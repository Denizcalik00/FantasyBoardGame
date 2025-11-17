#ifndef WEAPON_H
#define WEAPON_H





#include "Item.h"

// Weapon increase attack for character
class Weapon : public Item
{
private:
    int attackBoost;

public:
    Weapon(std::string n, int w, int boost)
        : Item(n, w, WEAPON)
    {
        attackBoost = boost;
    }

    void applyEffect(Character &c);   // add attack
    void removeEffect(Character &c);  // remove attack
};
#endif // WEAPON_H
