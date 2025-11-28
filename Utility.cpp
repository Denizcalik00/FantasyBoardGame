#include "Utility.h"
#include <random>
#include <chrono>

/**
 * @file Utility.cpp
 * @brief Implements utility functions for random numbers, probability, and day/night management.
 *
 * Responsibilities:
 *  - Generate random integers and real numbers.
 *  - Evaluate probabilistic events.
 *  - Maintain and toggle a simple day/night flag.
 */

/**
 * @brief Provides a reference to a static random number generator.
 * @return Reference to the Mersenne Twister RNG.
 */
static std::mt19937 &rng() {
    static std::mt19937 gen((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
    return gen;
}

/**
 * @brief Generates a random integer between min and max (inclusive).
 *
 * @param min Minimum integer value.
 * @param max Maximum integer value.
 * @return Random integer in [min, max].
 */
int Utility::randInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng());
}

/**
 * @brief Generates a random real number between min and max.
 *
 * @param min Minimum value.
 * @param max Maximum value.
 * @return Random double in [min, max).
 */
double Utility::randReal(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng());
}

/**
 * @brief Returns true with a given probability.
 *
 * @param chance Probability in [0.0, 1.0].
 * @return true with probability `chance`, false otherwise.
 */
bool Utility::probability(double chance) {
    return randReal(0.0, 1.0) <= chance;
}

// simple internal day/night flag:
static bool _isNight = false;

/**
 * @brief Toggles the day/night state.
 */
void Utility::toggleDayNight() {
    _isNight = !_isNight;
}

/**
 * @brief Returns true if it is currently night, false if day.
 *
 * @return Current day/night state.
 */
bool Utility::isNight() {
    return _isNight;
}
