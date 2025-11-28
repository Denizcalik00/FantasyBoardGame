/**
 * @file Character.h
 * @brief Declares the Character abstract base class for all playable and non-playable races.
 *
 * The Character class encapsulates all shared functionality between Player and Enemy,
 * including:
 *   - Base and effective combat statistics (attack, defence, health, strength)
 *   - Probabilistic attack and defence resolution
 *   - Inventory management (unique_ptr<Item>)
 *   - Stat modification used by item effects
 *
 * Subclasses (Player, Enemy) must implement:
 *   - getName()                  — race-specific display name
 *   - handleSuccessfulDefence()  — race-specific reaction logic when defence succeeds
 *
 * Ownership Model:
 *   - Inventory is stored as std::vector<std::unique_ptr<Item>>
 *     ensuring exclusive ownership and safe transfer on pickup/drop.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <memory>
#include "Item.h"

/**
 * @class Character
 * @brief Abstract base class for all races and characters in the game.
 *
 * Provides:
 *  - Combat logic (attack/defence probabilities)
 *  - Effective stats dynamically modified by items
 *  - Inventory management using unique_ptr<Item>
 *  - Weight management based on Strength
 *  - Hooks for race-specific defence behaviour
 *
 * This class is designed to support:
 *  - Player races (Human, Elf, Dwarf, Hobbit, Orc)
 *  - Enemy entities (with simplified rules)
 */
class Character {
public:

    /**
     * @brief Constructs a Character with base statistics.
     *
     * @param raceName      Name of the race ("Human", "Elf", etc.)
     * @param attack        Base attack value
     * @param attackChance  Probability of successful attack [0,1]
     * @param defence       Base defence value
     * @param defenceChance Probability of successful defence [0,1]
     * @param health        Starting health
     * @param strength      Weight capacity (limits inventory)
     */
    Character(const std::string &raceName,
              int attack, double attackChance,
              int defence, double defenceChance,
              int health, int strength);

    virtual ~Character() = default;

    /**
     * @brief Returns the race/name of the character.
     *
     * Implemented by subclasses (Player, Enemy).
     *
     * @return Race-specific string name.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Performs a generic attack: this (attacker) → target.
     *
     * PSEUDOCODE:
     * 1. If target == nullptr → return immediately.
     * 2. Roll attackSuccess():
     *       - If false → print "attack missed", return.
     * 3. Roll target->defenceSuccess():
     *       - If true → apply target->handleSuccessfulDefence() and return.
     * 4. Compute rawDamage = this->attack_ - target->defence_
     * 5. If rawDamage < 0 → rawDamage = 0
     * 6. target->health_ -= rawDamage
     * 7. If target->health_ <= 0:
     *       - target dies (Enemy awards gold externally)
     *
     * @param target Pointer to the character being attacked.
     */
    void attack(Character *target);

    // ---------------------------------------------------------------------
    // Inventory Management
    // ---------------------------------------------------------------------

    /**
     * @brief Attempts to pick up an item and add it to inventory.
     *
     * PSEUDOCODE:
     * 1. If item == nullptr → return false.
     * 2. If carriedWeight_ + item->weight > strength_ → return false.
     * 3. If item category already equipped (weapon/armour/shield):
     *        - unless item is a ring → return false.
     * 4. Transfer ownership: inventory_.push_back(move(item))
     * 5. Apply item's effect to this character.
     * 6. Update carriedWeight_.
     * 7. return true.
     *
     * @param item unique_ptr<Item> to take ownership of.
     * @return true if successfully picked up.
     */
    bool pickUp(std::unique_ptr<Item> item);

    /**
     * @brief Removes an item from inventory at the given index.
     *
     * PSEUDOCODE:
     * 1. If index >= inventory_.size() → return nullptr
     * 2. itemPtr = move(inventory_[index])
     * 3. Apply reverse effect via itemPtr->removeEffect()
     * 4. carriedWeight_ -= itemPtr->weight
     * 5. return itemPtr
     *
     * Ownership transfers OUT of the inventory.
     *
     * @param index Index within inventory_.
     * @return unique_ptr<Item> removed from inventory.
     */
    std::unique_ptr<Item> removeItem(size_t index);

