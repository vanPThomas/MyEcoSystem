#include "Carnivore.h"

Carnivore::Carnivore(float startX, float startY, int spaceWidth, int spaceHeight)
    : Creature(startX, startY, spaceWidth, spaceHeight)
{
    // Carnivore-specific DNA defaults
    brain.dna.speed = 70.0f;           // faster
    brain.dna.aggression = 0.85f;      // much more aggressive
    brain.dna.strength = 800.0f;
    brain.dna.metabolism = 65.0f;      // higher metabolism (needs more food)
    brain.dna.visionRange = 220.0f;    // better vision for hunting
}

void Carnivore::update(float deltaTime)
{
    Creature::update(deltaTime);

    if (brain.getHunger() > 0.5f)
        huntPrey();
    else
    {
        // occasional wandering or resting
        if (brain.getCurrentState() == Brain::State::Wandering)
        {
            // maybe pick random targets less often
        }

    }
}