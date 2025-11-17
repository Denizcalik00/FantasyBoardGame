#ifndef SHIELD_H
#define SHIELD_H




#include "Item.h"

// Shield increase defence, big shield decrease attack
class Shield : public Item
{
private:
    int defenceBoost;
    int attackPenalty;

public:
    Shield(std::string n, int w, int defBoost, int atkPenalty)
        : Item(n, w, SHIELD)
    {
        defenceBoost = defBoost;
        attackPenalty = atkPenalty;
    }

    void applyEffect(Character &c);
    void removeEffect(Character &c);
};

#endif // SHIELD_H
