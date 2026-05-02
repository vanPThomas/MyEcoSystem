#include "Herbivore.h"

Herbivore::Herbivore(Environment& environment, float startX, float startY)
    : Creature(Environment& environment, startX, startY)
{
    // Herbivore-specific default DNA adjustments
    brain.dna.speed = 45.0f;
    brain.dna.aggression = 0.2f;
    brain.dna.gregariousness = 0.8f;   // herbivores like to stay in groups
    brain.dna.metabolism = 35.0f;       // lower metabolism
}

void Herbivore::update(float deltaTime)
{
    Creature::update(deltaTime);   // Call base movement / energy drain

    // Herbivore-specific behavior
    if (brain.getHunger() > 0.6f)
        seekFood();
    else if (brain.getFear() > 0.7f)
        fleeFromPredators();
    // else wander peacefully
}