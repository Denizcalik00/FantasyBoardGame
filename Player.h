/**
 * @file Player.h
 * @brief Declares the Player class, representing the user-controlled character.
 *
 * Player extends Character and adds:
 *  - board position (x_, y_)
 *  - gold tracking
 *  - inventory interactions and selection for dropping items
 *  - time-of-day stat updates (Orc behaviour)
 *
 * Player objects are moved around the Board and interact with BoardSquares.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <memory>
#include <string>

/**
 * @class Player
 * @brief Represents the human-controlled player character.
 *
 * Responsibilities:
 *  - Maintain board coordinates for movement.
 *  - Manage inventory (pickup, drop, inspect, choose an item to drop).
 *  - Earn and track gold.
 *  - Adjust race stats dynamically if Orc (day vs night).
 *
 * Player inherits all combat and stat behaviour from Character.
 */
class Player : public Character {
public:

    /**
     * @brief Constructs a Player with a given race and starting board position.
     *
     * The raceName determines which stats from Constants::RaceStats are applied.
     *
     * @param raceName Name of player race ("Human", "Elf", etc.)
     * @param startX Starting X coordinate on the board.
     * @param startY Starting Y coordinate on the board.
     */
    Player(const std::string &raceName, int startX, int startY);

    /**
     * @brief Returns the display name of the player.
     *
     * Override of Character::getName().
     *
     * @return A string containing the player's race.
     */
    std::string getName() const override;

    // ----------------------------------------------------------------------
    // Position accessors
    // ----------------------------------------------------------------------

    /// @return Player’s current X coordinate.
    int getX() const { return x_; }

    /// @return Player’s current Y coordinate.
    int getY() const { return y_; }

    /**
     * @brief Sets player’s board position.
     *
     * @param x New X coordinate.
     * @param y New Y coordinate.
     */
    void setPosition(int x, int y) { x_ = x; y_ = y; }

    // ----------------------------------------------------------------------
    // Gold management
    // ----------------------------------------------------------------------

    /// @return Current gold total.
    int getGold() const { return gold_; }

    /// @brief Adds or subtracts gold.
    void addGold(int v) { gold_ += v; }

    // ----------------------------------------------------------------------
    // Inventory
    // ----------------------------------------------------------------------

    /**
     * @brief Displays the player’s inventory contents.
     *
     * Likely prints name, weight, and index of each carried item.
     */
    void showInventory() const;

    /**
     * @brief Allows user to select an item from inventory to drop.
     *
     * PSEUDOCODE:
     *  1. Print inventory with numbered list.
     *  2. Ask user to pick an index.
     *  3. Validate index.
     *  4. If valid:
     *         remove item from inventory_ → return unique_ptr<Item>
     *     Else:
     *         return nullptr.
     *
     * @return A unique_ptr<Item> if user chose an item, or nullptr.
     */
    std::unique_ptr<Item> selectItemToDrop();

    /**
     * @brief Returns an item to the player's inventory after a failed drop.
     *
     * Used if BoardSquare::dropItem() rejects the item (square occupied).
     *
     * @param item Item to add back to inventory.
     */
    void returnDroppedItem(std::unique_ptr<Item> item);

    // ----------------------------------------------------------------------
    // Time-based stat updates (Orcs only)
    // ----------------------------------------------------------------------

    /**
     * @brief Updates player stats for day/night transitions.
     *
     * Only applies race-specific changes for Orcs.
     * Non-Orc races are unaffected.
     *
     * PSEUDOCODE:
     *  if race_ != "Orc":
     *      return
     *  if isNight:
     *      switch to Constants::ORC_NIGHT stats
     *  else:
     *      switch to Constants::ORC_DAY stats
     *
     * @param isNight True if current time is night.
     */
    void updateForTime(bool isNight);

protected:

    /**
     * @brief Defines race-specific defence behaviour for the player.
     *
     * Called when defenceSuccess() == true in Character::attack().
     *
     * PSEUDOCODE (may match enemy behaviour depending on design):
     *  Human, Dwarf:
     *      return 0  // full block
     *  Elf:
     *      health_ += 1; return 0
     *  Hobbit:
     *      return random small damage
     *  Orc:
     *      if night:
     *          health_ += 1; return 0
     *      else:
     *          return reduced damage
     *
     * @return Amount of damage applied after a successful defence.
     */
    int handleSuccessfulDefence() override;

private:
    int x_;     ///< Player's current X coordinate on the board.
    int y_;     ///< Player's current Y coordinate on the board.
    int gold_;  ///< Amount of gold carried by the player.
};

#endif // PLAYER_H
