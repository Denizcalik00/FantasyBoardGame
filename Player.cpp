#include "Player.h"
#include "Utility.h"
#include <iostream>
#include "Constants.h"
#include <limits>

/**
 * @file Player.cpp
 * @brief Implements the Player class, a specialized Character controlled by the user.
 *
 * Responsibilities:
 *  - Track player position, gold, and inventory.
 *  - Handle race-specific defence effects.
 *  - Update Orc stats according to day/night.
 *  - Provide methods for inventory management and user interaction.
 */

/**
 * @brief Constructs a Player at a starting position with race-specific stats.
 *
 * @param raceName Name of the player's race ("Human", "Elf", "Dwarf", "Hobbit", "Orc").
 * @param startX Initial X position on the board.
 * @param startY Initial Y position on the board.
 */
Player::Player(const std::string &raceName, int startX, int startY)
    : Character(raceName,
                (raceName=="Human"?  Constants::HUMAN.attack  :
                     raceName=="Elf"?    Constants::ELF.attack    :
                     raceName=="Dwarf"?  Constants::DWARF.attack  :
                     raceName=="Hobbit"? Constants::HOBBIT.attack :
                     raceName=="Orc"?    Constants::ORC_DAY.attack :
                     Constants::HUMAN.attack),

                (raceName=="Human"?  Constants::HUMAN.attackChance  :
                     raceName=="Elf"?    Constants::ELF.attackChance    :
                     raceName=="Dwarf"?  Constants::DWARF.attackChance  :
                     raceName=="Hobbit"? Constants::HOBBIT.attackChance :
                     raceName=="Orc"?    Constants::ORC_DAY.attackChance :
                     Constants::HUMAN.attackChance),

                (raceName=="Human"?  Constants::HUMAN.defence  :
                     raceName=="Elf"?    Constants::ELF.defence    :
                     raceName=="Dwarf"?  Constants::DWARF.defence  :
                     raceName=="Hobbit"? Constants::HOBBIT.defence :
                     raceName=="Orc"?    Constants::ORC_DAY.defence :
                     Constants::HUMAN.defence),

                (raceName=="Human"?  Constants::HUMAN.defenceChance  :
                     raceName=="Elf"?    Constants::ELF.defenceChance    :
                     raceName=="Dwarf"?  Constants::DWARF.defenceChance  :
                     raceName=="Hobbit"? Constants::HOBBIT.defenceChance :
                     raceName=="Orc"?    Constants::ORC_DAY.defenceChance :
                     Constants::HUMAN.defenceChance),

                (raceName=="Human"?  Constants::HUMAN.health  :
                     raceName=="Elf"?    Constants::ELF.health    :
                     raceName=="Dwarf"?  Constants::DWARF.health  :
                     raceName=="Hobbit"? Constants::HOBBIT.health :
                     raceName=="Orc"?    Constants::ORC_DAY.health :
                     Constants::HUMAN.health),

                (raceName=="Human"?  Constants::HUMAN.strength  :
                     raceName=="Elf"?    Constants::ELF.strength    :
                     raceName=="Dwarf"?  Constants::DWARF.strength  :
                     raceName=="Hobbit"? Constants::HOBBIT.strength :
                     raceName=="Orc"?    Constants::ORC_DAY.strength :
                     Constants::HUMAN.strength)
                ),
    x_(startX), y_(startY), gold_(0)
{
}

/**
 * @brief Returns the display name of the player.
 * @return String containing race and identifier.
 */
std::string Player::getName() const {
    return "Player(" + race_ + ")";
}

/**
 * @brief Handles special effects when the player successfully defends an attack.
 *
 * Behaviour depends on race:
 *  - Human/Dwarf: return 0
 *  - Elf: regain 1 health, return 0
 *  - Hobbit: return random value between 0 and 5
 *  - Orc: if night, regain 1 health; if day, return quarter of adjusted base damage
 *
 * @return Amount of special damage dealt (or 0).
 */
int Player::handleSuccessfulDefence()
{
    if (race_ == "Human" || race_ == "Dwarf") return 0;

    if (race_ == "Elf") {
        modifyHealth(+1);
        return 0;
    }

    if (race_ == "Hobbit") {
        return Utility::randInt(0, 5);
    }

    if (race_ == "Orc") {
        if (Utility::isNight()) {
            modifyHealth(+1);
            return 0;
        } else {
            int adjusted = baseAttack_ - baseDefence_;
            if (adjusted < 0) adjusted = 0;
            return adjusted / 4;
        }
    }

    return 0;
}

/**
 * @brief Displays the player's stats and inventory.
 */
void Player::showInventory() const {
    std::cout << "=== Player Stats ===\n";
    std::cout << "Race: " << race_ << "\n";
    std::cout << "Health (H): " << getHealth() << "\n";
    std::cout << "Attack (A): " << getAttack() << "\n";
    std::cout << "Defence (D): " << getDefence() << "\n";
    std::cout << "Strength (Carry Cap): " << getStrength() << "\n\n";

    std::cout << "Gold: " << gold_ << "\n";
    printInventory();
}

/**
 * @brief Prompts the player to select an item to drop from inventory.
 *
 * @return Unique pointer to the item to drop, or nullptr if selection fails.
 */
std::unique_ptr<Item> Player::selectItemToDrop()
{
    if (inventory_.empty()) {
        std::cout << "No items to drop.\n";
        return nullptr;
    }

    printInventory();
    std::cout << "Enter item index to drop: ";

    int idx;
    if (!(std::cin >> idx)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input.\n";
        return nullptr;
    }

    if (idx < 0 || static_cast<size_t>(idx) >= inventory_.size()) {
        std::cout << "Index out of range.\n";
        return nullptr;
    }

    return removeItem(static_cast<size_t>(idx));
}

/**
 * @brief Returns a dropped item back to the inventory.
 * @param item Unique pointer to the Item to return.
 */
void Player::returnDroppedItem(std::unique_ptr<Item> item)
{
    addItemBack(std::move(item));
}

/**
 * @brief Updates player stats based on time of day (for Orcs only).
 * @param isNight True if it is night, false if day.
 */
void Player::updateForTime(bool isNight)
{
    if (race_ != "Orc") return;

    if (isNight) {
        setAttack(Constants::ORC_NIGHT.attack);
        setAttackChance(Constants::ORC_NIGHT.attackChance);
        setDefence(Constants::ORC_NIGHT.defence);
        setDefenceChance(Constants::ORC_NIGHT.defenceChance);
    } else {
        setAttack(Constants::ORC_DAY.attack);
        setAttackChance(Constants::ORC_DAY.attackChance);
        setDefence(Constants::ORC_DAY.defence);
        setDefenceChance(Constants::ORC_DAY.defenceChance);
    }
}
