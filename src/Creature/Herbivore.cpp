#include "Herbivore.h"

Herbivore::Herbivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Herbivore-specific default DNA adjustments
    brain.dna.setSpeed(45.0f);
    brain.dna.setAggression(0.2f);
    brain.dna.setGregariousness(0.8f);  // herbivores like to stay in groups
    brain.dna.setMetabolism(35.0f);     // lower metabolism
}

void Herbivore::update(float deltaTime)
{
    Creature::update(deltaTime);   // Call base movement / energy drain

    // // Herbivore-specific behavior
    // if (brain.getHunger() > 0.6f)
    //     seekFood();
    // else if (brain.getFear() > 0.7f)
    //     fleeFromPredators();
    // // else wander peacefully
}