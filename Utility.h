/**
 * @file Utility.h
 * @brief Provides helper functions for randomization, probability checks, and time management.
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <random>
#include <chrono>

class Utility {
public:
    /**
     * @brief Generates a random integer between min and max (inclusive).
     * @param min Minimum value
     * @param max Maximum value
     * @return Random integer
     */
    static int randInt(int min, int max);

    /**
     * @brief Generates a random real number between min and max.
     * @param min Minimum value
     * @param max Maximum value
     * @return Random double
     */
    static double randReal(double min, double max);

    /**
     * @brief Checks if an event occurs based on given probability.
     * @param chance Probability (0.0 to 1.0)
     * @return True if event occurs, false otherwise
     */
    static bool checkProbability(double chance);

    /**
     * @brief Determines if it's day or night based on command count.
     * @param commandCount Number of commands executed
     * @return True if day, false if night
     */
    static bool isDayTime(int commandCount);
};

#endif // UTILITY_H
