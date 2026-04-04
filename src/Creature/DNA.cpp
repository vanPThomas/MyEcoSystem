#include "DNA.h"
#include <random>

DNA DNA::crossover(const DNA& a, const DNA& b)
{
    return {
        (a.speed + b.speed) * 0.5f,
        (a.vision + b.vision) * 0.5f,
        (a.aggresion + b.aggresion) * 0.5f
    };
}

DNA DNA::mutate(const DNA& original, float rate)
{
    DNA result = original;
    result.speed += ((rand() / (float)RAND_MAX) - 0.5f) * rate;
    result.vision += ((rand() / (float)RAND_MAX) - 0.5f) * rate;
    result.aggresion += ((rand() / (float)RAND_MAX) - 0.5f) * rate;
    return result;
}