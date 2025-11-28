/**
 * @file Enemy.h
 * @brief Declares the Enemy class, representing non-player hostile characters placed on the board.
 *
 * Enemy extends the Character abstract class and provides:
 *  - Factory creation of random enemy races.
 *  - Automatic stat adjustments based on day/night cycle (Orc behaviour).
 *  - Implementation of race-specific defence reactions.
 *
 * Enemies occupy BoardSquare cells and are interacted with through player actions
 * such as attack, look, and movement.
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <memory>

/**
 * @class Enemy
 * @brief Represents an AI-controlled hostile character on the game board.
 *
 * Responsibilities:
 *  - Store race-specific base stats (inherited from Character)
 *  - Provide random enemy generation through createRandomEnemy()
 *  - Adjust stats dynamically based on the time of day (Orc day/night switch)
 *  - Implement race-specific successful defence behaviour
 *
 * Ownership:
 *  Enemies are typically placed inside BoardSquare objects using
 *  std::unique_ptr<Enemy>, allowing exclusive ownership and automatic cleanup.
 */
class Enemy : public Character {
public:

    /**
     * @brief Constructs an enemy of the given race.
     *
     * @param raceName Name of the enemy race, e.g., "Human", "Elf", "Orc", etc.
     *
     * Initialization loads race stats from the Constants table
     * when called inside createRandomEnemy().
     */
    explicit Enemy(const std::string &raceName);

    /**
     * @brief Returns the display name of the enemy.
     *
     * Format: "<race> (Enemy)"
     *
     * Override of Character::getName().
     *
     * @return A string containing race + " (Enemy)".
     */
    std::string getName() const override { return race_ + " (Enemy)"; }

    /**
     * @brief Factory function that creates a randomly selected enemy race.
     *
     * PSEUDOCODE:
     * 1. Generate random integer in range of available races.
     * 2. Match index to raceName (Human, Elf, Dwarf, Hobbit, Orc).
     * 3. Construct Enemy with that raceName.
     * 4. Return unique_ptr<Enemy>.
     *
     * @return A dynamically allocated Enemy wrapped in unique_ptr.
     */
    static std::unique_ptr<Enemy> createRandomEnemy();

    /**
     * @brief Updates the enemy’s effective stats depending on day/night.
     *
     * Used primarily for Orcs, whose stats change dramatically.
     *
     * PSEUDOCODE:
     * 1. If race_ != "Orc":
     *        return (no change).
     * 2. If isNight:
     *        setAttack(Constants::ORC_NIGHT.attack)
     *        setDefence(Constants::ORC_NIGHT.defence)
     *        setAttackChance(Constants::ORC_NIGHT.attackChance)
     *        setDefenceChance(Constants::ORC_NIGHT.defenceChance)
     * 3. Else (day):
     *        setAttack(Constants::ORC_DAY.attack)
     *        setDefence(Constants::ORC_DAY.defence)
     *        setAttackChance(Constants::ORC_DAY.attackChance)
     *        setDefenceChance(Constants::ORC_DAY.defenceChance)
     *
     * @param isNight True if the current time is night, False if day.
     */
    void updateForTime(bool isNight);

protected:

    /**
     * @brief Implements enemy-specific defence reaction.
     *
     * Called automatically when defenceSuccess() == true inside Character::attack.
     *
     * PSEUDOCODE (example behaviour—depends on race):
     *  Human, Dwarf:
     *      return 0 damage (block completely)
     *
     *  Elf:
     *      health_ += 1
     *      return 0
     *
     *  Hobbit:
     *      return random number in [0..5]
     *
     *  Orc:
     *      if day:
     *          return incomingDamage / 4    (reduced damage)
     *      if night:
     *          health_ += 1
     *          return 0
     *
     * @return The amount of damage applied after a successful defence.
     */
    int handleSuccessfulDefence() override;
};

#endif // ENEMY_H
