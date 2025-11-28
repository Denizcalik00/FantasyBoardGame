/**
 * @file Ring.h
 * @brief Declares the Ring class, a concrete Item that boosts health and/or strength.
 *
 * Rings are lightweight accessories that the player may carry multiple of.
 * They modify Character health and strength when applied, and reverse their
 * effects when removed.
 */

#ifndef RING_H
#define RING_H

#include "Item.h"
#include <string>

/**
 * @class Ring
 * @brief Concrete Item type that boosts health and strength.
 *
 * Responsibilities:
 *  - Increase a Character's health and strength when picked up.
 *  - Remove those stat changes when dropped.
 *  - Store boost values for modification.
 *
 * Rings satisfy assignment requirements:
 *  ✔ Unlimited carry quantity (subject to weight/strength rules)
 *  ✔ Stat-modifying behaviour via applyEffect/removeEffect
 *  ✔ Owned using std::unique_ptr<Item>
 */
class Ring : public Item {
public:

    /**
     * @brief Constructs a ring with specific stat bonuses.
     *
     * @param name          Name of the ring.
     * @param weight        Weight used in carry-capacity checks.
     * @param healthBoost   Amount to increase Character health.
     * @param strengthBoost Amount to increase Character strength.
     */
    Ring(const std::string &name, int weight, int healthBoost, int strengthBoost)
        : Item(name, weight, ItemType::RING),
        healthBoost_(healthBoost),
        strengthBoost_(strengthBoost) {}

    /**
     * @brief Applies the ring’s bonuses to a Character.
     *
     * PSEUDOCODE:
     *  c.modifyHealth(+healthBoost_)
     *  c.modifyStrength(+strengthBoost_)
     *
     * @param c Reference to the Character receiving the effect.
     */
    void applyEffect(class Character &c) override;

    /**
     * @brief Removes the ring’s bonuses from a Character.
     *
     * Must exactly reverse applyEffect().
     *
     * PSEUDOCODE:
     *  c.modifyHealth(-healthBoost_)
     *  c.modifyStrength(-strengthBoost_)
     *
     * @param c Reference to the Character losing the effect.
     */
    void removeEffect(class Character &c) override;

private:
    int healthBoost_;    ///< Amount of health added to the Character.
    int strengthBoost_;  ///< Amount of strength added to the Character.
};

#endif // RING_H
