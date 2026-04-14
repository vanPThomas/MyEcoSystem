#include "Utils.h"

std::mt19937 Utils::rng{ std::random_device{}() };

float Utils::RandomFloat(float min, float max)
{
    if (min > max) std::swap(min, max);
    
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

int Utils::RandomInt(int min, int max)
{
    if (min > max) std::swap(min, max);
    
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}