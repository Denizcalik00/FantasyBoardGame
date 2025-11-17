#include "Weapon.h"
#include "Character.h"

// when player pick up weapon
void Weapon::applyEffect(Character &c)
{
    // teacher said members can be public or use setter/getter.
    // For simplicity I follow assignment style and access directly.
    c.attack = c.attack + attackBoost;
}

// when player drop weapon
void Weapon::removeEffect(Character &c)
{
    c.attack = c.attack - attackBoost;
}
