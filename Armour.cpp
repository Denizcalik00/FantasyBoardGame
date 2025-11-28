#include "Armour.h"
#include "Character.h"

/**
 * @file Armour.cpp
 * @brief Implements the Armour class methods that modify Character stats.
 *
 * This file contains the definitions for Armour's applyEffect and removeEffect
 * methods, which manage defence boosts and optional attack penalties.
 */

/**
 * @brief Applies the armour's stat effects to a Character.
 *
 * Increases the Character's defence by `defenceBoost_`. If there is an attack
 * penalty, it reduces the Character's attack accordingly.
 *
 * PSEUDOCODE:
 * @code
 * c.modifyDefence(+defenceBoost_);
 * if attackPenalty_ != 0 then c.modifyAttack(-attackPenalty_);
 * @endcode
 *
 * @param c Reference to the Character equipping the armour.
 */
void Armour::applyEffect(Character &c) {
    c.modifyDefence(defenceBoost_);
    if (attackPenalty_ != 0) c.modifyAttack(-attackPenalty_);
}

/**
 * @brief Reverses the armour's effects when unequipped.
 *
 * Decreases the Character's defence by `defenceBoost_`. If there was an attack
 * penalty applied, it restores the Character's attack stat.
 *
 * PSEUDOCODE:
 * @code
 * c.modifyDefence(-defenceBoost_);
 * if attackPenalty_ != 0 then c.modifyAttack(+attackPenalty_);
 * @endcode
 *
 * @param c Reference to the Character removing the armour.
 */
void Armour::removeEffect(Character &c) {
    c.modifyDefence(-defenceBoost_);
    if (attackPenalty_ != 0) c.modifyAttack(+attackPenalty_);
}
