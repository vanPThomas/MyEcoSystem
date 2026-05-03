#include "Carnivore.h"

Carnivore::Carnivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Carnivore-specific DNA defaults
    brain.dna.setSpeed(70.0f);          // faster
    brain.dna.setAggression(0.85f);     // much more aggressive
    brain.dna.setStrength(800.0f);
    brain.dna.setMetabolism(65.0f);     // higher metabolism (needs more food) 
    brain.dna.setVisionRange(220.0f);   // better vision for hunting
}

void Carnivore::update(float deltaTime)
{
    Creature::update(deltaTime);

    // if (brain.getHunger() > 0.5f)
    //     huntPrey();
    // else
    // {
    //     // occasional wandering or resting
    //     if (brain.getCurrentState() == Brain::State::Wandering)
    //     {
    //         // maybe pick random targets less often
    //     }
    // }
}