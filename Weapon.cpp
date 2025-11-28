#include "Weapon.h"
#include "Character.h"

/**
 * @file Weapon.cpp
 * @brief Implements the Weapon class, an equippable item that increases a Character's attack.
 *
 * Responsibilities:
 *  - Apply attack boost when equipped.
 *  - Remove attack boost when unequipped.
 */

/**
 * @brief Applies the weapon's attack boost to a Character.
 *
 * @param c Reference to the Character equipping the weapon.
 */
void Weapon::applyEffect(Character &c) {
    // Pseudocode:
    //   c.modifyAttack(+attackBoost_);
    c.modifyAttack(attackBoost_);
}

/**
 * @brief Reverses the weapon's effect from a Character.
 *
 * @param c Reference to the Character removing the weapon.
 */
void Weapon::removeEffect(Character &c) {
    // Pseudocode:
    //   c.modifyAttack(-attackBoost_);
    c.modifyAttack(-attackBoost_);
}
