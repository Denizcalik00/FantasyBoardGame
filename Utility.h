// Utility.h
// Helper functions for random numbers, probability checks, and time management.

#ifndef UTILITY_H
#define UTILITY_H

class Utility {
public:
    static int randInt(int min, int max);          // Random integer
    static double randReal(double min, double max); // Random double
    static bool checkProbability(double chance);    // True if event occurs
    static bool isDayTime(int commandCount);        // True if day, false if night
};

#endif
