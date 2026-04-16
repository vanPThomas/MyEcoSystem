#include "MathUtils.h"

std::mt19937 MathUtils::rng{ std::random_device{}() };

float MathUtils::randomFloat(float min, float max)
{
    if (min > max) std::swap(min, max);
    
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

int MathUtils::randomInt(int min, int max)
{
    if (min > max) std::swap(min, max);
    
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}