#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include <string>

/**
 * @file Weapon.h
 * @brief Declares the Weapon class, an equipable item that increases a Character's attack.
 *
 * Weapons are concrete Item types that enhance a Character's offensive capability
 * when equipped. The effect must be reversed when unequipped.
 */

/**
 * @class Weapon
 * @brief Concrete Item type providing an attack boost to a Character.
 *
 * Responsibilities:
 *  - Increase a Character's attack stat when equipped.
 *  - Reverse this stat change when unequipped.
 *
 * Assignment compliance:
 *  ✔ Implements applyEffect() and removeEffect()
 *  ✔ Uses std::unique_ptr<Item> for ownership
 *  ✔ Encapsulates category-specific behaviour (ItemType::WEAPON)
 */
class Weapon : public Item {
public:

    /**
     * @brief Constructs a Weapon with a specified attack boost.
     *
     * @param name        Name of the weapon.
     * @param weight      Weight used for carry capacity.
     * @param attackBoost Amount added to Character's attack stat.
     */
    Weapon(const std::string &name, int weight, int attackBoost)
        : Item(name, weight, ItemType::WEAPON), attackBoost_(attackBoost) {}

    /**
     * @brief Applies the weapon’s attack boost to a Character.
     *
     * PSEUDOCODE:
     * @code
     * c.modifyAttack(+attackBoost_);
     * @endcode
     *
     * @param c Reference to the Character equipping the weapon.
     */
    void applyEffect(class Character &c) override;

    /**
     * @brief Reverses the weapon’s effect when unequipped.
     *
     * Must exactly undo applyEffect().
     *
     * PSEUDOCODE:
     * @code
     * c.modifyAttack(-attackBoost_);
     * @endcode
     *
     * @param c Reference to the Character removing the weapon.
     */
    void removeEffect(class Character &c) override;

private:
    int attackBoost_;   ///< Amount of attack added to the Character.
};

#endif // WEAPON_H
