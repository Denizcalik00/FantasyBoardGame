/**
 * @file Item.h
 * @brief Declares the Item abstract base class and ItemType enumeration for all in-game items.
 *
 * Items represent all equippable or carriable objects in the game. They modify Character
 * statistics through applyEffect() and removeEffect(). All concrete items (Weapon, Armour,
 * Shield, Ring) derive from this class.
 *
 * Items are ALWAYS passed, stored, and transferred via std::unique_ptr<Item>, ensuring
 * exclusive ownership and preventing accidental sharing between characters or board squares.
 *
 * The Item class also provides the static factory createRandomItem(), used when the board
 * is populated randomly during initialization.
 */

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

// Forward declaration prevents circular include with Character.h
class Character;

/**
 * @enum ItemType
 * @brief Enumerates the four required categories of equippable items.
 *
 * WEAPON  – Increases attack
 * ARMOUR  – Increases defence, may reduce attack
 * SHIELD  – Increases defence, may reduce attack
 * RING    – Special small items; player may carry multiple rings
 */
enum class ItemType { WEAPON, ARMOUR, SHIELD, RING };

/**
 * @class Item
 * @brief Abstract base class for all item types (Weapon, Armour, Shield, Ring).
 *
 * Responsibilities:
 *  - Store basic metadata (name, weight, type).
 *  - Apply and remove stat effects on a Character.
 *  - Allow Player inventory to store items via std::unique_ptr<Item>.
 *  - Provide Item::createRandomItem() factory for Board population.
 *
 * Assignment requirements satisfied:
 *  ✔ Abstract base class with virtual methods
 *  ✔ Dynamic and unbounded inventory via std::vector<std::unique_ptr<Item>>
 *  ✔ Items adjust stats through modifiers (apply/remove)
 *  ✔ Smart pointers used for memory safety
 */
class Item {
public:

    /**
     * @brief Constructs an Item with a given name, weight, and type.
     *
     * @param name   Human-readable name of the item.
     * @param weight Weight added to player's carried load; compared to strength.
     * @param type   Category of the item (weapon/armour/shield/ring).
     */
    Item(const std::string &name, int weight, ItemType type)
        : name_(name), weight_(weight), type_(type) {}

    virtual ~Item() = default;

    // ---------------------------------------------------------------------
    // Getters
    // ---------------------------------------------------------------------

    /// @return The display name of the item.
    std::string getName() const { return name_; }

    /// @return The weight of the item (used for carry capacity).
    int getWeight() const { return weight_; }

    /// @return The ItemType (used for pickup category restrictions).
    ItemType getType() const { return type_; }

    // ---------------------------------------------------------------------
    // Core Abstract Behaviour
    // ---------------------------------------------------------------------

    /**
     * @brief Applies this item's stat effects to a Character.
     *
     * Called when the Character successfully picks up the item.
     *
     * Examples:
     *  - Weapon: increase attack
     *  - Armour: increase defence, maybe decrease attack
     *  - Shield: increase defence
     *  - Ring: modify health or strength
     *
     * @param c Reference to Character receiving the effect.
     */
    virtual void applyEffect(Character &c) = 0;

    /**
     * @brief Removes this item's stat effects from a Character.
     *
     * Must reverse whatever applyEffect() did.
     *
     * @param c Reference to Character losing the effect.
     */
    virtual void removeEffect(Character &c) = 0;

    // ---------------------------------------------------------------------
    // Factory
    // ---------------------------------------------------------------------

    /**
     * @brief Creates a random item instance using assignment rules.
     *
     * Used by Board::populateSquare() to randomly place items.
     *
     * PSEUDOCODE:
     * 1. Generate random integer in range [0..3].
     * 2. If 0 → return unique_ptr<Weapon>(Sword or Dagger).
     * 3. If 1 → return unique_ptr<Armour>(Plate or Leather).
     * 4. If 2 → return unique_ptr<Shield>(Large or Small).
     * 5. If 3 → return unique_ptr<Ring>(RingOfLife or RingOfStrength).
     *
     * @return std::unique_ptr<Item> of a concrete item.
     */
    static std::unique_ptr<Item> createRandomItem();

private:
    std::string name_;  ///< The display name of the item.
    int weight_;        ///< Weight used for strength-based carry limits.
    ItemType type_;     ///< Category of item (weapon/armour/shield/ring).
};

#endif // ITEM_H
