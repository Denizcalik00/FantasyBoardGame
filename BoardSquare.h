/**
 * @file BoardSquare.h
 * @brief Declares the BoardSquare class, representing a single cell on the game board.
 *
 * A BoardSquare may contain either:
 *  - one Item
 *  - one Enemy
 *  - or nothing
 *
 * The square owns its contents exclusively using std::unique_ptr.
 * This ensures BoardSquare controls the lifetime of objects placed on it.
 */

#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <memory>
#include <string>
#include "Enemy.h"

class Item;
class Enemy;

/**
 * @class BoardSquare
 * @brief Represents one cell on the game board (may hold an Item or an Enemy).
 *
 * Responsibilities:
 *  - Store exactly one occupant: either an Item *or* an Enemy (never both).
 *  - Provide methods to look at, place, or remove contents.
 *  - Return raw pointers for inspection, but maintain ownership internally
 *    via std::unique_ptr.
 *
 * @note Game rules enforce that a BoardSquare cannot contain both an item
 *       and an enemy at the same time.
 */
class BoardSquare {
public:
    /**
     * @brief Constructs an empty BoardSquare.
     *
     * item_  = nullptr
     * enemy_ = nullptr
     */
    BoardSquare();

    ~BoardSquare() = default;

    /**
     * @brief Returns a text description of the square's contents.
     *
     * PSEUDOCODE:
     * 1. If enemy_ != nullptr → return "Enemy: <enemy-name>"
     * 2. Else if item_ != nullptr → return "Item: <item-name>"
     * 3. Else return "Empty"
     *
     * @return std::string describing what the square contains.
     */
    std::string look() const;

    /**
     * @brief Places an Item into the square.
     *
     * PSEUDOCODE:
     * 1. If enemy_ exists → cannot place item (but actual check is enforced externally).
     * 2. item_ = move(item)
     *
     * @param item Unique pointer to an Item (ownership transferred).
     */
    void placeItem(std::unique_ptr<Item> item);

    /**
     * @brief Places an Enemy into the square.
     *
     * PSEUDOCODE:
     * 1. If item_ exists → cannot place enemy (external logic ensures this).
     * 2. enemy_ = move(enemy)
     *
     * @param enemy Unique pointer to an Enemy (ownership transferred).
     */
    void placeEnemy(std::unique_ptr<Enemy> enemy);

    /**
     * @brief Returns a raw pointer to the Item (if any).
     *
     * @return Pointer to Item, or nullptr if no item present.
     *
     * @warning This does *not* transfer ownership. Only for inspection.
     */
    Item* getItem() const;

    /**
     * @brief Returns a raw pointer to the Enemy (if any).
     *
     * @return Pointer to Enemy, or nullptr if no enemy present.
     *
     * @note Ownership is still retained by the BoardSquare.
     */
    Enemy* getEnemy() const;

    /**
     * @brief Removes and returns the Item from the square.
     *
     * PSEUDOCODE:
     * 1. tmp = move(item_)
     * 2. item_ = nullptr
     * 3. return tmp
     *
     * @return unique_ptr<Item> (ownership transferred out).
     */
    std::unique_ptr<Item> takeItem();

    /**
     * @brief Removes and returns the Enemy from the square.
     *
     * PSEUDOCODE:
     * 1. tmp = move(enemy_)
     * 2. enemy_ = nullptr
     * 3. return tmp
     *
     * @return unique_ptr<Enemy> (ownership transferred out).
     */
    std::unique_ptr<Enemy> takeEnemy();

    /**
     * @brief Attempts to drop an Item into the square.
     *
     * @param itemToDrop unique_ptr<Item> representing the item to place.
     * @return true if drop succeeded, false otherwise.
     *
     * PSEUDOCODE:
     * 1. If item_ != nullptr or enemy_ != nullptr → return false.
     * 2. item_ = move(itemToDrop)
     * 3. return true
     *
     * @note Only one occupant allowed at a time.
     */
    bool dropItem(std::unique_ptr<Item> itemToDrop);

    /**
     * @brief Checks whether the square currently holds an enemy.
     *
     * @return true if enemy_ != nullptr.
     */
    bool hasEnemy() const;

    /**
     * @brief Checks whether the square currently holds an item.
     *
     * @return true if item_ != nullptr.
     */
    bool hasItem() const;

private:
    std::unique_ptr<Item> item_;   ///< Item contained in this square (if any).
    std::unique_ptr<Enemy> enemy_; ///< Enemy contained in this square (if any).
};

#endif // BOARDSQUARE_H
