#pragma once
#include <random>

namespace MathUtils
{
    // Returns a random float between min and max (inclusive)
    float randomFloat(float min, float max);

    // Returns a random int between min and max (inclusive)
    int randomInt(int min, int max);

    extern std::mt19937 rng;
}