    /**
     * @brief Adds an item back to the inventory (used after failed drops).
     *
     * @param item unique_ptr<Item> that regains ownership.
     */
    void addItemBack(std::unique_ptr<Item> item);

    /**
     * @brief Prints all items currently in inventory.
     *
     * Format:
     *   [index]  <ItemName>  (weight W)
     *   ...
     */
    void printInventory() const;

    /**
     * @brief Returns true if health_ > 0.
     */
    bool isAlive() const { return health_ > 0; }

    // ---------------------------------------------------------------------
    // Getters
    // ---------------------------------------------------------------------

    /// @return Effective attack value (after item modifiers).
    int getAttack() const { return attack_; }

    /// @return Effective defence value.
    int getDefence() const { return defence_; }

    /// @return Current health.
    int getHealth() const { return health_; }

    /// @return Current strength (weight capacity).
    int getStrength() const { return strength_; }

    /**
     * @brief Returns the effective defence value for reward calculation.
     *
     * Some games use: enemy reward = enemy.defence.
     * Subclasses may override.
     *
     * @return Defence value including item effects.
     */
    virtual int getDefenceValueWithItems() const { return defence_; }

    // ---------------------------------------------------------------------
    // Public Modifiers (used by Item subclasses)
    // ---------------------------------------------------------------------

    void modifyAttack(int delta)   { attack_ += delta; if (attack_ < 0) attack_ = 0; }
    void modifyDefence(int delta)  { defence_ += delta; if (defence_ < 0) defence_ = 0; }
    void modifyHealth(int delta)   { health_ += delta; if (health_ < 0) health_ = 0; }
    void modifyStrength(int delta) { strength_ += delta; if (strength_ < 0) strength_ = 0; }

    // Setters for day/night modifications (e.g., Orc behaviour)
    void setAttack(int v)          { attack_ = v; }
    void setAttackChance(double v) { attackChance_ = v; }
    void setDefence(int v)         { defence_ = v; }
    void setDefenceChance(double v){ defenceChance_ = v; }

protected:
    // ---------------------------------------------------------------------
    // Race + Base Stats
    // ---------------------------------------------------------------------

    std::string race_;        ///< Race tag for display and behaviour.

    int baseAttack_;          ///< Base attack (before item effects).
    int baseDefence_;         ///< Base defence.
    int baseHealth_;          ///< Base health.
    int baseStrength_;        ///< Base strength (max carry weight).

    // ---------------------------------------------------------------------
    // Effective Stats (modifiable)
    // ---------------------------------------------------------------------

    int attack_;              ///< Current attack value.
    int defence_;             ///< Current defence value.
    int health_;              ///< Current health.
    int strength_;            ///< Current strength capacity.
    int carriedWeight_ = 0;   ///< Total carried weight.

    double attackChance_;     ///< Probability [0,1] of successful attack.
    double defenceChance_;    ///< Probability [0,1] of successful defence.

    std::vector<std::unique_ptr<Item>> inventory_; ///< Character inventory.

    // ---------------------------------------------------------------------
    // Internal helpers
    // ---------------------------------------------------------------------

    /**
     * @brief Rolls for attack success.
     * @return true if random() < attackChance
     */
    bool attackSuccess() const;

    /**
     * @brief Rolls for defence success.
     * @return true if random() < defenceChance
     */
    bool defenceSuccess() const;

    /**
     * @brief Race-specific defence behaviour hook.
     *
     * Implemented by Player subclasses or Enemy.
     *
     * PSEUDOCODE (example for races):
     *  Human/Dwarf:
     *      return 0 damage (block completely)
     *  Elf:
     *      health_ += 1; return 0
     *  Hobbit:
     *      return random damage 0–5
     *  Orc:
     *      if day: return (incomingDamage / 4)
     *      if night: health_ += 1; return 0
     *
     * @return Amount of damage applied after successful defence.
     */
    virtual int handleSuccessfulDefence() = 0;
};

#endif // CHARACTER_H
