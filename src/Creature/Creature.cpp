#include "Creature.h"

Creature::Creature(float startX, float startY)
    : x(startX)
    , y(startY)
    , dna()           // creates default DNA
    , brain(dna)      // passes the creature's own dna to the brain
{
    tx = MathUtils::randomFloat(-30.0f, 30.0f);
    ty = MathUtils::randomFloat(-30.0f, 30.0f);
}