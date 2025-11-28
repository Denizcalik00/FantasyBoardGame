#include "BoardSquare.h"
#include "Item.h"
#include "Enemy.h"
#include <sstream>

/**
 * @file BoardSquare.cpp
 * @brief Implements BoardSquare class, representing a single square on the board.
 *
 * Each square may contain an Item or an Enemy. Provides functions to inspect,
 * place, take, or drop contents.
 */

/**
 * @brief Constructs an empty BoardSquare with no item or enemy.
 */
BoardSquare::BoardSquare()
    : item_(nullptr), enemy_(nullptr)
{}

/**
 * @brief Returns a textual description of the square's contents.
 * @return A string describing an enemy, an item, or that the square is empty.
 */
std::string BoardSquare::look() const
{
    std::ostringstream ss;
    if (enemy_) {
        ss << "An enemy is here: " << enemy_->getName()
        << " (H:" << enemy_->getHealth() << " A:" << enemy_->getAttack()
        << " D:" << enemy_->getDefence() << ")";
    } else if (item_) {
        ss << "You see an item: " << item_->getName()
        << " (weight " << item_->getWeight() << ")";
    } else {
        ss << "The square is empty.";
    }
    return ss.str();
}

/**
 * @brief Places an item on the square.
 * @param item Unique pointer to the Item to place.
 */
void BoardSquare::placeItem(std::unique_ptr<Item> item) {
    item_ = std::move(item);
}

/**
 * @brief Places an enemy on the square.
 * @param enemy Unique pointer to the Enemy to place.
 */
void BoardSquare::placeEnemy(std::unique_ptr<Enemy> enemy) {
    enemy_ = std::move(enemy);
}

/**
 * @brief Returns a raw pointer to the item on the square.
 * @return Pointer to Item, or nullptr if none.
 */
Item* BoardSquare::getItem() const { return item_.get(); }

/**
 * @brief Returns a raw pointer to the enemy on the square.
 * @return Pointer to Enemy, or nullptr if none.
 */
Enemy* BoardSquare::getEnemy() const { return enemy_.get(); }

/**
 * @brief Removes and returns the item from the square.
 * @return Unique pointer to the removed Item.
 */
std::unique_ptr<Item> BoardSquare::takeItem() {
    return std::move(item_);
}

/**
 * @brief Removes and returns the enemy from the square.
 * @return Unique pointer to the removed Enemy.
 */
std::unique_ptr<Enemy> BoardSquare::takeEnemy() {
    return std::move(enemy_);
}

/**
 * @brief Attempts to drop an item onto the square.
 * @param itemToDrop Unique pointer to the Item to drop.
 * @return True if the item was placed successfully, false if the square already contains an item or the pointer is null.
 */
bool BoardSquare::dropItem(std::unique_ptr<Item> itemToDrop)
{
    if (!itemToDrop) return false;
    if (item_) return false;
    item_ = std::move(itemToDrop);
    return true;
}

/**
 * @brief Checks if an enemy is present on the square.
 * @return True if an enemy exists, false otherwise.
 */
bool BoardSquare::hasEnemy() const { return enemy_ != nullptr; }

/**
 * @brief Checks if an item is present on the square.
 * @return True if an item exists, false otherwise.
 */
bool BoardSquare::hasItem() const { return item_ != nullptr; }
