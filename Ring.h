#ifndef RING_H
#define RING_H

#endif // RING_H

#include "Item.h"

// Ring can increase health or strength.
// Player can have many rings.
class Ring : public Item
{
private:
    int healthBoost;
    int strengthBoost;

public:
    Ring(std::string n, int w, int hBoost, int sBoost)
        : Item(n, w, RING)
    {
        healthBoost = hBoost;
        strengthBoost = sBoost;
    }

    void applyEffect(Character &c);
    void removeEffect(Character &c);
};
