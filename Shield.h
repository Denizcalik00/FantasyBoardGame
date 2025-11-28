/**
 * @file Shield.h
 * @brief Declares the Shield class, a defensive item that increases defence and may reduce attack.
 *
 * Shields are equipable defensive items. When applied to a Character, they increase
 * the defence stat but may also impose a small attack penalty. These effects must
 * be reversed when removed.
 */

#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"
#include <string>

/**
 * @class Shield
 * @brief Concrete Item type providing defensive enhancement at possible attack cost.
 *
 * Responsibilities:
 *  - Increase a Character's defence when the shield is equipped.
 *  - Optionally reduce the Character's attack (attackPenalty_).
 *  - Reverse these stat changes when removed.
 *
 * Assignment compliance:
 *  ✔ Implements applyEffect() and removeEffect()
 *  ✔ Uses std::unique_ptr<Item> for ownership
 *  ✔ Encapsulates category-specific behaviour (ItemType::SHIELD)
 */
class Shield : public Item {
public:

    /**
     * @brief Constructs a Shield with specified stat modifications.
     *
     * @param name          Name of the shield.
     * @param weight        Weight used for carry capacity.
     * @param defenceBoost  Value added to Character defence.
     * @param attackPenalty Value subtracted from Character attack (default = 0).
     */
    Shield(const std::string &name, int weight, int defenceBoost, int attackPenalty = 0)
        : Item(name, weight, ItemType::SHIELD),
        defenceBoost_(defenceBoost),
        attackPenalty_(attackPenalty) {}

    /**
     * @brief Applies the shield’s stat effects to a Character.
     *
     * PSEUDOCODE:
     *  c.modifyDefence(+defenceBoost_)
     *  c.modifyAttack(-attackPenalty_)
     *
     * @param c Reference to the Character equipping the shield.
     */
    void applyEffect(class Character &c) override;

    /**
     * @brief Reverses the shield’s effects when unequipped.
     *
     * Must exactly undo applyEffect().
     *
     * PSEUDOCODE:
     *  c.modifyDefence(-defenceBoost_)
     *  c.modifyAttack(+attackPenalty_)
     *
     * @param c Reference to the Character removing the shield.
     */
    void removeEffect(class Character &c) override;

private:
    int defenceBoost_;   ///< Amount of defence added to the Character.
    int attackPenalty_;  ///< Penalty applied to the Character's attack stat.
};

#endif // SHIELD_H
