/**
 * @file Constants.h
 * @brief Defines global constants and race stat templates used throughout the game.
 *
 * This header provides:
 *  - The number of commands required to toggle between day and night.
 *  - A RaceStats struct describing the combat and survival attributes for each race.
 *  - Constant RaceStats presets for all player and enemy races, including
 *    day/night variations for Orcs.
 *
 * These values centralize all core balance parameters, ensuring that character
 * construction and race-specific behaviour remain consistent across the program.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @namespace Constants
 * @brief Contains global constant values and race templates used by Characters.
 *
 * All race attributes (attack, defence, health, strength, etc.)
 * are stored as constexpr objects and referenced when initializing Player
 * or Enemy instances. This provides a clean separation between game logic
 * and character configuration.
 */
namespace Constants {

/// Number of player commands required to trigger day/night change.
constexpr int COMMANDS_PER_TIME_SWITCH = 5;

/**
 * @struct RaceStats
 * @brief Container for all base statistics of a game race.
 *
 * Each field corresponds to an attribute used during combat or inventory
 * calculations, and is applied when constructing Characters.
 *
 * Fields:
 *  - attack: Base attack value
 *  - attackChance: Probability [0–1] of successful attack
 *  - defence: Base defence value
 *  - defenceChance: Probability [0–1] of successful defence
 *  - health: Starting health
 *  - strength: Weight capacity used for inventory limits
 */
struct RaceStats {
    int attack;
    double attackChance;
    int defence;
    double defenceChance;
    int health;
    int strength;
};

// ---------------------------------------------------------------------
// Player Race Definitions
// ---------------------------------------------------------------------

/// Human: Balanced stats with moderate attack/defence and high health.
constexpr RaceStats HUMAN  = {30, 2.0/3.0, 20, 1.0/2.0, 60, 100};

/// Elf: High attack and perfect attackChance; low defence.
constexpr RaceStats ELF    = {40, 1.0,     10, 1.0/4.0, 40, 70};

/// Dwarf: Robust defence and strength; strong survivability.
constexpr RaceStats DWARF  = {30, 2.0/3.0, 20, 2.0/3.0, 50, 130};

/// Hobbit: Low attack but high health; very defensive race.
constexpr RaceStats HOBBIT = {25, 1.0/3.0, 20, 2.0/3.0, 70, 85};

// ---------------------------------------------------------------------
// Orc—Day/Night Variants
// ---------------------------------------------------------------------

/**
 * @brief Orc stats during daytime.
 *
 * Orcs are weaker during the day per game rules:
 *  - Lower attack and defence
 *  - Much lower attackChance and defenceChance
 */
constexpr RaceStats ORC_DAY   = {25, 1.0/4.0, 10, 1.0/4.0, 50, 130};

/**
 * @brief Orc stats during nighttime.
 *
 * Orcs become extremely strong during night:
 *  - Very high attack and defence values
 *  - Improved attackChance and defenceChance
 */
constexpr RaceStats ORC_NIGHT = {45, 1.0,    25, 1.0/2.0, 50, 130};

} // namespace Constants

#endif // CONSTANTS_H
