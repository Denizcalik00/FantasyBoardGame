#ifndef UTILITY_H
#define UTILITY_H

/**
 * @file Utility.h
 * @brief Provides static utility functions for RNG, probability, and day/night toggling.
 *
 * The Utility class offers general-purpose static methods used across modules,
 * including random number generation, probability checks, and day/night state management.
 * This class is non-instantiable.
 */

/**
  * @class Utility
  * @brief A static utility class for common operations.
  *
  * Responsibilities:
  *  - Generate random integers and real numbers.
  *  - Evaluate probability-based events.
  *  - Toggle and query day/night state.
  *
  * Design:
  *  - All functions are static.
  *  - No instances are allowed (constructor is deleted).
  */
class Utility {
public:

    /**
     * @brief Generates a random integer between min and max (inclusive).
     * @param min Minimum value.
     * @param max Maximum value.
     * @return Random integer in [min, max].
     */
    static int randInt(int min, int max);

    /**
     * @brief Generates a random real number between min and max.
     * @param min Minimum value.
     * @param max Maximum value.
     * @return Random double in [min, max].
     */
    static double randReal(double min, double max);

    /**
     * @brief Evaluates a probability check.
     * @param chance Probability of returning true (0.0 = 0%, 1.0 = 100%).
     * @return True with probability `chance`, false otherwise.
     */
    static bool probability(double chance);

    /**
     * @brief Toggles the internal day/night state.
     *
     * Flips the internal flag; if it was day, becomes night, and vice versa.
     */
    static void toggleDayNight();

    /**
     * @brief Checks if it is currently night.
     * @return True if night, false if day.
     */
    static bool isNight();

private:
    /// Private constructor to prevent instantiation
    Utility() = delete;
};

#endif // UTILITY_H
