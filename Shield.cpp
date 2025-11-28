#include "Shield.h"
#include "Character.h"

/**
 * @file Shield.cpp
 * @brief Implements the Shield class, an equippable defensive item.
 *
 * Responsibilities:
 *  - Increase a Character's defence when equipped.
 *  - Optionally reduce the Character's attack.
 *  - Reverse these changes when unequipped.
 */

/**
 * @brief Applies the shield's effects to a Character.
 *
 * @param c Reference to the Character equipping the shield.
 */
void Shield::applyEffect(Character &c) {
    c.modifyDefence(defenceBoost_);
    if (attackPenalty_ != 0) c.modifyAttack(-attackPenalty_);
}

/**
 * @brief Reverses the shield's effects from a Character.
 *
 * @param c Reference to the Character removing the shield.
 */
void Shield::removeEffect(Character &c) {
    c.modifyDefence(-defenceBoost_);
    if (attackPenalty_ != 0) c.modifyAttack(+attackPenalty_);
}
