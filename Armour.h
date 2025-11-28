/**
 * @file Armour.h
 * @brief Declares the Armour class, a defensive item that increases defence and may reduce attack.
 *
 * The Armour class represents wearable defensive equipment. It applies a defence boost
 * to a Character and may impose an attack penalty depending on the armour type.
 * Armour items belong to the ItemType::ARMOUR category and follow the rule that
 * the Player may equip only one armour at a time.
 *
 * This file is part of the Fantasy Board Game project.
 */

#ifndef ARMOUR_H
#define ARMOUR_H

#include "Item.h"
#include <string>

/**
 * @class Armour
 * @brief Represents an armour item that boosts defence and may reduce attack.
 *
 * This class extends Item and provides effects related to defensive equipment.
 * When applied to a character, an Armour object increases their defence stat and
 * optionally reduces their attack stat. When removed, these modifiers are reversed.
 *
 * Typical examples:
 * - Plate Armour: high defence boost, moderate attack penalty
 * - Leather Armour: small defence boost, no attack penalty
 *
 * @note Only one armour item may be worn at a time (enforced externally).
 */
class Armour : public Item {
public:

    /**
     * @brief Constructs an Armour item with specified statistics.
     *
     * @param name Name of the armour (e.g., "Plate Armour").
     * @param weight Weight of the armour in units; contributes to carry capacity.
     * @param defenceBoost Amount added to the Character's defence when equipped.
     * @param attackPenalty Optional penalty subtracted from attack (default = 0).
     */
    Armour(const std::string &name, int weight, int defenceBoost, int attackPenalty = 0)
        : Item(name, weight, ItemType::ARMOUR),
        defenceBoost_(defenceBoost),
        attackPenalty_(attackPenalty) {}

    /**
     * @brief Applies this armour's stat modifications to the given Character.
     *
     * PSEUDOCODE:
     * 1. Increase character.defence by defenceBoost_.
     * 2. Decrease character.attack by attackPenalty_ (if > 0).
     * 3. Ensure no stat goes below zero (if game rules enforce this).
     *
     * @param c Reference to the Character receiving the effect.
     */
    void applyEffect(class Character &c) override;

    /**
     * @brief Removes this armour's stat modifications from the Character.
     *
     * PSEUDOCODE:
     * 1. Decrease character.defence by defenceBoost_.
     * 2. Increase character.attack by attackPenalty_ (undo penalty).
     * 3. Ensure no stat becomes negative after removal.
     *
     * @param c Reference to the Character losing the effect.
     */
    void removeEffect(class Character &c) override;

private:
    int defenceBoost_;   ///< Amount added to defence while worn.
    int attackPenalty_;  ///< Attack penalty applied when armour is equipped.
};

#endif // ARMOUR_H
