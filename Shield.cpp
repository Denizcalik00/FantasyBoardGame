#include "Shield.h"
#include "Character.h"

void Shield::applyEffect(Character &c)
{
    c.defence = c.defence + defenceBoost;
    c.attack = c.attack - attackPenalty;
}

void Shield::removeEffect(Character &c)
{
    c.defence = c.defence - defenceBoost;
    c.attack = c.attack + attackPenalty;
}
