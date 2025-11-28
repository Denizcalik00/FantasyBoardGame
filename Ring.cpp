#include "Ring.h"
#include "Character.h"

/**
 * @file Ring.cpp
 * @brief Implements the Ring class, an equippable item that can boost health and/or strength.
 *
 * Responsibilities:
 *  - Apply stat boosts to a Character when equipped.
 *  - Remove those boosts when unequipped.
 */

/**
 * @brief Applies the ring's effects to a Character.
 *
 * @param c Reference to the Character equipping the ring.
 */
void Ring::applyEffect(Character &c) {
    if (healthBoost_ != 0) c.modifyHealth(healthBoost_);
    if (strengthBoost_ != 0) c.modifyStrength(strengthBoost_);
}

/**
 * @brief Reverses the ring's effects from a Character.
 *
 * @param c Reference to the Character removing the ring.
 */
void Ring::removeEffect(Character &c) {
    if (healthBoost_ != 0) c.modifyHealth(-healthBoost_);
    if (strengthBoost_ != 0) c.modifyStrength(-strengthBoost_);
}
