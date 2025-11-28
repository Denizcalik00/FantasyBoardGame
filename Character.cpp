#include "Character.h"
#include "Utility.h"
#include <iostream>

/**
 * @file Character.cpp
 * @brief Implements the Character class, including attacks, defence, and inventory management.
 *
 * Responsibilities:
 *  - Execute attacks and handle defence success.
 *  - Manage inventory with item effects.
 *  - Track health, attack, defence, and strength stats.
 */

/**
 * @brief Constructs a Character with specified stats.
 *
 * @param raceName Name of the character's race.
 * @param attack Base attack value.
 * @param attackChance Probability of a successful attack.
 * @param defence Base defence value.
 * @param defenceChance Probability of a successful defence.
 * @param health Starting health.
 * @param strength Maximum carry strength.
 */
Character::Character(const std::string &raceName,
                     int attack, double attackChance,
                     int defence, double defenceChance,
                     int health, int strength)
    : race_(raceName),
    baseAttack_(attack), baseDefence_(defence), baseHealth_(health), baseStrength_(strength),
    attack_(attack), defence_(defence), health_(health), strength_(strength),
    attackChance_(attackChance), defenceChance_(defenceChance)
{
}

/**
 * @brief Determines if an attack is successful based on attackChance_.
 * @return True if the attack succeeds, false otherwise.
 */
bool Character::attackSuccess() const {
    return Utility::probability(attackChance_);
}

/**
 * @brief Determines if a defence is successful based on defenceChance_.
 * @return True if the defence succeeds, false otherwise.
 */
bool Character::defenceSuccess() const {
    return Utility::probability(defenceChance_);
}

/**
 * @brief Executes an attack on a target Character.
 *
 * Handles attack success, defence success, normal and special damage,
 * and prints combat messages.
 *
 * @param target Pointer to the target Character. Must be non-null and alive.
 */
void Character::attack(Character *target)
{
    if (!target) {
        std::cout << "No target to attack.\n";
        return;
    }
    if (!target->isAlive()) {
        std::cout << target->getName() << " is already defeated.\n";
        return;
    }
    std::cout << getName() << " attacks " << target->getName() << "!\n";

    if (!attackSuccess()) {
        std::cout << getName() << " missed the attack.\n";
        return;
    }

    if (target->defenceSuccess()) {
        int specialDamage = target->handleSuccessfulDefence();
        if (specialDamage > 0) {
            target->modifyHealth(-specialDamage);
        }
        std::cout << target->getName() << " successfully defended (special). Damage taken: "
                  << specialDamage << "\n";
        return;
    }

    int damage = attack_ - target->defence_;
    if (damage < 0) damage = 0;
    target->modifyHealth(-damage);

    std::cout << getName() << " deals " << damage << " damage to " << target->getName() << ".\n";
}

/**
 * @brief Attempts to pick up an item and add it to inventory.
 *
 * Applies the item's effects if picked up successfully. Respects weight and category constraints.
 *
 * @param item Unique pointer to the Item to pick up.
 * @return True if pickup succeeded, false otherwise.
 */
bool Character::pickUp(std::unique_ptr<Item> item)
{
    if (!item) return false;

    int w = item->getWeight();
    ItemType t = item->getType();
    if (t != ItemType::RING) {
        for (const auto &it : inventory_) {
            if (it->getType() == t) return false;
        }
    }

    if (carriedWeight_ + w > strength_) {
        return false;
    }

    item->applyEffect(*this);
    carriedWeight_ += w;
    inventory_.push_back(std::move(item));
    return true;
}

/**
 * @brief Removes an item from the inventory by index.
 *
 * Reverses the item's effect and updates carried weight.
 *
 * @param index Index of the item to remove.
 * @return Unique pointer to the removed item, or nullptr if index invalid.
 */
std::unique_ptr<Item> Character::removeItem(size_t index)
{
    if (index >= inventory_.size()) return nullptr;
    std::unique_ptr<Item> taken = std::move(inventory_[index]);
    taken->removeEffect(*this);
    carriedWeight_ -= taken->getWeight();
    if (carriedWeight_ < 0) carriedWeight_ = 0;
    inventory_.erase(inventory_.begin() + index);
    return taken;
}

/**
 * @brief Re-adds an item to inventory.
 *
 * Applies the item's effect and updates carried weight. Will not add if capacity exceeded.
 *
 * @param item Unique pointer to the Item to re-add.
 */
void Character::addItemBack(std::unique_ptr<Item> item)
{
    if (!item) return;
    if (carriedWeight_ + item->getWeight() > strength_) return;
    item->applyEffect(*this);
    carriedWeight_ += item->getWeight();
    inventory_.push_back(std::move(item));
}

/**
 * @brief Prints the inventory contents and total weight carried.
 */
void Character::printInventory() const
{
    std::cout << "Inventory (" << inventory_.size() << ") weight " << carriedWeight_ << "/" << strength_ << ":\n";
    for (size_t i = 0; i < inventory_.size(); ++i) {
        std::cout << " [" << i << "] " << inventory_[i]->getName() << " (w=" << inventory_[i]->getWeight() << ")\n";
    }
}
