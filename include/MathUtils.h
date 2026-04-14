#pragma once
#include <random>

namespace MathUtils
{
    // Returns a random float between min and max (inclusive)
    float RandomFloat(float min, float max);

    // Returns a random int between min and max (inclusive)
    int RandomInt(int min, int max);

    extern std::mt19937 rng;
}