#include "Board.h"
#include "Utility.h"
#include "Enemy.h"
#include "Item.h"
#include "ItemFactory.h"
#include <iostream>

/**
 * @file Board.cpp
 * @brief Implements the Board class, managing the game grid, player movement, and interactions.
 *
 * Responsibilities:
 *  - Create and initialize a game board of given dimensions.
 *  - Populate squares with random enemies or items.
 *  - Handle player actions: move, pick up, drop, attack.
 *  - Update enemy and player stats based on day/night cycle.
 */

/**
 * @brief Helper function to create a random item.
 * @return std::unique_ptr<Item> pointing to a randomly generated Item.
 *
 * Delegates creation to ItemFactory.
 */
static std::unique_ptr<Item> createRandomItem() {
    return ItemFactory::createRandomItem();
}

/**
 * @brief Constructs a Board with the specified width and height.
 * @param width Width of the board.
 * @param height Height of the board.
 *
 * Initializes all squares as empty BoardSquare objects.
 */
Board::Board(int width, int height)
    : width_(width), height_(height)
{
    grid_.resize(height_);
    for (int y = 0; y < height_; ++y) {
        grid_[y].resize(width_);
        for (int x = 0; x < width_; ++x) {
            grid_[y][x] = std::make_unique<BoardSquare>();
        }
    }
}

/**
 * @brief Initializes the board by populating each square.
 */
void Board::initialize()
{
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            populateSquare(x, y);
        }
    }
}

/**
 * @brief Populates a single square with an enemy, item, or leaves it empty.
 * @param x X-coordinate of the square.
 * @param y Y-coordinate of the square.
 */
void Board::populateSquare(int x, int y)
{
    int c = Utility::randInt(0, 2);
    if (c == 0) {
        auto e = Enemy::createRandomEnemy();
        if (e) {
            e->updateForTime(Utility::isNight());
            grid_[y][x]->placeEnemy(std::move(e));
        }
    } else if (c == 1) {
        auto item = createRandomItem();
        if (item) grid_[y][x]->placeItem(std::move(item));
    }
}

/**
 * @brief Checks whether the given coordinates are inside the board boundaries.
 * @param x X-coordinate.
 * @param y Y-coordinate.
 * @return True if coordinates are valid, false otherwise.
 */
bool Board::inBounds(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

/**
 * @brief Moves the player in the specified direction.
 * @param player Reference to the Player.
 * @param direction Character 'N', 'S', 'E', or 'W' representing direction.
 * @return True if the move succeeded, false otherwise.
 *
 * Updates enemy stats if an enemy is present on the new square, and displays the square content.
 */
bool Board::movePlayer(Player &player, char direction)
{
    int x = player.getX();
    int y = player.getY();
    char d = static_cast<char>(std::toupper(direction));
    int nx = x, ny = y;
    if (d == 'N') ny = y - 1;
    else if (d == 'S') ny = y + 1;
    else if (d == 'E') nx = x + 1;
    else if (d == 'W') nx = x - 1;
    else {
        std::cout << "Unknown direction.\n";
        return false;
    }
    if (!inBounds(nx, ny)) {
        std::cout << "You cannot move that direction (out of bounds).\n";
        return false;
    }
    player.setPosition(nx, ny);
    BoardSquare *sq = grid_[ny][nx].get();
    if (sq && sq->hasEnemy()) {
        Enemy *e = sq->getEnemy();
        if (e) e->updateForTime(Utility::isNight());
    }
    lookAtPlayerSquare(player);
    return true;
}

/**
 * @brief Displays the contents of the square where the player is located.
 * @param player Reference to the Player.
 */
void Board::lookAtPlayerSquare(const Player &player) const
{
    int x = player.getX();
    int y = player.getY();
    std::cout << grid_[y][x]->look() << "\n";
}

/**
 * @brief Handles player picking up an item from the current square.
 * @param player Reference to the Player.
 *
 * Transfers ownership if pickup succeeds; otherwise, the item remains on the square.
 */
void Board::playerPickUp(Player &player)
{
    int x = player.getX();
    int y = player.getY();
    BoardSquare *sq = grid_[y][x].get();
    if (!sq) return;
    if (!sq->hasItem()) {
        std::cout << "There is no item here to pick up.\n";
        return;
    }
    std::unique_ptr<Item> it = sq->takeItem();
    if (!player.pickUp(std::move(it))) {
        sq->placeItem(std::move(it));
        std::cout << "You cannot carry that item (category/weight). It remains here.\n";
    } else {
        std::cout << "Item picked up successfully.\n";
    }
}

/**
 * @brief Handles player dropping an item on the current square.
 * @param player Reference to the Player.
 * @param itemToDrop Unique pointer to the item to drop.
 * @return True if dropped successfully, false otherwise.
 */
bool Board::playerDrop(Player &player, std::unique_ptr<Item> itemToDrop)
{
    int x = player.getX();
    int y = player.getY();
    BoardSquare *sq = grid_[y][x].get();
    if (!sq) return false;
    if (sq->hasItem()) {
        std::cout << "Square already contains an item.\n";
        return false;
    }
    if (sq->dropItem(std::move(itemToDrop))) {
        std::cout << "Dropped item on square.\n";
        return true;
    }
    return false;
}

/**
 * @brief Handles player attacking an enemy on the current square.
 * @param player Reference to the Player.
 *
 * Updates enemy stats, executes attack and counterattack, and handles death and gold rewards.
 */
void Board::playerAttack(Player &player)
{
    int x = player.getX();
    int y = player.getY();
    BoardSquare *sq = grid_[y][x].get();
    if (!sq) return;
    if (!sq->hasEnemy()) {
        std::cout << "There is no enemy here to attack.\n";
        return;
    }
    Enemy *e = sq->getEnemy();
    if (!e) return;
    e->updateForTime(Utility::isNight());
    player.attack(e);
    if (!e->isAlive()) {
        std::unique_ptr<Enemy> dead = sq->takeEnemy();
        int reward = dead->getDefenceValueWithItems();
        player.addGold(reward);
        std::cout << "Enemy defeated! You gained " << reward << " gold.\n";
        return;
    }
    std::cout << e->getName() << " attempts to counterattack!\n";
    e->attack(&player);
    if (!player.isAlive()) {
        std::cout << "You have been defeated! Game over.\n";
    }
}

/**
 * @brief Prints a simple debug view of the board.
 *
 * 'E' represents an enemy, 'I' an item, '.' an empty square.
 */
void Board::printDebug() const
{
    std::cout << "Board debug (" << width_ << "x" << height_ << "):\n";
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (grid_[y][x]->hasEnemy()) std::cout << "E ";
            else if (grid_[y][x]->hasItem()) std::cout << "I ";
            else std::cout << ". ";
        }
        std::cout << "\n";
    }
}
