/**
 * @file Board.h
 * @brief Declares the Board class, which manages the 2D grid and all player–square interactions.
 *
 * The Board class stores a dynamic 2D grid of BoardSquare objects. It provides
 * methods that support player movement, combat interactions, item pickup/drop,
 * and examining the current square. The board is populated randomly at the start
 * of the game with enemies and items according to game rules.
 *
 * The Board uses std::unique_ptr<BoardSquare> to model exclusive ownership of each square.
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "BoardSquare.h"
#include "Player.h"

/**
 * @class Board
 * @brief Represents the dynamic 2D game board on which players move.
 *
 * The Board is responsible for:
 * - Initializing a grid of BoardSquare objects.
 * - Randomly populating squares with items and enemies.
 * - Handling all operations related to a Player's interaction with the board:
 *   movement, pickup, drop, and attack.
 * - Ensuring that movements occur only within bounds and that interactions
 *   correspond to the Player's current position.
 *
 * Internally, the board is implemented as:
 * `std::vector<std::vector<std::unique_ptr<BoardSquare>>>`
 * which gives each square unique ownership and prevents accidental sharing.
 */
class Board {
public:

    /**
     * @brief Constructs a board with a given width and height.
     *
     * @param width Width of the board (columns).
     * @param height Height of the board (rows).
     *
     * The constructor allocates the underlying 2D grid but does not populate
     * items/enemies. Call initialize() after construction.
     */
    Board(int width, int height);

    ~Board() = default;

    /**
     * @brief Randomly populates the entire board with items and enemies.
     *
     * PSEUDOCODE:
     * 1. Loop over all x from 0..width-1:
     * 2.   Loop over all y from 0..height-1:
     * 3.       Call populateSquare(x, y)
     *
     * populateSquare():
     * - Random chance to place an item OR an enemy OR leave empty.
     * - Ensures only one occupant per square.
     *
     * @note This should be called once after constructing the board.
     */
    void initialize();

    /**
     * @brief Moves the player one step in the given direction.
     *
     * @param player Reference to the player.
     * @param direction One of {'N','S','E','W'} or lowercase variants.
     * @return true if movement succeeded, false if out of bounds.
     *
     * PSEUDOCODE:
     * 1. Convert direction into (dx, dy).
     * 2. newX = player.x + dx
     *    newY = player.y + dy
     * 3. If NOT inBounds(newX, newY): return false.
     * 4. Update player's internal position.
     * 5. Return true.
     *
     * @note Combat or square interaction is NOT triggered here; those are
     *       handled in other functions based on player's location.
     */
    bool movePlayer(Player &player, char direction);

    /**
     * @brief Prints information about the BoardSquare where the player stands.
     *
     * @param player Const reference to the Player.
     *
     * PSEUDOCODE:
     * 1. Locate the player's current (x, y).
     * 2. Access grid_[y][x].
     * 3. Print:
     *      - Whether it contains an item (and its name)
     *      - Whether it contains an enemy (and its stats)
     *      - Whether the square is empty
     */
    void lookAtPlayerSquare(const Player &player) const;

    /**
     * @brief Allows the player to pick up an item from the current square.
     *
     * @param player Reference to Player.
     *
     * PSEUDOCODE:
     * 1. Locate player's square.
     * 2. If square has no item → print "Nothing to pick up".
     * 3. Otherwise:
     *       - Check player's carry capacity (weight vs strength).
     *       - Check if item type already equipped (for armour/weapon/shield).
     *       - If valid: transfer unique_ptr<Item> from the square to player's inventory.
     * 4. Remove the item from the square.
     */
    void playerPickUp(Player &player);

    /**
     * @brief Drops an item from the player's inventory into the current square.
     *
     * @param player Reference to Player.
     * @param itemToDrop Unique pointer to the Item being dropped.
     * @return true if drop succeeded, false otherwise.
     *
     * PSEUDOCODE:
     * 1. Locate player's square.
     * 2. If square already contains an item or enemy → return false.
     * 3. Place `itemToDrop` into the square.
     * 4. Remove it from player inventory.
     * 5. Return true.
     *
     * @note BoardSquare can only hold ONE occupant (enemy OR item).
     */
    bool playerDrop(Player &player, std::unique_ptr<Item> itemToDrop);

    /**
     * @brief Executes an attack action from the player to the enemy in the same square.
     *
     * @param player Reference to Player initiating the attack.
     *
     * PSEUDOCODE:
     * 1. Locate player's square.
     * 2. If no enemy present → print "No enemy here".
     * 3. Call player.attack(enemy).
     * 4. If enemy's health <= 0:
     *        - Award gold to player.
     *        - Remove enemy from square.
     * 5. If enemy survives and is allowed to counterattack:
     *        - Call enemy.attack(player)
     */
    void playerAttack(Player &player);

    /**
     * @brief Prints the entire board state for debugging.
     *
     * Each square may show:
     * - 'P' for player
     * - 'E' for enemy
     * - 'I' for item
     * - '.' for empty
     *
     * This function is used during development only.
     */
    void printDebug() const;

private:
    int width_;   ///< Number of columns in the board.
    int height_;  ///< Number of rows in the board.

    /**
     * @brief The grid storing all board squares.
     *
     * grid_[y][x] → unique_ptr<BoardSquare>
     */
    std::vector<std::vector<std::unique_ptr<BoardSquare>>> grid_;

    /**
     * @brief Checks whether the coordinate (x, y) lies inside the board.
     *
     * @return true if valid, false if out of bounds.
     *
     * PSEUDOCODE:
     * return (0 <= x < width_) AND (0 <= y < height_)
     */
    bool inBounds(int x, int y) const;

    /**
     * @brief Randomly assigns content to a square (enemy, item, or empty).
     *
     * PSEUDOCODE:
     * 1. Generate random number in range [0, 99].
     * 2. If < threshold → place enemy.
     * 3. Else if < another threshold → place item.
     * 4. Else → leave empty.
     *
     * @param x X coordinate of the square.
     * @param y Y coordinate of the square.
     */
    void populateSquare(int x, int y);
};

#endif // BOARD_H
