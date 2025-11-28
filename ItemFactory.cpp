#include "ItemFactory.h"
#include "Utility.h"
#include "Weapon.h"
#include "Armour.h"
#include "Shield.h"
#include "Ring.h"

/**
 * @file ItemFactory.cpp
 * @brief Implements the ItemFactory class for creating random items.
 *
 * Responsibilities:
 *  - Provide a factory function to generate random items from a predefined list.
 */

/**
 * @brief Creates a random item from a predefined set of items.
 *
 * Randomly selects one of eight items:
 *  - Weapon: Sword, Dagger
 *  - Armour: Plate Armour, Leather Armour
 *  - Shield: Large Shield, Small Shield
 *  - Ring: Ring of Life, Ring of Strength
 *
 * @return Unique pointer to the newly created Item, or nullptr if selection fails.
 */
std::unique_ptr<Item> ItemFactory::createRandomItem() {
    int choice = Utility::randInt(0, 7);
    switch (choice) {
    case 0: return std::make_unique<Weapon>("Sword", 10, 10);
    case 1: return std::make_unique<Weapon>("Dagger", 5, 5);
    case 2: return std::make_unique<Armour>("Plate Armour", 40, 10, 5);
    case 3: return std::make_unique<Armour>("Leather Armour", 20, 5, 0);
    case 4: return std::make_unique<Shield>("Large Shield", 30, 10, 5);
    case 5: return std::make_unique<Shield>("Small Shield", 10, 5, 0);
    case 6: return std::make_unique<Ring>("Ring of Life", 1, 10, 0);
    case 7: return std::make_unique<Ring>("Ring of Strength", 1, -10, 50);
    }
    return nullptr;
}
